/*
 * NXP IP3912 Ethernet driver
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
#ifndef _IP3912_CFG_H_
#define _IP3912_CFG_H_

#include "ip3912_regs.h"


/* default config values for the Firetux board */

#define IP3912_ETN_PORTS	2

#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
#define IP3912_DESCR_QUEUE_LEN	6
#else
#define IP3912_DESCR_QUEUE_LEN	192
#endif

#define IP3912_BASEADDR_ETN1	0xC1600000
#define IP3912_BASEADDR_ETN2	0xC1700000
#define IP3912_ETN_IOMEM_SIZE	0x00100000	// 1 Mbyte

#define IP3912_IRQ_ETN1		22
#define IP3912_IRQ_ETN2		21

#ifdef CONFIG_IP3912_USE_SCRAM_FOR_DATA
// Each packet is of size 1792 (0x700) bytes.
#define IP3912_SCRAM_PACKET_BASE PNX8181_SCRAM_VA_DEV + 0x0002C000 - (IP3912_DESCR_QUEUE_LEN*0xE00)
#define IP3912_SCRAM_PACKET_SIZE IP3912_DESCR_QUEUE_LEN*0xE00
#endif

#ifdef CONFIG_IP3912_USE_SCRAM
#define	IP3912_SCRAM_BASE	PNX8181_SCRAM_BASE + 0x0002C000
#define IP3912_SCRAM_BASE_VA	PNX8181_SCRAM_VA_DEV + 0x0002C000
#define IP3912_SCRAM_SIZE	0x3000				// 12 KByte
#define IP3912_SCRAM_PER_ETN	0x1800
#endif

/* General ethernet configuration options */

#define ETN_MBITS_100 			100
#define ETN_MBITS_10 			10

#define ETN_MODE_FULL_DUPLEX		1
#define ETN_MODE_HALF_DUPLEX		0

#define ETN_FLOW_CONTROL_DISABLE	0x0
#define ETN_TX_FLOW_CONTROL		0x1
#define ETN_RX_FLOW_CONTROL		0x2
#define ETN_FLOW_CONTROL_ENABLE		(ETN_TX_FLOW_CONTROL |		\
					 ETN_RX_FLOW_CONTROL)

#define ETN_AUTONEG_ENABLE		1
#define ETN_AUTONEG_DISABLE		0

#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
#define MAX_ETH_FRAME_SIZE		(1536 + VLAN_HLEN)
#else
#define MAX_ETH_FRAME_SIZE		1536
#endif
#define ETN_HEADER_SIZE			MAX_ETH_FRAME_SIZE - ETH_DATA_LEN


/* Define which ETN interrupts are enabled:
	- when an TX descriptor was processed
	- when an RX descriptor was processed
	- when an RX error was reported
 */
#define	IP3912_RX_IRQS_ENABLE		(ETN_INTENABLE_RX_DONE	|	\
					ETN_INTENABLE_RX_ERROR	|	\
					ETN_INTENABLE_RX_OVERRUN)

#define	IP3912_TX_IRQS_ENABLE		ETN_INTENABLE_TX_DONE

#define	IP3912_IRQS_ENABLE		IP3912_RX_IRQS_ENABLE |		\
					IP3912_TX_IRQS_ENABLE

#endif /* _IP3912_CFG_H_ */
