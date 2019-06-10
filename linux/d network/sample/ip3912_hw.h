/*
 * NXP IP3912 Ethernet driver
 *
 * ip3912_hw.h: Macros and function definitions for performing HW access to
 * the NXP IP3912 ethernet controller
 *
 * Copyright (C) 2007 Sebastian Smolorz <ssm@emlix.com>, emlix GmbH
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _IP3912_HW_H_
#define _IP3912_HW_H_

#include <asm/io.h>

#include "ip3912_regs.h"
#include "ip3912.h"
#include "ip3912_cfg.h"


#define IP3912_READ_REG(priv, reg)					\
	__raw_readl((priv)->base_addr_virt + IP3912_ETN_##reg)

#define IP3912_WRITE_REG(priv, reg, val)				\
	__raw_writel(val, (priv)->base_addr_virt + IP3912_ETN_##reg)

#define IP3912_WRITE_MII_REG(reg, val)					\
	__raw_writel(val, etn_base_addr_mii + IP3912_ETN_##reg)

#define IP3912_READ_MII_REG(reg)					\
	__raw_readl(etn_base_addr_mii + IP3912_ETN_##reg)


#define IP3912_PHY_ADDR_MASK	0x1f
#define IP3912_PHY_REG_MASK	0x1f


extern int ip3912_hw_reset(ip3912_priv_t *priv);

extern int ip3912_hw_init(struct net_device *dev);
extern void ip3912_hw_setup_dma_descriptors(ip3912_priv_t *priv,
						unsigned int desc);

extern void ip3912_hw_set_mac_addr(struct net_device *dev);
extern void ip3912_hw_retrieve_mac_addr(struct net_device *dev);

extern void ip3912_hw_set_max_frame_size(ip3912_priv_t *priv);

extern void ip3912_hw_start(ip3912_priv_t *priv);
extern void ip3912_hw_stop(ip3912_priv_t *priv);

extern int ip3912_hw_is_txfifo_full(ip3912_priv_t *priv, unsigned int desc);

extern void ip3912_hw_reset_tx(ip3912_priv_t *priv);
extern void ip3912_hw_reset_rx_overrun(ip3912_priv_t *priv);


extern void ip3912_mii_init_spinlock(void);

extern u16 ip3912_hw_mii_mdio_transfer(ip3912_priv_t *priv, int dir,
					u16 phy_addr, u16 addr, u16 data);

extern void ip3912_hw_mii_mdio_write(struct net_device *dev, int phy,
						int reg, int val);

extern int ip3912_hw_mii_mdio_read(struct net_device *dev, int phy, int reg);


static inline void ip3912_hw_set_txproduceindex(ip3912_priv_t *priv,
						uint32_t idx)
{
	IP3912_WRITE_REG(priv, TXPRODUCEINDEX, idx);
}

static inline uint32_t ip3912_hw_get_txconsumeindex(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, TXCONSUMEINDEX) & ETN_INDEX_MASK;
}

static inline uint32_t ip3912_hw_get_rxproduceindex(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, RXPRODUCEINDEX) & ETN_INDEX_MASK;
}

static inline uint32_t ip3912_hw_get_rxconsumeindex(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, RXCONSUMEINDEX) & ETN_INDEX_MASK;
}

static inline void ip3912_hw_set_rxconsumeindex(ip3912_priv_t *priv,
						uint32_t idx)
{
	IP3912_WRITE_REG(priv, RXCONSUMEINDEX, idx);
}


/*
 * R/W interrupt registers
 */

static inline void ip3912_hw_enable_interrupts(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTENABLE, IP3912_IRQS_ENABLE);
}

static inline uint32_t ip3912_hw_get_intstatus(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, INTSTATUS);
}

static inline void ip3912_hw_clear_intstatus(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_ALL);
}

static inline void ip3912_hw_clear_intstatus_rx(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_RX_ALL);
}

static inline void ip3912_hw_clear_intstatus_tx(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_TX_ALL);
}

#ifdef CONFIG_IP3912_NAPI
#ifdef CONFIG_IP3912_TX_NAPI
static inline void ip3912_hw_disable_and_clear_ints(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTENABLE, 0);
	ip3912_hw_clear_intstatus(priv);
}

static inline void ip3912_hw_disable_and_clear_rx_ints(ip3912_priv_t *priv)
{
	uint32_t intenable = IP3912_READ_REG(priv, INTENABLE);
	intenable &= ~IP3912_RX_IRQS_ENABLE;
	IP3912_WRITE_REG(priv, INTENABLE, intenable);
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_RX_ALL);
}

static inline void ip3912_hw_disable_and_clear_tx_ints(ip3912_priv_t *priv)
{
	uint32_t intenable = IP3912_READ_REG(priv, INTENABLE);
	intenable &= ~IP3912_TX_IRQS_ENABLE;
	IP3912_WRITE_REG(priv, INTENABLE, intenable);
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_TX_ALL);
}
#else
static inline void ip3912_hw_disable_and_clear_rx_ints(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, INTENABLE, IP3912_TX_IRQS_ENABLE);
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_RX_ALL);
}
#endif

static inline uint32_t ip3912_hw_get_intenable(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, INTENABLE);
}
#endif


/* Accept unicast (only our address) and broadcast but no multicast. */
static inline void ip3912_hw_normal_rx_op(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, RXFILTERCTRL, ETN_RXFILTERCTRL_BROADCAST |
						ETN_RXFILTERCTRL_PERFECT);
}

/* Instruct HW to receive each and every packet. */
static inline void ip3912_hw_promisc_mode(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, RXFILTERCTRL, ETN_RXFILTERCTRL_UNICAST |
						ETN_RXFILTERCTRL_BROADCAST |
						ETN_RXFILTERCTRL_MULTICAST);
}

/* Don't filter multicast packets, receive them all. */
static inline void ip3912_hw_all_multi(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, RXFILTERCTRL, ETN_RXFILTERCTRL_BROADCAST |
						ETN_RXFILTERCTRL_MULTICAST |
						ETN_RXFILTERCTRL_PERFECT);
}

/* Set up the multicast hash filter according to the given arguments. */
static inline void ip3912_hw_multicast(ip3912_priv_t *priv,
					uint32_t hash_l, uint32_t hash_h)
{
	IP3912_WRITE_REG(priv, RXFILTERCTRL, ETN_RXFILTERCTRL_MULTICAST_HASH |
						ETN_RXFILTERCTRL_BROADCAST |
						ETN_RXFILTERCTRL_PERFECT);
	IP3912_WRITE_REG(priv, HASHFILTERL, hash_l);
	IP3912_WRITE_REG(priv, HASHFILTERH, hash_h);
}


static inline uint32_t ip3912_hw_get_rsv(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, RSV);
}

static inline uint32_t ip3912_hw_get_tsv0(ip3912_priv_t *priv)
{
	return IP3912_READ_REG(priv, TSV0);
}


#endif /* _IP3912_HW_H_ */
