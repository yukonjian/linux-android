/*
 * NXP IP3912 Ethernet driver
 *
 * ip3912_regs.h: Register map for NXP IP3912 ethernet controller
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
#ifndef _IP3912_REGS_H_
#define _IP3912_REGS_H_


/* ------------------------------------
 *  Register offsets from base address
 * ------------------------------------
 */

/* PE-MAC core registers */
#define IP3912_ETN_MAC1				0x0000
#define IP3912_ETN_MAC2				0x0004
#define IP3912_ETN_IPGT				0x0008
#define IP3912_ETN_IPGR				0x000C
#define IP3912_ETN_CLRT				0x0010
#define IP3912_ETN_MAXF				0x0014
#define IP3912_ETN_SUPP				0x0018
#define IP3912_ETN_TEST				0x001C
#define IP3912_ETN_MCFG				0x0020		// Access
#define IP3912_ETN_MCMD				0x0024		// only
#define IP3912_ETN_MADR				0x0028		// through
#define IP3912_ETN_MWTD				0x002C		// first
#define IP3912_ETN_MRDD				0x0030		// ETN
#define IP3912_ETN_MIND				0x0034		// device.
#define IP3912_ETN_SA0				0x0040
#define IP3912_ETN_SA1				0x0044
#define IP3912_ETN_SA2				0x0048
/* Control registers */
#define IP3912_ETN_COMMAND			0x0100
#define IP3912_ETN_STATUS			0x0104
#define IP3912_ETN_RXDESCRIPTOR			0x0108
#define IP3912_ETN_RXSTATUS			0x010C
#define IP3912_ETN_RXDESCRIPTORNUM		0x0110
#define IP3912_ETN_RXPRODUCEINDEX		0x0114
#define IP3912_ETN_RXCONSUMEINDEX		0x0118
#define IP3912_ETN_TXDESCRIPTOR			0x011C
#define IP3912_ETN_TXSTATUS			0x0120
#define IP3912_ETN_TXDESCRIPTORNUM		0x0124
#define IP3912_ETN_TXPRODUCEINDEX		0x0128
#define IP3912_ETN_TXCONSUMEINDEX		0x012C
#define IP3912_ETN_TXRTDESCRIPTOR		0x0130
#define IP3912_ETN_TXRTSTATUS			0x0134
#define IP3912_ETN_TXRTDESCRIPTORNUM		0x0138
#define IP3912_ETN_TXRTPRODUCEINDEX		0x013C
#define IP3912_ETN_TXRTCONSUMEINDEX		0x0140
#define IP3912_ETN_QOSTIMEOUT			0x0148
#define IP3912_ETN_TSV0				0x0158
#define IP3912_ETN_TSV1				0x015C
#define IP3912_ETN_RSV				0x0160
#define IP3912_ETN_FLOWCONTROLCOUNTER		0x0170
#define IP3912_ETN_FLOWCONTROLSTATUS		0x0174
/* RX filter registers */
#define IP3912_ETN_RXFILTERCTRL			0x0200
#define IP3912_ETN_RXFILTERWOLSTATUS		0x0204
#define IP3912_ETN_RXFILTERWOLCLR		0x0208
#define IP3912_ETN_HASHFILTERL			0x0210
#define IP3912_ETN_HASHFILTERH			0x0214
/* Standard registers */
#define IP3912_ETN_INTSTATUS			0x0FE0
#define IP3912_ETN_INTENABLE			0x0FE4
#define IP3912_ETN_INTCLEAR			0x0FE8
#define IP3912_ETN_INTSET			0x0FEC
#define IP3912_ETN_POWERDOWN			0x0FF4
#define IP3912_ETN_MODULEID			0x0FFC


/* -------------------
 *  Register contents
 * -------------------
 */

/* MAC configuration register 1 */
enum IP3912_ETN_REG_MAC1 {
	ETN_MAC1_RX_ENABLE		= 1,
	ETN_MAC1_PASS_ALL_RX		= 1 << 1,
	ETN_MAC1_RX_FLOWCTRL		= 1 << 2,
	ETN_MAC1_TX_FLOWCTRL		= 1 << 3,
	ETN_MAC1_LOOPBACK		= 1 << 4,
	ETN_MAC1_RESET_PETFUN		= 1 << 8,
	ETN_MAC1_RESET_PEMCS_TX		= 1 << 9,
	ETN_MAC1_RESET_PERFUN		= 1 << 10,
	ETN_MAC1_RESET_PEMCS_RX		= 1 << 11,
	ETN_MAC1_SIM_RESET		= 1 << 14,
	ETN_MAC1_SOFT_RESET		= 1 << 15
};

/* MAC configuration register 2 */
enum IP3912_ETN_REG_MAC2 {
	ETN_MAC2_FULL_DUPLEX		= 1,
	ETN_MAC2_FRAMELEN_CHK		= 1 << 1,
	ETN_MAC2_HUGE_FRAME		= 1 << 2,
	ETN_MAC2_DELAYED_CRC		= 1 << 3,
	ETN_MAC2_CRC_ENABLE		= 1 << 4,
	ETN_MAC2_PADCRC_ENABLE		= 1 << 5,
	ETN_MAC2_VLAN_PAD_ENABLE	= 1 << 6,
	ETN_MAC2_AUTO_DETECT_PAD	= 1 << 7,
	ETN_MAC2_PURE_PREAMBLE		= 1 << 8,
	ETN_MAC2_LONG_PREAMBLE		= 1 << 9,
	ETN_MAC2_NO_BACKOFF		= 1 << 12,
	ETN_MAC2_BACKPRESS_NO_BACKOFF	= 1 << 13,
	ETN_MAC2_EXCESS_DEFER		= 1 << 14
};

/* Back-to-Back Inter-Packet-Gap register */
#define ETN_IPGT_B2B_FD_DEFAULT		0x15
#define ETN_IPGT_B2B_HD_DEFAULT		0x12

/* Non Back-to-Back Inter-Packet-Gap register */
#define ETN_IPGR_NB2B_IPGR2_DEFAULT	0X12

/* PHY support register */
enum IP3912_ETN_REG_SUPP {
	ETN_SUPP_BIT_MODE		= 1,
	ETN_SUPP_JABBER_PROTECT		= 1 << 1,
	ETN_SUPP_RESET_PE_10T		= 1 << 3,
	ETN_SUPP_DISABLE_LINK_FAIL	= 1 << 4,
	ETN_SUPP_NO_CIPHER		= 1 << 5,
	ETN_SUPP_FORCE_QUIET		= 1 << 6,
	ETN_SUPP_RESET_PE_100X		= 1 << 7,
	ETN_SUPP_SPEED			= 1 << 8,
	ETN_SUPP_RESET_PE_RMII		= 1 << 11,
	ETN_SUPP_PHY_MODE		= 1 << 12
};

/* MII Management configuration register */
enum IP3912_ETN_REG_MCFG {
	ETN_MCFG_SCAN_INCR		= 1,
	ETN_MCFG_SUPPRESS_PREAMBLE	= 1 << 1,
	ETN_MCFG_CLOCK_SELECT_DIV4	= 1 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV6	= 2 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV8	= 3 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV10	= 4 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV14	= 5 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV20	= 6 << 2,
	ETN_MCFG_CLOCK_SELECT_DIV28	= 7 << 2,
	ETN_MCFG_RESET_MII_MGMT		= 1 << 15
};

/* MII mgmt command register */
#define ETN_MCMD_READ			1

/* MII mgmt address register */
#define ETN_MADR_PHY_ADDR_SHIFT		8

/* MII mgmt read data register */
#define ETN_MRDD_READ_DATA_MASK		0xFFFF

/* MII mgmt indicators register */
#define ETN_MIND_MASK			0x7

/* Station address 0 register */
#define ETN_SA0_STATION_ADR1_SHIFT	8
#define ETN_SA0_STATION_ADR1_MASK	0xFF00
#define ETN_SA0_STATION_ADR2_MASK	0xFF

/* Station address 1 register */
#define ETN_SA1_STATION_ADR3_SHIFT	8
#define ETN_SA1_STATION_ADR3_MASK	0xFF00
#define ETN_SA1_STATION_ADR4_MASK	0xFF

/* Station address 2 register */
#define ETN_SA2_STATION_ADR5_SHIFT	8
#define ETN_SA2_STATION_ADR5_MASK	0xFF00
#define ETN_SA2_STATION_ADR6_MASK	0xFF

/* Command register */
enum IP3912_ETN_REG_CMD {
	ETN_CMD_RX_ENABLE		= 1,
	ETN_CMD_TX_ENABLE		= 1 << 1,
	ETN_CMD_TXRT_ENABLE		= 1 << 2,
	ETN_CMD_REG_RESET		= 1 << 3,
	ETN_CMD_TX_RESET		= 1 << 4,
	ETN_CMD_RX_RESET		= 1 << 5,
	ETN_CMD_PASS_RUNT_FRAME		= 1 << 6,
	ETN_CMD_PASS_RX_FILTER		= 1 << 7,
	ETN_CMD_TX_FLOW_CTRL		= 1 << 8,
	ETN_CMD_RMII			= 1 << 9,
	ETN_CMD_FULL_DUPLEX		= 1 << 10,
	ETN_CMD_ENABLE_QOS		= 1 << 11,
};

#define	ETN_INDEX_MASK			0xFFFF

/* Receive filter control register */
enum IP3912_ETN_REG_RXFILTERCTRL {
	ETN_RXFILTERCTRL_UNICAST	= 1,
	ETN_RXFILTERCTRL_BROADCAST	= 1 << 1,
	ETN_RXFILTERCTRL_MULTICAST	= 1 << 2,
	ETN_RXFILTERCTRL_UNICAST_HASH	= 1 << 3,
	ETN_RXFILTERCTRL_MULTICAST_HASH	= 1 << 4,
	ETN_RXFILTERCTRL_PERFECT	= 1 << 5,
	ETN_RXFILTERCTRL_MAGIC_PACKET	= 1 << 12,
	ETN_RXFILTERCTRL_RX_FILTER_WOL	= 1 << 13,
};


/* Interrupt status register */
enum IP3912_ETN_REG_INTSTATUS {
	ETN_INTSTATUS_RX_OVERRUN	= 1,
	ETN_INTSTATUS_RX_ERROR		= 1 << 1,
	ETN_INTSTATUS_RX_FINISHED	= 1 << 2,
	ETN_INTSTATUS_RX_DONE		= 1 << 3,
	ETN_INTSTATUS_TX_UNDERRUN	= 1 << 4,
	ETN_INTSTATUS_TX_ERROR		= 1 << 5,
	ETN_INTSTATUS_TX_FINISHED	= 1 << 6,
	ETN_INTSTATUS_TX_DONE		= 1 << 7,
	ETN_INTSTATUS_TXRT_UNDERRUN	= 1 << 8,
	ETN_INTSTATUS_TXRT_ERROR	= 1 << 9,
	ETN_INTSTATUS_TXRT_FINISHED	= 1 << 10,
	ETN_INTSTATUS_TXRT_DONE		= 1 << 11,
	ETN_INTSTATUS_SOFT_INT		= 1 << 12,
	ETN_INTSTATUS_WAKEUP		= 1 << 13,
};

/* Interrupt enable register */
enum IP3912_ETN_REG_INTENABLE {
	ETN_INTENABLE_RX_OVERRUN	= 1,
	ETN_INTENABLE_RX_ERROR		= 1 << 1,
	ETN_INTENABLE_RX_FINISHED	= 1 << 2,
	ETN_INTENABLE_RX_DONE		= 1 << 3,
	ETN_INTENABLE_TX_UNDERRUN	= 1 << 4,
	ETN_INTENABLE_TX_ERROR		= 1 << 5,
	ETN_INTENABLE_TX_FINISHED	= 1 << 6,
	ETN_INTENABLE_TX_DONE		= 1 << 7,
	ETN_INTENABLE_TXRT_UNDERRUN	= 1 << 8,
	ETN_INTENABLE_TXRT_ERROR	= 1 << 9,
	ETN_INTENABLE_TXRT_FINISHED	= 1 << 10,
	ETN_INTENABLE_TXRT_DONE		= 1 << 11,
	ETN_INTENABLE_SOFT_INT		= 1 << 12,
	ETN_INTENABLE_WAKEUP		= 1 << 13,
};

/* Interrupt clear register */
enum IP3912_ETN_REG_INTCLEAR {
	ETN_INTCLEAR_RX_OVERRUN	= 1,
	ETN_INTCLEAR_RX_ERROR		= 1 << 1,
	ETN_INTCLEAR_RX_FINISHED	= 1 << 2,
	ETN_INTCLEAR_RX_DONE		= 1 << 3,
	ETN_INTCLEAR_RX_ALL		= 0xF,
	ETN_INTCLEAR_TX_UNDERRUN	= 1 << 4,
	ETN_INTCLEAR_TX_ERROR		= 1 << 5,
	ETN_INTCLEAR_TX_FINISHED	= 1 << 6,
	ETN_INTCLEAR_TX_DONE		= 1 << 7,
	ETN_INTCLEAR_TX_ALL		= 0xF0,
	ETN_INTCLEAR_TXRT_UNDERRUN	= 1 << 8,
	ETN_INTCLEAR_TXRT_ERROR		= 1 << 9,
	ETN_INTCLEAR_TXRT_FINISHED	= 1 << 10,
	ETN_INTCLEAR_TXRT_DONE		= 1 << 11,
	ETN_INTCLEAR_SOFT_INT		= 1 << 12,
	ETN_INTCLEAR_WAKEUP		= 1 << 13,
	ETN_INTCLEAR_ALL		= 0x3FFF
};


#endif /* _IP3912_REGS_H_ */
