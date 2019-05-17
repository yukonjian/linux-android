/*
 * NXP IP3912 Ethernet driver
 *
 * ip3912_hw.c: Functions for performing HW access to the NXP IP3912
 * ethernet controller
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

#include <linux/mii.h>
#include <linux/delay.h>

#include "ip3912_hw.h"
#include "ip3912.h"

/* Do a full reset of the HW. This is only done at initialization time of
   the driver. */
int ip3912_hw_reset(ip3912_priv_t *priv)
{
	/* Reset RMII and 10/100 Mbit parts of the MAC. */
	IP3912_WRITE_REG(priv, SUPP, ETN_SUPP_PHY_MODE |
				ETN_SUPP_RESET_PE_RMII |
				ETN_SUPP_RESET_PE_100X |
				ETN_SUPP_RESET_PE_10T);

	/* Reset PE-MAC. */
	IP3912_WRITE_REG(priv, MAC1, ETN_MAC1_SOFT_RESET |
					ETN_MAC1_RESET_PEMCS_RX |
					ETN_MAC1_RESET_PERFUN |
					ETN_MAC1_RESET_PEMCS_TX |
					ETN_MAC1_RESET_PETFUN);

	/* Reset all data paths and the host registers. */
	IP3912_WRITE_REG(priv, COMMAND, ETN_CMD_REG_RESET |
					ETN_CMD_TX_RESET |
					ETN_CMD_RX_RESET);

	/* Remove SoftReset Condition. */
	IP3912_WRITE_REG(priv, MAC1, 0);
	return 0;
}


/* Only set and clear some RX reset bits. This function expects that the RX
   data path and DMA engine has been disabled before calling us. Therefore
   the corresponding bits of the given register values must be cleared. */
static inline void ip3912_hw_reset_rx(ip3912_priv_t *priv, uint32_t mac1_reg,
							uint32_t cmd_reg)
{
	/* Reset RX, step 1. */
	IP3912_WRITE_REG(priv, MAC1, mac1_reg | ETN_MAC1_RESET_PEMCS_RX);

	/* Reset RX, step 2. (self-clearing bit) */
	IP3912_WRITE_REG(priv, COMMAND, cmd_reg | ETN_CMD_RX_RESET);

	/* Clear RX reset bit. */
	IP3912_WRITE_REG(priv, MAC1, mac1_reg);
}

/* Stop the HW. Used when stopping the network interface. */
void ip3912_hw_stop(ip3912_priv_t *priv)
{
	uint32_t mac1_reg, cmd_reg;

	/* Disable Interrupts. */
	IP3912_WRITE_REG(priv, INTENABLE, 0);

	/* Save current registers' values. */
	mac1_reg = IP3912_READ_REG(priv, MAC1);
	cmd_reg = IP3912_READ_REG(priv, COMMAND);

	/* Disable RX data path. */
	mac1_reg &= ~ETN_MAC1_RX_ENABLE;
	IP3912_WRITE_REG(priv, MAC1, mac1_reg);

	/* Disable RX and TX DMA engines. */
	cmd_reg &= ~(ETN_CMD_RX_ENABLE | ETN_CMD_TX_ENABLE);
	IP3912_WRITE_REG(priv, COMMAND, cmd_reg);

	ip3912_hw_reset_rx(priv, mac1_reg, cmd_reg);

	/* Clear all possibly still pending interrupts. */
	ip3912_hw_clear_intstatus(priv);
}

void ip3912_hw_set_mac_addr(struct net_device *dev)
{
	ip3912_priv_t	*priv = netdev_priv(dev);

	IP3912_WRITE_REG(priv, SA0, dev->dev_addr[5] <<
			       ETN_SA0_STATION_ADR1_SHIFT | dev->dev_addr[4]);
	IP3912_WRITE_REG(priv, SA1, dev->dev_addr[3] <<
			       ETN_SA1_STATION_ADR3_SHIFT | dev->dev_addr[2]);
	IP3912_WRITE_REG(priv, SA2, dev->dev_addr[1] <<
			       ETN_SA2_STATION_ADR5_SHIFT | dev->dev_addr[0]);
}

void ip3912_hw_retrieve_mac_addr(struct net_device *dev)
{
	ip3912_priv_t	*priv = netdev_priv(dev);
	uint32_t	sa;

	sa = IP3912_READ_REG(priv, SA0);
	dev->dev_addr[5] = (uint8_t)((sa & ETN_SA0_STATION_ADR1_MASK) >>
						ETN_SA0_STATION_ADR1_SHIFT);
	dev->dev_addr[4] = (uint8_t)(sa & ETN_SA0_STATION_ADR2_MASK);

	sa = IP3912_READ_REG(priv, SA1);
	dev->dev_addr[3] = (uint8_t)((sa & ETN_SA1_STATION_ADR3_MASK) >>
						ETN_SA1_STATION_ADR3_SHIFT);
	dev->dev_addr[2] = (uint8_t)(sa & ETN_SA1_STATION_ADR4_MASK);

	sa = IP3912_READ_REG(priv, SA2);
	dev->dev_addr[1] = (uint8_t)((sa & ETN_SA2_STATION_ADR5_MASK) >>
						ETN_SA2_STATION_ADR5_SHIFT);
	dev->dev_addr[0] = (uint8_t)(sa & ETN_SA2_STATION_ADR6_MASK);
}

void ip3912_hw_set_max_frame_size(ip3912_priv_t *priv)
{
	IP3912_WRITE_REG(priv, MAXF, priv->rx_buf_size);
}

int ip3912_hw_init(struct net_device *dev)
{
	ip3912_priv_t	*priv = netdev_priv(dev);
	uint32_t regval = 0;

/*	if (ip3912_hw_init_phy(priv))
		return -EIO;
*/
	/* Init command register: enable RMII mode, set duplex mode
	   and whether filtering is done in HW or SW. */
	regval = ETN_CMD_RMII;
	if (priv->mode == ETN_MODE_FULL_DUPLEX)
		regval |= ETN_CMD_FULL_DUPLEX;
#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
	regval |= ETN_CMD_PASS_RUNT_FRAME;
#endif
	IP3912_WRITE_REG(priv, COMMAND, regval);

	/* Init MAC1 register: Flow control */
	regval = 0;
	if (priv->flow_ctrl && ETN_TX_FLOW_CONTROL)
		regval |= ETN_MAC1_TX_FLOWCTRL;
	if (priv->flow_ctrl && ETN_RX_FLOW_CONTROL)
		regval |= ETN_MAC1_RX_FLOWCTRL;
	IP3912_WRITE_REG(priv, MAC1, regval);

	/* Init MAC2 register: enable HW CRC and padding of short frames,
	   select duplex mode. */
	regval = ETN_MAC2_CRC_ENABLE | ETN_MAC2_PADCRC_ENABLE;
#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
	regval |= ETN_MAC2_VLAN_PAD_ENABLE | ETN_MAC2_AUTO_DETECT_PAD;
#endif
	if (priv->mode == ETN_MODE_FULL_DUPLEX)
		regval |= ETN_MAC2_FULL_DUPLEX;
	IP3912_WRITE_REG(priv, MAC2, regval);

	/* Init IPGT register */
	regval = priv->mode == ETN_MODE_FULL_DUPLEX ?
						ETN_IPGT_B2B_FD_DEFAULT :
						ETN_IPGT_B2B_HD_DEFAULT;
	IP3912_WRITE_REG(priv, IPGT, regval);

	/* Init IPGR register */
	IP3912_WRITE_REG(priv, IPGR, ETN_IPGR_NB2B_IPGR2_DEFAULT);

	/* Init SUPP register */
	regval = ETN_SUPP_PHY_MODE;
	if (priv->speed == ETN_MBITS_100)
		regval |= ETN_SUPP_SPEED;
	IP3912_WRITE_REG(priv, SUPP, regval);

	/* Init RXFILTERCTRL register */
	if (!priv->mc_list_set)
		ip3912_hw_normal_rx_op(priv);

	ip3912_hw_set_max_frame_size(priv);

	/* PRELIMINARY. As the station address registers which hold the MAC
	   address are zeroed by a reset these registers must be newly
	   initialized. */
	ip3912_hw_set_mac_addr(dev);

	return 0;
}

/* Inform the ETN DMA engine where to find RX and TX buffers in memory. */
void ip3912_hw_setup_dma_descriptors(ip3912_priv_t *priv, unsigned int desc)
{
	desc--;

	/* TX */
	IP3912_WRITE_REG(priv, TXDESCRIPTOR, priv->dma_tx_descr);
	IP3912_WRITE_REG(priv, TXSTATUS, priv->dma_tx_status);
	IP3912_WRITE_REG(priv, TXDESCRIPTORNUM, desc);

	/* RX */
	IP3912_WRITE_REG(priv, RXDESCRIPTOR, priv->dma_rx_descr);
	IP3912_WRITE_REG(priv, RXSTATUS, priv->dma_rx_status);
	IP3912_WRITE_REG(priv, RXDESCRIPTORNUM, desc);
}


/* Declare TX FIFO as empty. */
static inline void ip3912_hw_empty_tx_fifo(ip3912_priv_t *priv)
{
	uint32_t regval = 0;

	regval = ip3912_hw_get_txconsumeindex(priv);
	IP3912_WRITE_REG(priv, TXPRODUCEINDEX, regval);
	priv->txproduceindex = regval;
	priv->txconsumeindex = regval;
}


/* Enable both the RX and TX data paths. */
static inline void ip3912_hw_enable_data_paths(ip3912_priv_t *priv)
{
	uint32_t regval = 0;

	/* Declare TX FIFO as empty. */
	ip3912_hw_empty_tx_fifo(priv);

	/* Enable the RX and TX DMA engines. */
	regval = IP3912_READ_REG(priv, COMMAND);
	regval |= (ETN_CMD_RX_ENABLE | ETN_CMD_TX_ENABLE);
	IP3912_WRITE_REG(priv, COMMAND, regval);

	/*  Enable the RX data path. */
	regval = IP3912_READ_REG(priv, MAC1);
	regval |= ETN_MAC1_RX_ENABLE;
	IP3912_WRITE_REG(priv, MAC1, regval);
}


void ip3912_hw_start(ip3912_priv_t *priv)
{
	ip3912_hw_enable_interrupts(priv);
	ip3912_hw_enable_data_paths(priv);
}


int ip3912_hw_is_txfifo_full(ip3912_priv_t *priv, unsigned int desc)
{
	uint32_t	txconsumeindex;
	int		index_diff;

	txconsumeindex = ip3912_hw_get_txconsumeindex(priv);

	index_diff = priv->txproduceindex + 1 - txconsumeindex;

	if (index_diff == 0 || index_diff == desc)
		return 1;

	return 0;
}

void ip3912_hw_reset_tx(ip3912_priv_t *priv)
{
	uint32_t cmd_reg = 0;

	/* Disable and reset TX DMA engine. */
	cmd_reg = IP3912_READ_REG(priv, COMMAND);
	cmd_reg = (cmd_reg & ~ETN_CMD_TX_ENABLE) | ETN_CMD_TX_RESET;
	IP3912_WRITE_REG(priv, COMMAND, cmd_reg);

	/* Clear TX done interrupt. */
	IP3912_WRITE_REG(priv, INTCLEAR, ETN_INTCLEAR_TX_DONE);

	/* Declare TX FIFO as empty. */
	ip3912_hw_empty_tx_fifo(priv);

	/* Enable TX DMA engine. */
	cmd_reg = (cmd_reg & ~ETN_CMD_TX_RESET) | ETN_CMD_TX_ENABLE;
	IP3912_WRITE_REG(priv, COMMAND, cmd_reg);
}


