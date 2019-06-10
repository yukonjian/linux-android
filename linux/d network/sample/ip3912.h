/*
 * NXP IP3912 Ethernet driver
 *
 * ip3912_hw.h: main header file, defining private structure for net_device
 *		and structures for the ETN DMA descriptors and statuses
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
 */
#ifndef _IP3912_H_
#define _IP3912_H_

#include <linux/timer.h>
#include <linux/phy.h>
#include <linux/netdevice.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/semaphore.h>


#define DRV_NAME	"ip3912"
#define DRV_VERSION	"2.6.0"
#define DRV_RELDATE	"2007-08-29"


/* Different device state flags, used for flags in ip3912_priv_t. */
#define	IP3912_FLAG_TX_FIFO_FULL	0x01
#define IP3912_FLAG_CHECK_TX_DMA	0x02


typedef struct {
	/* size of the frame to be transmitted */
	uint32_t size:		11;
	uint32_t :		15;
	/* override the PE-MAC internal register values */
	uint32_t override:	1;
	/* huge frame enabling */
	uint32_t huge:		1;
	/* pad the short length frame to 64 bytes */
	uint32_t pad:		1;
	/* calculate the CRC and append for this frame */
	uint32_t crc:		1;
	/* last fragment in the fragmented frames */
	uint32_t last:		1;
	/* generate an interrupt when this frame is transmitted */
	uint32_t interrupt:	1;
} tx_control_t;

typedef struct {
	/* maximum size of the frame to be received */
	uint32_t size:		11;
	uint32_t :		20;
	/* generate an interrupt when frame is received */
	uint32_t interrupt:	1;
} rx_control_t;

typedef struct {
	uint32_t :			21;
	/* collision count */
	uint32_t collision_cnt:		4;
	/* Transmission is deferred because medium was occupied (no error). */
	uint32_t defer:			1;
	/* Transmission exceeded the maximum deferral limit and was aborted. */
	uint32_t excessive_defer:	1;
	/* excessive collision (FATAL) */
	uint32_t excessive_collision:	1;
	/* late collision (FATAL) */
	uint32_t late_collision:	1;
	/* underrun error (FATAL) */
	uint32_t underrun:		1;
	/* descriptor is not present */
	uint32_t no_descriptor:		1;
	/* error occurred during transmission */
	uint32_t error:			1;
} tx_status_t;


typedef struct {
	/* received frame size */
	uint32_t size:			11;
	uint32_t :			7;
	/* received frame is control frame */
	uint32_t control_frame:		1;
	/* received frame is VLAN frame */
	uint32_t vlan_frame:		1;
	/* received frame is failed to pass hardware filter */
	uint32_t fail_filter:		1;
	/* received frame is multicast frame */
	uint32_t multicast_frame:	1;
	/* received frame is broadcast frame */
	uint32_t broadcast_frame:	1;
	/* error in CRC */
	uint32_t crc_error:		1;
	/* symbol error in PHY */
	uint32_t symbol_error:		1;
	/* frame length error */
	uint32_t len_error:		1;
	/* received packet exceeds max size */
	uint32_t range_error:		1;
	/* alignment error */
	uint32_t alignment_error:	1;
	/* Rx overrun error */
	uint32_t overrun:		1;
	/* descriptor is not found */
	uint32_t no_descriptor:		1;
	/* this frame is the last fragment in the fragmented frames */
	uint32_t last_frag:		1;
	/* error is occurred during reception */
	uint32_t error:			1;
} rx_status_info_t;

#define IP3912_RX_STATUS_INFO_ERRMASK		0x13800000

typedef struct {
	/* hash value for SA */
	uint32_t sa_hash_crc:	9;
	uint32_t :		7;
	/* hash value for DA */
	uint32_t da_hash_crc:	9;
	uint32_t :		7;
} rx_status_hash_crc_t;


typedef struct {
	rx_status_info_t	info;
	rx_status_hash_crc_t	hash_crc;
} rx_status_t;


typedef struct {
	uint32_t	packet;		/* address of the ethernet packet */
	tx_control_t	ctrl;		/* control address for Tx packet */
} tx_descr_t;

typedef struct {
	uint32_t	packet;		/* address of the ethernet packet */
	rx_control_t	ctrl;		/* control address for Rx packet */
} rx_descr_t;


/*
 * ip3912 private structure
 */
typedef struct ip3912_priv {
	/* physical base address of ethernet device */
	unsigned long		base_addr;
	/* mapped base address after ioremap() */
	void			*base_addr_virt;
	/* name of the corresponding PHY. */
	const char		*phy;
	unsigned int		phy_addr; /* To go away */
	struct phy_device	*phydev;
	/* MII interface */
	struct mii_if_info	mii;
	/* MDIO Bus */
	struct mii_bus *mii_bus;
	/* NAPI infrastucture */
	struct napi_struct napi;

	/* Pointer to our device */
	struct net_device *dev;
	struct platform_device *pdev;

	/* Clocking */
	struct clk *clock;

	/* Physical base address of DMA-capable memory region used by TX/RX
	   descriptors and status fields. */
	dma_addr_t 		dma_descr_status;
	/* Virtual base address of allocated memory for the TX/RX descriptors
	   and status fields. */
	void			*mem_descr_status;

	/* Physical TX descriptor array base address. */
	dma_addr_t  		dma_tx_descr;
	/* Physical TX status array base address. */
	dma_addr_t  		dma_tx_status;
	/* TX descriptor array */
	tx_descr_t		*tx_descr;
	/* TX status array */
	tx_status_t		*tx_status;

	/* Physical RX descriptor array base address. */	
	dma_addr_t  		dma_rx_descr;
	/* Physical RX status array base address. */
	dma_addr_t  		dma_rx_status;
	/* RX descriptor array */
	rx_descr_t		*rx_descr;
	/* RX status array */
	rx_status_t		*rx_status;

	/* Array of pointers to every RX data buffer. */
        struct sk_buff          **rx_skbs;

	/* Array of pointers to skbs which were handed over to the TX HW but
	   not processed yet. */
	struct sk_buff		**tx_skbs;

	/* current value of register TXPRODUCEINDEX */
	uint32_t		txproduceindex;
	/* The value of txconsumeindex is set to the current value of the
	   register TXCONSUMEINDEX in two situations:
	   1. at opening time of the interface;
	   2. after having processed all TX descriptors consumed by the DMA
	      engine in the ISR.*/
	uint32_t		txconsumeindex;

	/* speed setting 10/100/1000 */
	unsigned int		speed;
	/* mode setting Full Duplex, Half Duplex */
	unsigned int		mode;
	/* auto negotiation enable/disable */
	unsigned int		auto_neg;
	/* TX/RX flow control enabled/disabled */
	unsigned int		flow_ctrl;
	/* indicates whether set_multicast_list() was called at least once */
	unsigned int		mc_list_set;

	/* holds the maximum RX buf size */
	uint32_t		rx_buf_size;

	/* timer for probing the link status */
//	struct timer_list	phy_timer;
	/* status (counters) structure */
	struct net_device_stats stats;

	/* serialize access to this structure */
	spinlock_t		lock;
	/* This semaphore is for the case when the interface is about to be
	   brought down but TX DMA transfers are outstanding. As long as the
	   DMA transfer are in progress this semaphore prevents deactivating
	   the interface. */
	struct semaphore	txsem_ifdown;

	/* flags for different device states */
	volatile unsigned long	flags;

	/* counter which indicates how many descriptors don't point to a valid
	   skb data area */
	unsigned int		lost_desc;
} ip3912_priv_t;


extern void *etn_base_addr_mii;

/* MDIO init functions */
int ip3912_mii_init(struct ip3912_priv *priv, struct ip3912_priv *first_intf);

#endif /* _IP3912_H_ */
