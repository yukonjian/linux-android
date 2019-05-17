/*
 * IP3912 MDIO Bus Interface
 *
 * written by Sebastian HeÃ <sh@emlix.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/phy.h>
#include <net/ip3912.h>
#include <asm/io.h>

#include "ip3912.h"
#include "ip3912_regs.h"
/*
 * Register offsets agains the base_addr
 */
#define IP3912_MAC1	0x00
#define IP3912_SUPP	0x18
#define IP3912_MCFG	0x20
#define IP3912_MCMD	0x24
#define IP3912_MADR	0x28
#define IP3912_MWTD	0x2C
#define IP3912_MRDD	0x30
#define IP3912_MIND	0x34
#define IP3912_CMD	0x100
#define IP3912_BUSY	0x7

/* These macros need priv to be valid */
#define SET_ADDR(phy, phyreg) \
	__raw_writel((u32)((phy << ETN_MADR_PHY_ADDR_SHIFT) | phyreg), \
	priv->base_addr_virt + IP3912_MADR)

#define PHY_RW_TIMEOUT_10NS 1200

/* Read from the PHY, this function is called with mdio_lock held */
static int ip3912_mdio_read(struct mii_bus *bus, int phy, int regnum)
{
	struct ip3912_priv *priv = bus->priv;
	int i;
	int value;
	int state;

	/* Set the phy address */
	SET_ADDR(phy, regnum);

	/* Trigger a read command */
	__raw_writel(ETN_MCMD_READ, priv->base_addr_virt + IP3912_MCMD);

	for (i = 0; (state = (__raw_readl(priv->base_addr_virt + IP3912_MIND) & ETN_MIND_MASK)) &&
				i < PHY_RW_TIMEOUT_10NS; i++) {
		ndelay(10);
	}

	/* Read the value */
	value = __raw_readl(priv->base_addr_virt + IP3912_MRDD);

	/* Disable reading */
	__raw_writel(0x00, priv->base_addr_virt + IP3912_MCMD);

	if (state)
		value = 0xffff;

	return value;
}

static int ip3912_mdio_write(struct mii_bus *bus, int phy, int regnum,
				u16 value)
{
	int i;
	int state;
	struct ip3912_priv *priv = bus->priv;

	/* Set the phy address */
	SET_ADDR(phy, regnum);

	/* Write the data out */
	__raw_writel(value, priv->base_addr_virt + IP3912_MWTD);

	/* wait for completion of read cycle */
	for (i = 0; (state = (__raw_readl(priv->base_addr_virt + IP3912_MIND) & ETN_MIND_MASK) &&
			    i < PHY_RW_TIMEOUT_10NS); i++)
		ndelay(10);

	if (state)
		return -ENODEV;

	return 0;
}

/*
 * This functions should reset the complete bus, by now it only resets the
 * management core
 */
static int ip3912_mdio_reset(struct mii_bus *bus)
{
	struct ip3912_priv *priv = bus->priv;

	/* Reset RMII and 10/100 Mbit parts of the MAC. */
	__raw_writel(ETN_SUPP_PHY_MODE | ETN_SUPP_RESET_PE_RMII
			| ETN_SUPP_RESET_PE_100X | ETN_SUPP_RESET_PE_10T,
			priv->base_addr_virt + IP3912_SUPP);

	__raw_writel(ETN_MAC1_SOFT_RESET | ETN_MAC1_RESET_PEMCS_RX
			| ETN_MAC1_RESET_PERFUN | ETN_MAC1_RESET_PEMCS_TX
			| ETN_MAC1_RESET_PETFUN,
			priv->base_addr_virt + IP3912_MAC1);

	__raw_writel(ETN_CMD_REG_RESET | ETN_CMD_TX_RESET | ETN_CMD_RX_RESET,
			priv->base_addr_virt + IP3912_CMD);

	/* Remove SoftReset Condition. */
	__raw_writel(0, priv->base_addr_virt + IP3912_MAC1);

	return 0;
}

/*
 * Register the phy bus for each ETN device
 *
 * Not every IP3912 connects all MDIO buses to the outer world, we
 * select the bus based upon the devid and setup the phys in the
 * architecture specific bootup code. This way we register all buses
 * but only some of them.
 */

int ip3912_mii_init(struct ip3912_priv *priv, struct ip3912_priv *first_intf)
{
	int i;

#ifdef CONFIG_IP3912_ETN1
	if(priv->pdev->id != 0)
		return 0;
#endif
	priv->mii_bus = mdiobus_alloc();
	if (priv->mii_bus == NULL)
		return -1;

	priv->mii_bus->name = "ip3912_mii_bus";
	priv->mii_bus->read = &ip3912_mdio_read;
	priv->mii_bus->write = &ip3912_mdio_write;
	priv->mii_bus->reset = &ip3912_mdio_reset;
	priv->mii_bus->priv = first_intf;
	priv->mii_bus->phy_mask = 0; /* 31 phys per bus */
	snprintf(priv->mii_bus->id, MII_BUS_ID_SIZE, "%x", 0);

	priv->mii_bus->irq = kmalloc(PHY_MAX_ADDR*sizeof(int), GFP_KERNEL);
	if (!priv->mii_bus->irq)
		return -ENOMEM;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		priv->mii_bus->irq[i] = PHY_POLL;

	i = mdiobus_register(priv->mii_bus);
	if (i < 0)
		printk("%s: registration of the bus failed: %d\n", 
				__FUNCTION__, i);

	return 0;
}
