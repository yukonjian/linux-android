/*
 * NXP IP3912 Ethernet driver
 *
 * Copyright(C) 2007 Sebastian Smolorz <ssm@emlix.com>, emlix GmbH
 * Copyright(C) 2002, 2003, 2004, 2007 NXP B.V.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation, version 2
 * of the Licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public Licence for more details.
 *
 * The full text of the licence can be found at
 * http://www.gnu.org/copyleft/gpl.html
 *
 *---------------------------------------------------------------------------
 * Revision History
 * Version       Author             Date           Remarks
 * 0.0.1       Mahadev K C      23/11/2005       Initial version
 * 2.0.0	ssmolorz	15/06/2007	Revamped for kernel 2.6.21
 *						and PNX8181 Firetux board
 * 2.1.0	ssmolorz	27/06/2007	Various fixes for critical bugs
 * 2.2.0	ssmolorz	04/07/2007	Support multicast list
 * 2.3.0	ssmolorz	06/07/2007	Automatic detection of link
 *						status
 * 2.4.0	ssmolorz	16/08/2007	Support 100 Mbit/s
 * 2.5.0	ssmolorz	23/08/2007	NAPI + Fix kernel crash in
 *						low memory situations
 * 2.5.1	ssmolorz	27/08/2007	Full NAPI (RX + TX)
 * 2.6.0	ssmolorz	28/08/2007	Put dscriptors and statuses
 *						into SCRAM
 *---------------------------------------------------------------------------
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/in.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/mii.h>
#include <linux/init.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <linux/highmem.h>
#include <linux/dma-mapping.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <linux/crc32.h>
#include <linux/clk.h>
#include <net/ip3912.h>
#include <asm/irq.h>
#include <asm/bitops.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
#include <mach/platform.h>
#endif

#include "ip3912.h"
#include "ip3912_cfg.h"
#include "ip3912_hw.h"
#include "ip3912_regs.h"

//Support to Qos,Add by Jame:2014.7.4
#include <net/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/udp.h>
#define NF_IP_LOCAL_OUT 3
#define UDP_PROTOCOL 17
unsigned int RTPSourceMin = 0;
unsigned int RTPSourceMax = 0;
unsigned int SIPDest      = 0;
static unsigned char is_nfhook_register = 0;
static struct nf_hook_ops nfhook;


MODULE_AUTHOR("Koninklijke Philips Electronics N.V., Sebastian Smolorz");
MODULE_DESCRIPTION("NXP IP3912 ethernet driver" DRV_VERSION " " DRV_RELDATE);
MODULE_LICENSE("GPL");

static int g_is10Mbit = 0;

static inline void ip3912_print_connection(struct net_device *dev, char *msg)
{
	ip3912_priv_t *priv = netdev_priv(dev);

	printk(KERN_INFO DRV_NAME ": %s%s up, speed is %s Mbps, %s Duplex%s\n",
		dev->name, msg,
		(priv->speed == ETN_MBITS_100) ? "100": "10",
		(priv->mode == ETN_MODE_FULL_DUPLEX) ? "Full": "Half",
		(priv->flow_ctrl == ETN_FLOW_CONTROL_ENABLE) ?
					", flow control enabled." : ".");
}


/* Free TX DMA mapping and skb. */
static inline void ip3912_free_tx_skb(dma_addr_t packet, struct sk_buff *skb)
{
#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
        // packet in SRAM and it is mapped at 0
        if(packet >= 0x2C000)
#endif
        dma_unmap_single(NULL, packet, skb->len, DMA_TO_DEVICE);
        dev_kfree_skb_any(skb);
}

static inline void ip3912_handle_tx_one(ip3912_priv_t *priv)
{
	tx_descr_t	*tx_descr;
	tx_status_t	*tx_status;

	tx_descr = &priv->tx_descr[priv->txconsumeindex];
	tx_status = &priv->tx_status[priv->txconsumeindex];

	/* Update stats. */
	if (tx_status->error) {
		priv->stats.tx_errors++;
		if (tx_status->late_collision)
			priv->stats.tx_window_errors++;
		if (tx_status->excessive_collision || tx_status->excessive_defer)
			priv->stats.tx_carrier_errors++;
		if (tx_status->underrun)
			priv->stats.tx_aborted_errors++;
	} else {
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += tx_descr->ctrl.size;
	}
	priv->stats.collisions += tx_status->collision_cnt;

	ip3912_free_tx_skb(tx_descr->packet,
				priv->tx_skbs[priv->txconsumeindex]);

	if (++priv->txconsumeindex == IP3912_DESCR_QUEUE_LEN)
		priv->txconsumeindex = 0;
}

#define IP3912_HANDLE_TX_DONT_WAKE_UP	0
#define IP3912_HANDLE_TX_WAKE_UP	1
#define IP3912_HANDLE_TX_DONT_CARE	2

static int ip3912_handle_tx(ip3912_priv_t *priv)
{
	uint32_t	txconsume_new;

	txconsume_new = ip3912_hw_get_txconsumeindex(priv);

	while (priv->txconsumeindex != txconsume_new)
		ip3912_handle_tx_one(priv);

	/* Check if a ip3912_down() is waiting for us and we processed the
	   last skb. */
	if (test_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags) &&
				priv->txproduceindex == txconsume_new) {
#ifdef CONFIG_IP3912_DEBUG
		printk(KERN_INFO DRV_NAME "up'ing sema in handle_tx\n");
#endif
		/* Signal ip3912_down() to go on. */
		up(&priv->txsem_ifdown);
		/* Don't wake queue. */
		return IP3912_HANDLE_TX_DONT_WAKE_UP;
	}
	else if (test_and_clear_bit(IP3912_FLAG_TX_FIFO_FULL, &priv->flags))
		/* Wake queue */
		return IP3912_HANDLE_TX_WAKE_UP;

	/* Let caller decide whether to wake up queue. */
	return IP3912_HANDLE_TX_DONT_CARE;
}

/* update the detailed RX error counters */
static inline void ip3912_handle_rx_errors(ip3912_priv_t *priv,
						uint32_t rxconsume)
{
	if (priv->rx_status[rxconsume].info.len_error)
		priv->stats.rx_length_errors++;

	if (priv->rx_status[rxconsume].info.no_descriptor) {
		priv->stats.rx_over_errors++;
		priv->stats.rx_fifo_errors++;
	}

	if (priv->rx_status[rxconsume].info.overrun)
		priv->stats.rx_missed_errors++;

	if (priv->rx_status[rxconsume].info.crc_error)
		priv->stats.rx_crc_errors++;

	if (priv->rx_status[rxconsume].info.alignment_error)
		priv->stats.rx_frame_errors++;

	priv->stats.rx_errors++;
}

#define IP3912_RX_MULTICAST_PASS	0
#define IP3912_RX_MULTICAST_BLOCK	1

/* Handle RX multicast frames. */
static inline int ip3912_handle_rx_multicast(struct net_device *dev,
							uint32_t rxconsume)
{
	ip3912_priv_t	*priv = netdev_priv(dev);

	priv->stats.multicast++;

	if (!(dev->flags & (IFF_PROMISC | IFF_ALLMULTI))) {
		if (priv->rx_status[rxconsume].info.fail_filter)
			return IP3912_RX_MULTICAST_BLOCK;
	}

	return IP3912_RX_MULTICAST_PASS;
}


static int ip3912_alloc_new_rx_skb(struct net_device *dev, uint32_t rxconsume)
{
        ip3912_priv_t *priv = netdev_priv(dev);

        priv->rx_skbs[rxconsume] = dev_alloc_skb(MAX_ETH_FRAME_SIZE);

        if (!priv->rx_skbs[rxconsume]) {
                if (printk_ratelimit())
                        printk(KERN_ERR DRV_NAME ": Allocating new skb in RX "
                                        "IRQ handler failed, losing one DMA "
                                        "descriptor for %s!\n", dev->name);
                /* This is quite nasty. We have to signal the DMA
                   engine not to use the packet buffer of this
                   descriptor although it is in the descriptor
                   array. We do this with a max. packet size of 0
                   for this descriptor. */
                priv->rx_descr[rxconsume].ctrl.size = 0;
                return -ENOMEM;
        }

        skb_reserve(priv->rx_skbs[rxconsume], NET_IP_ALIGN);

#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
        priv->rx_descr[rxconsume].packet = priv->rx_skbs[rxconsume]->data - PNX8181_SCRAM_VA_DEV; 
#else

        priv->rx_descr[rxconsume].packet = dma_map_single(NULL,
                        priv->rx_skbs[rxconsume]->data,
                        MAX_ETH_FRAME_SIZE, DMA_FROM_DEVICE);

        if (unlikely(!priv->rx_descr[rxconsume].packet)) {
                if (printk_ratelimit())
                        printk(KERN_ERR DRV_NAME ": Mapping of new skb in RX "
                                        "IRQ handler failed, losing one DMA "
                                        "descriptor for %s!\n", dev->name);
                /* Same as above, nasty. Without DMA mapping this skb
                   is useless. So free the mem and instruct the RX
                   DMA engine not use use this buffer. */
                dev_kfree_skb(priv->rx_skbs[rxconsume]);
                priv->rx_skbs[rxconsume] = NULL;
                priv->rx_descr[rxconsume].ctrl.size = 0;
                return -ENOMEM;
        }
#endif

        return 0;
}

static inline int ip3912_replace_missing_skb(struct net_device *dev,
							uint32_t rxconsume)
{
	ip3912_priv_t *priv = netdev_priv(dev);

	if (!ip3912_alloc_new_rx_skb(dev, rxconsume)) {
		priv->rx_descr[rxconsume].ctrl.size = priv->rx_buf_size - 1;
#ifdef CONFIG_IP3912_DEBUG
		printk(KERN_INFO DRV_NAME ": %s gets back one RX descriptor "
					"formerly lost due to low memory\n",
					dev->name);
#endif
		return 0;
	} else
		return -ENOMEM;
}


#define IP3912_RX_ERROR	1

static inline int ip3912_rx_error(ip3912_priv_t *priv,
					uint32_t rxconsume)
{
	rx_status_info_t *info = &priv->rx_status[rxconsume].info;

	if (*((uint32_t *)info) & IP3912_RX_STATUS_INFO_ERRMASK)
		return IP3912_RX_ERROR;
	else
		/* Also entered in case of a
		   1. Range error: Instead of checking the ethernet type/length
		      field to be really sure we assume that this is false
		      alarm here. In case of a 'real' range error there should
		      also be a CRC error anyway.
		   2. Alignment error: This is a common error in 100 Mbit/s
		      mode and also interpreted as false alarm. */
		return 0;
}


/*
 *  FUNCTION:	 ip3912_isr
 *  DESCRIPTION: This function handles the interrupt events from ip3912 for 
 *		 the packets transmitted or received
 *  PARAMETERS:
 *		 irq	- interrupt number
 *		 dev_id	- net_device structure for the device
 *  RETURN:
 *		 IRQ_HANDLED	- interrupt handled
 *		 IRQ_NONE	- invalid interrupt
 */
static irqreturn_t ip3912_isr(int irq, void *dev_id)
{
	struct net_device	*dev		= dev_id;
        ip3912_priv_t		*priv		= netdev_priv(dev);
	uint32_t		intstatus;

	/* Read the interrupt status ... */
	intstatus = ip3912_hw_get_intstatus(priv);
	/* ... and clear it. */
	ip3912_hw_clear_intstatus(priv);

	if (!intstatus)
		return IRQ_NONE;
#ifdef CONFIG_IP3912_TX_NAPI
	if (ip3912_hw_get_intenable(priv) & IP3912_RX_IRQS_ENABLE &&
		intstatus & (ETN_INTSTATUS_RX_DONE | ETN_INTSTATUS_RX_ERROR |
						ETN_INTSTATUS_RX_OVERRUN))
		    ip3912_hw_disable_and_clear_rx_ints(priv);
	if (ip3912_hw_get_intenable(priv) & IP3912_TX_IRQS_ENABLE &&
		intstatus & ETN_INTSTATUS_TX_DONE)
	    	ip3912_hw_disable_and_clear_tx_ints(priv);
	{
#else
	if (ip3912_hw_get_intenable(priv) & IP3912_RX_IRQS_ENABLE &&
		intstatus & (ETN_INTSTATUS_RX_DONE | ETN_INTSTATUS_RX_ERROR |
						ETN_INTSTATUS_RX_OVERRUN)) {
		ip3912_hw_disable_and_clear_rx_ints(priv);
#endif
		napi_schedule(&priv->napi);
	}

#ifndef CONFIG_IP3912_TX_NAPI
	/* Process all interrupts till there are no more. */
	do {
		/* check for TX done interrupt */
		if (intstatus & ETN_INTSTATUS_TX_DONE) {
			/* handle the transmitted packets */
			if (ip3912_handle_tx(priv) == IP3912_HANDLE_TX_WAKE_UP)
				netif_wake_queue(dev);
		}
		intstatus = ip3912_hw_get_intstatus(priv);
		ip3912_hw_clear_intstatus(priv);
	} while (intstatus);
#endif /* !CONFIG_IP3912_TX_NAPI */
	return IRQ_HANDLED;
}


/*
 *  FUNCTION:	 ip3912_get_aligned_address:
 *  DESCRIPTION: This function returns an aligned address for the boundary
 *		 specified.
 *  PARAMETERS:
 *		 addr	  - Address that need to be aligned
 *		 boundary - boundary for alignment
 * RETURN:
 *		 aligned address
 */
static inline dma_addr_t ip3912_get_aligned_address(dma_addr_t addr,
							int boundary)
{
	int mod;

	mod = addr % boundary;

	return mod ? addr + boundary - mod : addr;
}

#define SIZEOF_TX_ALLOC(x)						\
	sizeof(tx_descr_t) * ((x) + 1) + sizeof(tx_status_t) * ((x) + 1)

#define SIZEOF_RX_ALLOC(x)						\
	sizeof(rx_descr_t) * ((x) + 1) + sizeof(rx_status_t) * ((x) + 1)

#define SIZEOF_TX_DESCR(x)	sizeof(tx_descr_t) * (x)
#define SIZEOF_TX_STATUS(x)	sizeof(tx_status_t) * (x)

#define SIZEOF_RX_DESCR(x)	sizeof(rx_descr_t) * (x)
#define SIZEOF_RX_STATUS(x)	sizeof(rx_status_t) * (x)

/*
 *  FUNCTION:	 ip3912_alloc_dma_descriptors
 *  DESCRIPTION: This function allocates the DMA-capable memory required to
 *		 store the received packets and to store the hardware
 *		 descriptor array for addresses and statuses for TX and RX.
 *  PARAMETERS:
 * 		 priv	- ip3912_priv_t private structure
 *  RETURN:
 *		 0	- success
 */
static int ip3912_alloc_dma_descriptors(ip3912_priv_t *priv)
{
	int		i;
	dma_addr_t	dma_addr;
	void		*vaddr;

	/* Alloc mem for the array that holds pointers to TX skbs which
	   weren't sent out by the HW yet. */
	priv->tx_skbs = kmalloc(sizeof(struct sk_buff *) * IP3912_DESCR_QUEUE_LEN, GFP_KERNEL);
	if (!priv->tx_skbs)
		return -ENOMEM;

#ifndef CONFIG_IP3912_USE_SCRAM
	/* Alloc DMA mem for TX and RX descriptors and status arrays. */
	vaddr = dma_alloc_coherent(NULL, SIZEOF_TX_ALLOC(IP3912_DESCR_QUEUE_LEN) +
					SIZEOF_RX_ALLOC(IP3912_DESCR_QUEUE_LEN),
	 				&priv->dma_descr_status, GFP_KERNEL);
	if (!(priv->mem_descr_status = vaddr))
		goto out_free_tx_skbs;
#else
	vaddr = priv->mem_descr_status;
#endif

	/* Clear whole descriptor and status memory. */
	memset(priv->mem_descr_status, 0,
		SIZEOF_TX_ALLOC(IP3912_DESCR_QUEUE_LEN) + SIZEOF_RX_ALLOC(IP3912_DESCR_QUEUE_LEN));

	/* Memory is allocated, just align the addresses. */
	dma_addr = priv->dma_descr_status;

	priv->dma_tx_descr = ip3912_get_aligned_address(dma_addr,
							sizeof(tx_descr_t));
	priv->tx_descr = (tx_descr_t *)(vaddr + (priv->dma_tx_descr -
								dma_addr));

	dma_addr = priv->dma_tx_descr + SIZEOF_TX_DESCR(IP3912_DESCR_QUEUE_LEN);
	vaddr = (void *)priv->tx_descr + SIZEOF_TX_DESCR(IP3912_DESCR_QUEUE_LEN);

	priv->dma_tx_status = ip3912_get_aligned_address(dma_addr,
							sizeof(tx_status_t));
	priv->tx_status = (tx_status_t *)(vaddr + (priv->dma_tx_status -
								dma_addr));

	dma_addr = priv->dma_tx_status + SIZEOF_TX_STATUS(IP3912_DESCR_QUEUE_LEN);
	vaddr = (void *)priv->tx_status + SIZEOF_TX_STATUS(IP3912_DESCR_QUEUE_LEN);

	priv->dma_rx_descr = ip3912_get_aligned_address(dma_addr,
							sizeof(rx_descr_t));
	priv->rx_descr = (rx_descr_t *)(vaddr + (priv->dma_rx_descr -
								dma_addr));

	dma_addr = priv->dma_rx_descr + SIZEOF_RX_DESCR(IP3912_DESCR_QUEUE_LEN);
	vaddr = (void *)priv->rx_descr + SIZEOF_RX_DESCR(IP3912_DESCR_QUEUE_LEN);

	priv->dma_rx_status = ip3912_get_aligned_address(dma_addr,
							sizeof(rx_status_t));
	priv->rx_status = (rx_status_t *)(vaddr + (priv->dma_rx_status -
								dma_addr));

	/* Allocate memory for the array that holds the pointers to the
	   RX skbs. */
	priv->rx_skbs = kmalloc(sizeof(struct sk_buff *) * IP3912_DESCR_QUEUE_LEN, GFP_KERNEL);
	if (!priv->rx_skbs)
		goto out_free_dma_mem;
	for (i = 0; i < IP3912_DESCR_QUEUE_LEN; i++) {
		priv->rx_skbs[i] = dev_alloc_skb(MAX_ETH_FRAME_SIZE);
		if (!priv->rx_skbs[i])
			goto out_unmap_and_free_rx;

		skb_reserve(priv->rx_skbs[i], NET_IP_ALIGN);

#ifndef CONFIG_IP3912_USE_SCRAM_FOR_DATA
		priv->rx_descr[i].packet = dma_map_single(NULL,
						priv->rx_skbs[i]->data,
						MAX_ETH_FRAME_SIZE,
						DMA_FROM_DEVICE);
		if (unlikely(!priv->rx_descr[i].packet))
			goto out_free_rx;
#endif

		priv->rx_descr[i].ctrl.interrupt = 1;
		priv->rx_descr[i].ctrl.size = priv->rx_buf_size - 1;
	}

#ifdef CONFIG_IP3912_DEBUG
	printk(DRV_NAME ": Set Rx buffer size of %d to every DMA descriptor\n",
				priv->rx_buf_size);
#endif

	priv->lost_desc = 0;

	return 0;

out_free_rx:
	dev_kfree_skb(priv->rx_skbs[i]);

out_unmap_and_free_rx:
	for (--i; i >= 0; i--) {
		dma_unmap_single(NULL, priv->rx_descr[i].packet,
					MAX_ETH_FRAME_SIZE, DMA_FROM_DEVICE);
		dev_kfree_skb(priv->rx_skbs[i]);
	}

	kfree(priv->rx_skbs);

out_free_dma_mem:
#ifndef CONFIG_IP3912_USE_SCRAM
	dma_free_coherent(NULL, SIZEOF_TX_ALLOC(IP3912_DESCR_QUEUE_LEN) + SIZEOF_RX_ALLOC(IP3912_DESCR_QUEUE_LEN),
			priv->mem_descr_status, priv->dma_descr_status);
out_free_tx_skbs:
#endif
	kfree(priv->tx_skbs);

	return -ENOMEM;
}

static void ip3912_hw_soft_reset(struct net_device *dev)
{
	ip3912_priv_t *priv = netdev_priv(dev);
	u32 tmp;

	/* disable rx/tx */
	IP3912_WRITE_REG(priv, MAC1, 0);

	/* disable rx/tx */
	tmp = IP3912_READ_REG(priv, COMMAND);
	IP3912_WRITE_REG(priv, COMMAND, tmp & ~((1 << 0) | (1 << 1)));

	/* put rx/tx logic to pause mode */
	IP3912_WRITE_REG(priv, MAC1, (1 << 11) | (1 << 9));

	/* reset all data paths and registers */
	tmp = IP3912_READ_REG(priv, COMMAND);
	IP3912_WRITE_REG(priv, COMMAND, tmp | (1 << 3));

	udelay(1);

	/* unpause rx/tx logic */
	IP3912_WRITE_REG(priv, MAC1, 0);
}

/*
 *  FUNCTION:	 ip3912_free_dma_descriptors
 *  DESCRIPTION: This function frees the DMA-capable memory for
 *		 storing the received packets and the hardware
 *		 descriptor array for addresses and statuses for TX and RX.
 *		 It also frees the SKB memory allocated by kernel for
 *		 non-transmitted packets present in the queue.
 *  PARAMETERS:
 *		 priv	- ip3912_priv_t private structure
 *  RETURN:
 *		 None
 */
static void ip3912_free_dma_descriptors(ip3912_priv_t *priv)
{
	int i;

	/* Unmap and free all RX skbs. */
	for (i = 0; i < IP3912_DESCR_QUEUE_LEN; i++) {
		if (priv->rx_skbs[i]) {
			dma_unmap_single(NULL, priv->rx_descr[i].packet,
					MAX_ETH_FRAME_SIZE, DMA_FROM_DEVICE);
			dev_kfree_skb(priv->rx_skbs[i]);
		}
	}

	/* Free the memory for the array that holds the pointers to the
	   RX buffers. */
	kfree(priv->rx_skbs);

#ifndef CONFIG_IP3912_USE_SCRAM
	/* Free the memory allocated for RX and TX descriptors and status
	   arrays. */
	dma_free_coherent(NULL, SIZEOF_TX_ALLOC(IP3912_DESCR_QUEUE_LEN) + SIZEOF_RX_ALLOC(IP3912_DESCR_QUEUE_LEN),
			priv->mem_descr_status, priv->dma_descr_status);
#endif
	/* Free the memory for the array that holds the pointers to the
	   TX skbs which are under control of the driver. */
	kfree(priv->tx_skbs);
}

/* Write RX buffer size to every RX descriptor control word. */
static inline void ip3912_update_rx_buf_size(ip3912_priv_t *priv)
{
	int i;

	for (i = 0; i < IP3912_DESCR_QUEUE_LEN; i++)
		priv->rx_descr[i].ctrl.size = priv->rx_buf_size - 1;

#ifdef CONFIG_IP3912_DEBUG
	printk(DRV_NAME ": New max RX buffer size is %d\n",
				priv->rx_buf_size);
#endif
}


static inline void ip3912_free_irq_and_dma(struct net_device *dev)
{
	ip3912_priv_t *priv = netdev_priv(dev);

	/* free the interrupt */
//	free_irq(dev->irq, dev);
	/* free the memory */
	ip3912_free_dma_descriptors(priv);
}

static int ip3912_up(struct net_device *dev)
{
	int		ret_val;
	ip3912_priv_t	*priv		= netdev_priv(dev);

	/* Init PHY and afterwards the MAC host registers. */
	if ((ret_val = ip3912_hw_init(dev))) {
		ip3912_free_irq_and_dma(dev);
		return ret_val;
	}

	/* Set weight value depending on speed. */
	if (priv->speed == ETN_MBITS_10)
		priv->napi.weight = min_t(unsigned int, 16, IP3912_DESCR_QUEUE_LEN);
	else
		priv->napi.weight = min_t(unsigned int, 64, IP3912_DESCR_QUEUE_LEN);

	clear_bit(IP3912_FLAG_TX_FIFO_FULL, &priv->flags);

	sema_init(&priv->txsem_ifdown, 0);

	ip3912_hw_start(priv);

	return 0;
}

/*
 *  FUNCTION:	 ip3912_open
 *  DESCRIPTION: 'open' driver handler for ethernet device. This function
 *		 will set up the hardware, allocates memory and enables the
 *		 hardware for reception.
 *  PARAMETERS:
 *		 dev	- net_device structure for the device
 *  RETURN:
 *		 0	- success
 *		 ENOMEM	- memory allocation error
 *		 ENXIO	- IO error
 */
static int ip3912_open(struct net_device *dev)
{
    struct ip3912_priv *priv = netdev_priv(dev);
    int ret_val = 0;
#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
    int i=0;
#endif

    /* Allocate memory buffers for TX/RX descriptors and RX data. */
    if (ip3912_alloc_dma_descriptors(priv)) {
        printk(KERN_ERR DRV_NAME ": Unable to allocate memory "
                "during ifup of %s.\n", dev->name);
        return -ENOMEM;
    }

#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
    for (i = 0; i < IP3912_DESCR_QUEUE_LEN; i++)
    {
        ip3912_alloc_new_rx_skb(dev,i);
        priv->rx_descr[i].ctrl.interrupt = 1;
        priv->rx_descr[i].ctrl.size = priv->rx_buf_size - 1;
    }
#endif

#if 0
	/* install the ISR */
	ret_val = request_irq(dev->irq, ip3912_isr, 0, dev->name, dev);
	if (ret_val) {
		printk(KERN_ERR DRV_NAME ": Requesting IRQ number %d failed "
					"for %s.\n", dev->irq, dev->name);
		goto out_free_dma_mem;
	}
#endif
	if (priv->phydev)
		phy_start(priv->phydev);
	else
		netif_carrier_on(dev);

	/* setup the DMA descriptors */
	ip3912_hw_setup_dma_descriptors(priv, IP3912_DESCR_QUEUE_LEN);

	/* Bring interface up. */
	if ((ret_val = ip3912_up(dev)))
		goto out_free_dma_mem;

	netif_start_queue(dev);

	napi_enable(&priv->napi);

	return 0;

out_free_dma_mem:
	ip3912_free_dma_descriptors(priv);

	return ret_val;
}


static void ip3912_down(struct net_device *dev)
{
	ip3912_priv_t *priv = netdev_priv(dev);

#if 1
	/* Do not replace with netif_stop_queue! We want ensure that no
	   hard_start_xmit() is running. */
	netif_tx_disable(dev);
#else
	/* netif_tx_disable will call netif_stop_queue */
	netif_stop_queue(dev);
#endif
	set_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags);
	/* Wait for the TX DMA engine to complete. */
	if (priv->txproduceindex != priv->txconsumeindex) {
#ifdef CONFIG_IP3912_DEBUG
		printk(KERN_INFO DRV_NAME "decrementing sema while trying "
				"to disable interface %s\n", dev->name);
#endif
		down(&priv->txsem_ifdown); /* replace with down_interruptible() */
	}
	clear_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags);

	/* Stop HW for this net_device. */
	ip3912_hw_stop(priv);
}

/*
 *  FUNCTION:	 ip3912_stop
 *  DESCRIPTION: 'stop' driver handler for ethernet device. This function will
 *		 disable the hardware, free the memory allocated and reverse
 *		 all other operations which were set up in the open-handler.
 *  PARAMETERS:
 *		 dev	- net_device structure for the device
 *  RETURN:
 *		 0	- success
 */
static int ip3912_stop(struct net_device *dev)
{
	struct ip3912_priv *priv = netdev_priv(dev);

	napi_disable(&priv->napi);
	if (priv->phydev)
		phy_stop(priv->phydev);
	else
		netif_carrier_off(dev);
//	netif_stop_queue(dev);
	ip3912_down(dev);
	ip3912_free_irq_and_dma(dev);

	return 0;
}


static int ip3912_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	ip3912_priv_t	*priv = netdev_priv(dev);
	unsigned long	flags;


	/* Check whether the TX FIFO is full. */
	if(g_is10Mbit)
	{
		mdelay(2);
	}

	spin_lock_irqsave(&priv->lock, flags);

	if (ip3912_hw_is_txfifo_full(priv, IP3912_DESCR_QUEUE_LEN)) {
		netif_stop_queue(dev);
		set_bit(IP3912_FLAG_TX_FIFO_FULL, &priv->flags);

		spin_unlock_irqrestore(&priv->lock, flags);

#ifdef CONFIG_IP3912_DEBUG
		printk(DRV_NAME ": %s: TX FIFO is full, leaving "
					"hard_start_xmit() ...\n", dev->name);
#endif

		return NETDEV_TX_BUSY;
	}

    /* Map skb data to DMA. */
#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
     if (skb->data < IP3912_SCRAM_PACKET_BASE  ||
      skb->data > IP3912_SCRAM_BASE_VA)
      priv->tx_descr[priv->txproduceindex].packet =
       dma_map_single(NULL, skb->data, skb->len, DMA_TO_DEVICE);
     else
      priv->tx_descr[priv->txproduceindex].packet =
       skb->data - PNX8181_SCRAM_VA_DEV;
#else
     priv->tx_descr[priv->txproduceindex].packet =
      dma_map_single(NULL, skb->data, skb->len, DMA_TO_DEVICE);
#endif

	if (unlikely(!priv->tx_descr[priv->txproduceindex].packet)) {

		dev_kfree_skb(skb);
		priv->stats.tx_dropped++;

		spin_unlock_irqrestore(&priv->lock, flags);

		printk(KERN_ERR DRV_NAME "DMA mapping of TX skb data failed, "
					"dropping packet.\n");
		return 0;
	}

	/* Set Control word values. */
	priv->tx_descr[priv->txproduceindex].ctrl.size = skb->len - 1;
	priv->tx_descr[priv->txproduceindex].ctrl.override = 1;
	priv->tx_descr[priv->txproduceindex].ctrl.pad = 1;
	priv->tx_descr[priv->txproduceindex].ctrl.crc = 1;
	priv->tx_descr[priv->txproduceindex].ctrl.last = 1;
	priv->tx_descr[priv->txproduceindex].ctrl.interrupt = 1;

	/* Remember skb for freeing in ISR. */
	priv->tx_skbs[priv->txproduceindex] = skb;

	priv->txproduceindex++;
	if (priv->txproduceindex == IP3912_DESCR_QUEUE_LEN)
		priv->txproduceindex = 0;

	/* Initiate DMA transmission. */
	ip3912_hw_set_txproduceindex(priv, priv->txproduceindex);

	dev->trans_start = jiffies;

	/* Check if array of TX skb pointers is full. In this case we have to
	   free the first pending one now. Otherwise we would overwrite this
	   skb pointer the next time this routine is entered before
	   ip3912_poll had a chance to free it. */
	if (priv->txproduceindex == priv->txconsumeindex)
		ip3912_handle_tx_one(priv);

	spin_unlock_irqrestore(&priv->lock, flags);

	return NETDEV_TX_OK;
}

static int ip3912_poll(struct napi_struct *napi, int budget)
{
	ip3912_priv_t *priv	= container_of(napi, ip3912_priv_t, napi); 
	struct net_device *dev = priv->dev;
	int		packets		= 0;
	/* If we return the complete budget we will 
	 * get a crash in the network layer 
	 */
	int		quota		= budget-1; 
	uint32_t	rxproduce;
	uint32_t	rxconsume;
	struct sk_buff	*skb;

#ifdef CONFIG_IP3912_TX_NAPI
	uint32_t	txconsume_new;
#endif /* CONFIG_IP3912_TX_NAPI */

	/* First handle RX done packets (more critical than TX done). */
	rxproduce = ip3912_hw_get_rxproduceindex(priv);
	rxconsume = ip3912_hw_get_rxconsumeindex(priv);

	while (packets < quota && rxproduce != rxconsume) {

		if (unlikely(priv->rx_skbs[rxconsume] == NULL)) {
			if (!ip3912_replace_missing_skb(dev, rxconsume))
				priv->lost_desc--;
			priv->stats.rx_errors++;
			goto rx_error;
		}

		if (ip3912_rx_error(priv, rxconsume) == IP3912_RX_ERROR) {
			ip3912_handle_rx_errors(priv, rxconsume);
			goto rx_error;
		}

		if (!priv->rx_status[rxconsume].info.last_frag) {
			priv->stats.rx_errors++;
			goto rx_error;
		}

		if (priv->rx_status[rxconsume].info.multicast_frame) {
			if (ip3912_handle_rx_multicast(dev, rxconsume) ==
						IP3912_RX_MULTICAST_BLOCK)
				goto rx_error;
		}

#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
		if (priv->rx_descr[rxconsume].packet > 0x2C000)
#endif
                dma_unmap_single(NULL, priv->rx_descr[rxconsume].packet,
                        MAX_ETH_FRAME_SIZE, DMA_FROM_DEVICE);

		skb = priv->rx_skbs[rxconsume];

		skb_put(skb, priv->rx_status[rxconsume].info.size + 1);
		skb->dev = dev;
		skb->protocol = eth_type_trans(skb, dev);
		skb->ip_summed = CHECKSUM_NONE;

                /* submit the packet to kernel */
		netif_receive_skb(skb);

		priv->stats.rx_packets++;
		priv->stats.rx_bytes +=
				priv->rx_status[rxconsume].info.size + 1;
		packets++;

		dev->last_rx = jiffies;

		if (unlikely(ip3912_alloc_new_rx_skb(dev, rxconsume))) {
			/* allocation of new skb failed */
			if (++priv->lost_desc == IP3912_DESCR_QUEUE_LEN) {
				/* No single DMA descriptor points to a free
				   skb. EMERGENCY! Memory exhausted.
				   Stop ETN HW. */
				ip3912_hw_stop(priv);
				printk(KERN_ERR DRV_NAME ": Unable to alloc "
					"memory for new RX skbs, eth HW "
					"stopped. You have to manually "
					"restart (down-up) %s.\n", dev->name);
				priv->lost_desc = 0;
				return 0;
			}
		}

rx_error:
		if (++rxconsume == IP3912_DESCR_QUEUE_LEN)
			rxconsume = 0;

		ip3912_hw_set_rxconsumeindex(priv, rxconsume);

		rxproduce = ip3912_hw_get_rxproduceindex(priv);
	}

	ip3912_hw_clear_intstatus_rx(priv);

#ifdef CONFIG_IP3912_TX_NAPI
	/* Next handle TX done packets. */
	txconsume_new = ip3912_hw_get_txconsumeindex(priv);

	while (priv->txconsumeindex != txconsume_new) {
		ip3912_handle_tx_one(priv);
		txconsume_new = ip3912_hw_get_txconsumeindex(priv);
	}

	ip3912_hw_clear_intstatus_tx(priv);

	/* Check if a ip3912_down() is waiting for us and we processed the
	   last skb. */
	if (test_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags) &&
				priv->txproduceindex == txconsume_new)
		/* Signal ip3912_down() to go on. */
		up(&priv->txsem_ifdown);

	else if (test_and_clear_bit(IP3912_FLAG_TX_FIFO_FULL, &priv->flags))
		/* Wake queue */
		netif_wake_queue(dev);
#endif /* CONFIG_IP3912_TX_NAPI */

	/* If we processed all packets we're done. Tell the kernel and
	   reenable interrupts. */
	//*budget -= packets;
	//dev->quota -= packets;

	if (rxproduce == rxconsume) {
		napi_complete(napi);
		ip3912_hw_enable_interrupts(priv);
		return packets; /* TODO sh check! */
	}

	/* We couldn't process every packet. */
	return 1;
}


/* We assume that the RX filter settings can be changed on the fly, i.e.
   without bringing down a running interface. */
static void ip3912_set_multicast_list(struct net_device *dev)
{
	ip3912_priv_t		*priv		= netdev_priv(dev);
	struct dev_mc_list	*mc_list;
	uint32_t		hash_l		= 0;
	uint32_t		hash_h		= 0;
	int			bit_nr		= 0;

	priv->mc_list_set = 1;

	/* Promiscous mode? */
	if (dev->flags & IFF_PROMISC) {
		ip3912_hw_promisc_mode(priv);
		return;
	}

	/* Receive all multicast packets? */
	if (dev->flags & IFF_ALLMULTI) {
		ip3912_hw_all_multi(priv);
		return;
	}

	/* No multicast, normal RX operation? */
	if (dev->mc_count == 0) {
		ip3912_hw_normal_rx_op(priv);
		return;
	}

	/* Update of multicast list. Calculate new hash filter. */
	for (mc_list = dev->mc_list; mc_list; mc_list = mc_list->next) {

		bit_nr = ether_crc(ETH_ALEN, mc_list->dmi_addr) >> 23 & 0x3F;

		if (bit_nr < 32)
			hash_l |= 1 << bit_nr;
		else
			hash_h |= 1 << (bit_nr - 32);
	}

	/* Program HW multicast hash filter. */
	ip3912_hw_multicast(priv, hash_l, hash_h);
}


static int ip3912_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *hw_addr	= (struct sockaddr *)addr;
	int		dev_up_again	= 0;
	int		ret_val		= 0;

	if (!is_valid_ether_addr(hw_addr->sa_data))
		return -EADDRNOTAVAIL;

	if (netif_running(dev)) {
		ip3912_down(dev);
		dev_up_again = 1;
	}

	/* copy the MAC address to dev structure */
	memcpy(dev->dev_addr, hw_addr->sa_data, dev->addr_len);
	/* Write new MAC address into the registers. */
	ip3912_hw_set_mac_addr(dev);

	if (dev_up_again) {

		if ((ret_val = ip3912_up(dev))) {
			printk(KERN_ERR DRV_NAME ": Cannot bring %s up after "
				"setting MAC address, interface remains "
				"down.\n", dev->name);
			return ret_val;
		}

		netif_wake_queue(dev);
	}

	return 0;
}

static int ip3912_change_mtu(struct net_device *dev, int new_mtu)
{
	ip3912_priv_t	*priv		= netdev_priv(dev);
	int		ret_val		= 0;

#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
	if (new_mtu < VLAN_ETH_ZLEN || new_mtu > VLAN_ETH_DATA_LEN)
		return -EINVAL;
#else
	if (new_mtu < ETH_ZLEN || new_mtu > ETH_DATA_LEN)
		return -EINVAL;
#endif

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		priv->rx_buf_size = new_mtu + ETN_HEADER_SIZE;
	} else {
		/* bring down the interface */
		ip3912_down(dev);

		dev->mtu = new_mtu;
		priv->rx_buf_size = new_mtu + ETN_HEADER_SIZE;

		ip3912_update_rx_buf_size(priv);

		if ((ret_val = ip3912_up(dev))) {
			printk(KERN_ERR DRV_NAME ": Cannot bring %s up after "
				"changing MTU value, interface remains "
				"down.\n", dev->name);
			return ret_val;
		}

		/* Restart accepting the packets. */
		netif_wake_queue(dev);
	}

	return 0;
}


static void ip3912_tx_timeout(struct net_device *dev)
{
	unsigned long	flags;
	ip3912_priv_t	*priv		= netdev_priv(dev);
	int		wake_queue	= IP3912_HANDLE_TX_WAKE_UP;

#ifdef CONFIG_IP3912_DEBUG
	printk(KERN_INFO DRV_NAME ": %s: TX Timeout!\n", dev->name);
#endif

	netif_stop_queue(dev);

	spin_lock_irqsave(&priv->lock, flags);

	if (unlikely(priv->txproduceindex == priv->txconsumeindex)) {
#ifdef CONFIG_IP3912_DEBUG
		printk(KERN_ERR DRV_NAME ": %s: TX timeout occured but there "
				"is no buffer to process!\n", dev->name);
#endif
		goto out_tx_timeout;
	}

	wake_queue = ip3912_handle_tx(priv);

	if (wake_queue == IP3912_HANDLE_TX_DONT_CARE)
		wake_queue = IP3912_HANDLE_TX_WAKE_UP;


	/* Now there should really be no packet in the TX FIFO. If there are
	   some, nevertheless, something really weird is bugging the HW. Either
	   the counters are screwed up or the DMA engine does not do its work.
	   Resetting it is our last hope. */
	if (unlikely(priv->txproduceindex != priv->txconsumeindex)) {
		printk(KERN_ERR "%s: FATAL: TX DMA engine does not process "
				"packets!\n", dev->name);

		/* Release DMA mapping and skbs. */
		do {
			priv->stats.tx_errors++;

			ip3912_free_tx_skb(
				priv->tx_descr[priv->txconsumeindex].packet,
					priv->tx_skbs[priv->txconsumeindex]);

			if (++priv->txconsumeindex == IP3912_DESCR_QUEUE_LEN)
				priv->txconsumeindex = 0;

		} while (priv->txconsumeindex != priv->txproduceindex);

		if (test_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags)) {
			/* Signal ip3912_down() to go on. */
			up(&priv->txsem_ifdown);
			wake_queue = IP3912_HANDLE_TX_DONT_WAKE_UP;
		}

		/* Reset TX data path HW. */
		ip3912_hw_reset_tx(priv);
	}

out_tx_timeout:
	 spin_unlock_irqrestore(&priv->lock, flags);

	if (wake_queue == IP3912_HANDLE_TX_WAKE_UP)
		netif_wake_queue(dev);
}

/*
 *  FUNCTION:	 ip3912_get_stats
 *  DESCRIPTION: 'get_stats' driver handler for ethernet device. This function
 *		 returns the address of net_device_stats structure that
 *		 contains the statistics for the ethernet device.
 *  PARAMETERS:
 *		 dev	- net_device structure for the device
 *  RETURN:
 *		 address of the net_device_stats structure
 */
static struct net_device_stats *ip3912_get_stats(struct net_device *dev)
{
	ip3912_priv_t *priv = netdev_priv(dev);

	/* return the address priv->stats structure that contain the
	   counters */
	return &priv->stats;
}

/* Callback from the phy layer */
static void ip3912_adjlink(struct net_device *dev)
{
	struct ip3912_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	unsigned long flags;
	int speed, mode;

	if (!phydev->link)
	{
		printk(KERN_INFO "%s: Link down\n", dev->name);
		priv->speed = -1;
		priv->mode = -1; /* Link down ! */
		return;
	}

	spin_lock_irqsave(&priv->lock, flags);

	if (phydev->speed == SPEED_100)
    
		speed = ETN_MBITS_100;
	else
		speed = ETN_MBITS_10;

	if (phydev->duplex)
		mode = ETN_MODE_FULL_DUPLEX;
	else
		mode = ETN_MODE_HALF_DUPLEX;

	/* If none is different .. go out*/
	if(mode == priv->mode && speed == priv->speed)
		goto out;

	/*
	 * We must wait for all TX data to leave the system
	 *
	 * we will call netif_carrier_off to prevent more packages going
	 * through this interface
	 */
	netif_carrier_off(dev);

	set_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags);
	/* Wait for the TX DMA engine to complete. */
	if (priv->txproduceindex != priv->txconsumeindex) {
		printk(KERN_INFO DRV_NAME "decrementing sema while trying "
			"to disable interface %s\n", dev->name);
		spin_unlock_irqrestore(&priv->lock, flags);
		down(&priv->txsem_ifdown); /* replace with down_interruptible() */
		spin_lock_irqsave(&priv->lock, flags);
	}
	clear_bit(IP3912_FLAG_CHECK_TX_DMA, &priv->flags);

	ip3912_hw_stop(priv);
	priv->mode = mode;
	priv->speed = speed;
	ip3912_up(dev);

	/* Tell the kernel your network cable is ready again */
	netif_carrier_on(dev);

	ip3912_print_connection(dev, "");

out:
	spin_unlock_irqrestore(&priv->lock, flags);
}

/* The ethtool ioctls */
static int ip3912_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ip3912_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;

	if (!phydev)
		return -ENODEV;

	return phy_ethtool_gset(phydev, cmd);
}

static int ip3912_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ip3912_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;

	if (!phydev)
		return -ENODEV;

	return phy_ethtool_sset(phydev, cmd);
}

static void ip3912_get_drvinfo(struct net_device *dev,
			     struct ethtool_drvinfo *info)
{
	struct ip3912_priv *priv = netdev_priv(dev);

	strcpy(info->driver, priv->pdev->dev.driver->name);
	strcpy(info->version, "");
	strcpy(info->bus_info, priv->pdev->dev.bus->name);
}

static struct ethtool_ops ip3912_ethtool_ops = {
	.get_settings		= ip3912_get_settings,
	.set_settings		= ip3912_set_settings,
	.get_drvinfo		= ip3912_get_drvinfo,
	.get_link		= ethtool_op_get_link,
};

/*Added by akuvox, support IOCTL to get phy link status*/
struct ksz8873_vlan {
	u16 id;
	u16 members;
};

struct ksz8873 {
	struct i2c_client *client;
	struct proc_dir_entry *pde;
	struct mutex lock;
	struct ksz8873_vlan vlans[16];
};

/*Added by akuvox, support IOCTL to config VLAN */
struct ksz8873_VLAN_t {
  unsigned int VLAN_Cmd;
  unsigned int VLAN_Portx;
  unsigned int VLAN_ID;
  unsigned char VLAN_Priority;
};

struct ksz8873_QoS_t {
  unsigned int RTPSourceMin;
  unsigned int RTPSourceMax;
  //unsigned int SIPDest;
  unsigned char SIPTosID;
  unsigned char RTPTosID;
};

int ksz8873_get_link(int port);
void ksz8873_set_VLANID(int port,int IDValue);
void ksz8873_set_VLANPriority(int port,int VLANPriority);
void ksz8873_enable_VLAN(int port);
void ksz8873_disable_VLAN(int port);
#define CONFIG_VLAN       0x01
#define DISABLE_VLAN      0x02
#define SET_VLAN_PRIORITY 0x03
#define ENABLE_VLAN       0x04

unsigned char SIP_tos_ID = 0;
unsigned char RTP_tos_ID = 0;


unsigned int hook_func(unsigned int hooknum,
	                   struct sk_buff *skb,
	                   const struct net_device *in,
	                   const struct net_device *out,
	                   int (*okfn)(struct sk_buff *))
{
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  struct udphdr *udph;

  if (!sb) 
  	return NF_ACCEPT;
  iph = ip_hdr(sb);
  if (!iph)
  	return NF_ACCEPT;
  
  if ( iph->protocol == UDP_PROTOCOL ) {
  	unsigned int ByteSwpDest   = 0;
	unsigned int ByteSwpSource = 0;
	
  	udph         = udp_hdr(sb);
	ByteSwpDest  = (udph->dest & 0xFF00) >> 8;
	ByteSwpDest |= (udph->dest & 0x00FF) << 8;

	ByteSwpSource  = (udph->source & 0xFF00) >> 8;
	ByteSwpSource |= (udph->source & 0x00FF) << 8;
		
    if (ByteSwpDest == SIPDest) {
  	  //printk("@ protocol UDP,SIP dest %d\n",ByteSwpDest);
  	  iph->tos &= 0x03;
  	  iph->tos |= (SIP_tos_ID << 2) & 0xFC;//0x68;
	  ip_send_check(iph);
    }
  
    if ( (ByteSwpSource >= RTPSourceMin) && (ByteSwpSource <= RTPSourceMax) ) {
  	  //printk("@ protocol UDP,RTP source %d\n",ByteSwpSource);
  	  iph->tos &= 0x03;
  	  iph->tos |= (RTP_tos_ID << 2) & 0xFC;//0x70;
	  ip_send_check(iph);
    }
  }

  return NF_ACCEPT;
}

/*
 * Handle the ethtool ioctls at the phylayer
 */
static int ip3912_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct ip3912_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	struct ksz8873_VLAN_t *VLANConfig = NULL;
	struct ksz8873_QoS_t *QoSConfig = NULL;
		
	if (!netif_running(dev))
		return -EINVAL;

	/*Added by akuvox, support IOCTL to get phy link status*/
	if(cmd == SIOCWANDEV || cmd == SIOCGMIIREG)
	{
      if_mii(rq)->val_out = ksz8873_get_link(if_mii(rq)->reg_num == 2 ? 1:2);		
	  if((if_mii(rq)->val_out & 0x0C) == 0)
	  {			
	    g_is10Mbit = 1;		
	  } else {			
	    g_is10Mbit = 0;		
	  }
	  return 0;
	}
	
	if (cmd == SIOCVLANDEV) {
	  VLANConfig = (struct ksz8873_VLAN_t *)if_mii(rq);
	  switch (VLANConfig->VLAN_Cmd) {
	  	case CONFIG_VLAN:
			//printk("Config VLAN port%d\n",VLANConfig->VLAN_Portx);
		    ksz8873_set_VLANID(VLANConfig->VLAN_Portx,VLANConfig->VLAN_ID);
			return 0;
	    break;
		case DISABLE_VLAN:
			//printk("Disable VLAN port%d\n",VLANConfig->VLAN_Portx);
		    ksz8873_disable_VLAN(VLANConfig->VLAN_Portx);
			return 0;
	    break;
		case SET_VLAN_PRIORITY:
			//printk("Set VLAN priority port%d\n",VLANConfig->VLAN_Portx);
			ksz8873_set_VLANPriority(VLANConfig->VLAN_Portx,VLANConfig->VLAN_Priority); //ksz8873_set_VLANPriority
			//ksz8873_enable_VLAN(VLANConfig->VLAN_Portx);
		break;
		case ENABLE_VLAN:
			//printk("Enable VLAN port%d/n",VLANConfig->VLAN_Portx);
			ksz8873_enable_VLAN(VLANConfig->VLAN_Portx);
	    default:
			return 0;
		break;
	  }
	return 0;
	}

	if (cmd == SIOCQOSDEV) {
	  QoSConfig    = (struct ksz8873_QoS_t *)if_mii(rq);

	  RTPSourceMin = QoSConfig->RTPSourceMin;
	  RTPSourceMax = QoSConfig->RTPSourceMax;
	  SIPDest      = 5060;//QoSConfig->SIPDest;
	  SIP_tos_ID   = QoSConfig->SIPTosID;
	  RTP_tos_ID   = QoSConfig->RTPTosID;
	  if (0 == is_nfhook_register) {
	  	is_nfhook_register = 1;
        nfhook.hook     = hook_func;
	    nfhook.hooknum  = NF_IP_LOCAL_OUT;
	    nfhook.pf       = PF_INET;
	    nfhook.priority = NF_IP_PRI_FIRST;
	    nf_register_hook(&nfhook);
	  }
	  return 0;
	}
	
	if (!phydev)
		return -ENODEV;

	return phy_mii_ioctl(phydev, if_mii(rq), cmd);
}

static struct ip3912_priv *first_priv;

static const struct net_device_ops ip3912_netdev_ops = {
	.ndo_open		= ip3912_open,
	.ndo_stop		= ip3912_stop,
	.ndo_start_xmit		= ip3912_hard_start_xmit,
	.ndo_tx_timeout		= ip3912_tx_timeout,
	.ndo_get_stats		= ip3912_get_stats,
	.ndo_set_multicast_list = ip3912_set_multicast_list,
	.ndo_set_mac_address	= ip3912_set_mac_address,
	.ndo_change_mtu		= ip3912_change_mtu,
	.ndo_do_ioctl		= ip3912_ioctl,
};

/*
 * Try to get a new instance up and running
 */
static int __devinit ip3912_probe(struct platform_device *pdev)
{
	struct ip3912_pdev *pdata;
	struct resource *regs;
	struct net_device *dev;
	struct ip3912_priv *priv;
	unsigned int dev_id;
	int ret = -ENXIO;


#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
        /* Clear the SCRAM */
        memset(IP3912_SCRAM_PACKET_BASE,0,IP3912_SCRAM_PACKET_SIZE);
#endif
    
	/* Get platform data */
	pdata = (struct ip3912_pdev *)pdev->dev.platform_data;
	if (!pdata) {
		dev_err(&pdev->dev, "no pdata defined!\n");
		goto out;
	}

	/* TODO: This should go away later */
	dev_id = pdev->id;

	/* Get the resources */
	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs) {
		dev_err(&pdev->dev, "no memory region defined\n");
		goto out;
	}

	/* Get the ethernet device */
	dev = alloc_etherdev(sizeof(*priv));
	if (!dev) {
		dev_err(&pdev->dev, "etherdev alloc failed, aborting.\n");
		ret = -ENOMEM;
		goto out;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

	priv = netdev_priv(dev);
	priv->pdev = pdev;
	priv->dev = dev;

	spin_lock_init(&priv->lock);

	/* Enable the clocks */
	if (!pdata->clock) {
		dev_err(&pdev->dev, "no clock specified for the device\n");
		goto out_free_dev;
	}

	priv->clock = clk_get(&pdev->dev, pdata->clock);
	if (!priv->clock)
	{
		dev_err(&pdev->dev, "can't get a clock for the device\n");
		goto out_free_dev;
	}

	if (clk_enable(priv->clock))
	{
		dev_err(&pdev->dev, "can't enable the clocking\n");
		goto out_free_dev;
	}

	/* Setup the private structure */
	priv->base_addr = regs->start;
	priv->rx_buf_size = MAX_ETH_FRAME_SIZE;

	priv->base_addr_virt = ioremap(priv->base_addr, 
					regs->end - regs->start + 1);

	if (!priv->base_addr_virt) {
		dev_err(&pdev->dev, "failed to map registers, aborting.\n");
		ret = -ENOMEM;
		goto out_disable_clocks;
	}

	/* Take the phy from the platform data */
	dev->irq = pdata->irq;
	priv->phy = pdata->phy;

	/* TODO: Remove this or at least: make it clearer :) */
#ifdef CONFIG_IP3912_USE_SCRAM
	priv->mem_descr_status = (void *)(IP3912_SCRAM_BASE_VA +
					IP3912_SCRAM_PER_ETN * dev_id);
	priv->dma_descr_status = IP3912_SCRAM_BASE +
					IP3912_SCRAM_PER_ETN * dev_id;
#endif

	if (dev_id == 0) {
		/* PHYs can only be detected through the first unit.
		 * Therefore we keep a reference to it for mii_init if unit 1
		 * is disabled and unit 2 enabled.
		 */
		first_priv = priv;
#ifndef CONFIG_IP3912_ETN1
		return 0;
#endif
	}

	ip3912_hw_soft_reset(dev);

	/* Copy MAC address from HW registers into net_device struct.
	   Note: As currently the MAC address is unset in the HW during a
	   reset we read the address now. At this point the MAC address set
	   by u-boot is still there. */
	ip3912_hw_retrieve_mac_addr(dev);

	dev->netdev_ops = &ip3912_netdev_ops;
	netif_napi_add(dev, &priv->napi, ip3912_poll, 64);
	dev->ethtool_ops = &ip3912_ethtool_ops;

	/* assing the net_device data fields */
	strcpy(dev->name, "eth%d");
	dev->watchdog_timeo = 5 * HZ;

	if (register_netdev(dev) != 0) {
		dev_err(&pdev->dev, "Unable to register network device\n");
		ret = -ENXIO;
		goto out_iounmap;
	}

	/* install the ISR */
	if (request_irq(dev->irq, ip3912_isr, 0, dev->name, dev)) {
		dev_err(&pdev->dev, "Requesting IRQ number %d failed "
					"for s.\n", dev->irq);
		goto out_unreg_dev;
	}

	platform_set_drvdata(pdev, dev);

	/* Register the mii bus for this interface */
	ip3912_mii_init(priv, first_priv);

	/* Try to use the phydev */
	if (priv->phy) {
		priv->phydev = phy_connect(dev, priv->phy, &ip3912_adjlink,
					PHY_BASIC_FEATURES, PHY_INTERFACE_MODE_RMII);

		if (IS_ERR(priv->phydev)) {
			dev_err(&pdev->dev, "Unable to get the phy, aborting\n");
			goto out_disable_irq;
		}

		/* Allow the basic features for the phy */
		priv->phydev->irq = PHY_POLL;
		priv->phydev->supported &= PHY_BASIC_FEATURES;
		priv->phydev->advertising = priv->phydev->supported;

		phy_start(priv->phydev);
	} else {
		priv->phydev = NULL;

		ip3912_hw_stop(priv);
		priv->mode = ETN_MODE_FULL_DUPLEX;
		priv->speed = ETN_MBITS_100;
		ip3912_up(dev);
		netif_carrier_on(dev);
		ip3912_print_connection(dev, "");
	}

	printk(KERN_INFO "%s: IP3912 at 0x%08lx using %s phy\n", dev->name,
		priv->base_addr, priv->phy ? priv->phy : "no");

	return 0;

out_disable_irq:
	free_irq(dev->irq, dev);
out_unreg_dev:
	unregister_netdev(dev);
out_iounmap:
	iounmap(priv->base_addr_virt);
out_disable_clocks:
	/* Disable the clocks! */
	clk_disable(priv->clock);
out_free_dev:
	free_netdev(dev);
out:
	platform_set_drvdata(pdev, NULL);
	return ret;
}
/*
 * Use the platform interface to enable multiple instances of this
 * driver
 */
static struct platform_driver ip3912_driver = {
	.probe		= ip3912_probe,
	.remove		= __devexit_p(ip3912_remove),
	.driver		= {
			.name	= "ip3912",
		},
};

static int __init ip3912_init(void)
{
	return platform_driver_register(&ip3912_driver);
}

static void __exit ip3912_exit(void)
{
	platform_driver_unregister(&ip3912_driver);
}

module_init(ip3912_init);
module_exit(ip3912_exit);
