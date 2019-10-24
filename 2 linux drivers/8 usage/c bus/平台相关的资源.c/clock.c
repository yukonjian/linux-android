/*
 *  linux/arch/arm/mach-pnx8181/clock.c
 *
 *  Copyright (C) 2008 Sebastian Heß <sh@emlix.com>, emlix GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <asm/io.h>
#include <mach/io.h>

#include "clock.h"

static DEFINE_MUTEX(clocks_mutex);

static struct pnx8181_clk_usage registers = {
	.gatesc = (u32 *) 0xC2200008,
};


/* TODO: rouding is not supported right now */
long clk_round_rate(struct clk *clk, unsigned long rate)
{
	return rate;
}
EXPORT_SYMBOL(clk_round_rate);

unsigned long clk_get_rate(struct clk *clk)
{
	return clk ? clk->rate : 0;
}
EXPORT_SYMBOL(clk_get_rate);

/* TODO: Set the rate is not implemented */
int clk_set_rate(struct clk *clk, unsigned long rate)
{
	return 0;
}
EXPORT_SYMBOL(clk_set_rate);


/* Clock enabling an disabling is currently
 * only implemented for non PLL outputs */
int clk_enable(struct clk *clk)
{
	/* Caching of the CGUGATESC register */
	u32 value;

	if (!clk)
		return -ENODEV;

	/* No enabling of the PLL Sources right now */
	if (clk->flags == FLAG_PLL)
		return -EINVAL;

	/* Set the corresponding bit */
	mutex_lock(&clocks_mutex);
	value = __raw_readl(registers.gatesc);
	value |= (1 << clk->enable_bit);
	__raw_writel(value, registers.gatesc);
	mutex_unlock(&clocks_mutex);

	return 0;
}
EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *clk)
{
	u32 value;

	if (!clk)
		return;

	/* No disabling of the PLL Sources right now */
	if (clk->flags == FLAG_PLL)
		return;

	/* Reset the corresponding bit */
	mutex_lock(&clocks_mutex);
	value = __raw_readl(registers.gatesc);
	value &= ~(1 << clk->enable_bit);
	__raw_writel(value, registers.gatesc);
	mutex_unlock(&clocks_mutex);
	return;
}
EXPORT_SYMBOL(clk_disable);

/* All clocks are taken from the VegaFB_CGU_simulator */
static struct clk pnx8181_clocks[] = {
	/* PLL outputs */
	CLK_PLL("clk32k", 32000)
	/* Clocks to be activated / gated */
	CLK_GATED_FLAGS("intc", 0, FLAG_ENABLE)
	CLK_GATED("extint", 1)
	CLK_GATED_FLAGS("sctu", 2, FLAG_ENABLE)
	CLK_GATED("spi1", 3)
	CLK_GATED("spi2", 4)
	CLK_GATED("pnx-i2c", 5)
	CLK_GATED_FLAGS("uart1", 6, FLAG_ENABLE)
	CLK_GATED_FLAGS("uart2", 7, FLAG_ENABLE)
	CLK_GATED("bmp", 8)
	CLK_GATED("gpio", 9)
	CLK_GATED("kbs", 10)
	CLK_GATED("pwm1", 11)
	CLK_GATED("pwm2", 12)
	CLK_GATED("pwm3", 13)
	CLK_GATED("ipint", 14)
	CLK_GATED("usim", 15)
	CLK_GATED("fci", 16)
	CLK_GATED("usbd", 17)
	CLK_GATED("iis", 18)
	CLK_GATED("drt", 19)
	CLK_GATED("dmau", 20)
	CLK_GATED("daif", 21)
	CLK_GATED("etn1", 22)
	CLK_GATED("etn2", 23)
	CLK_GATED("fir", 24)
	CLK_GATED("adpcm", 25)
	/* 26, 27 = reserved */
	CLK_GATED_FLAGS("sdi", 28, FLAG_ENABLE)
	/* 29 = reserved */
	CLK_GATED_FLAGS("ebi1", 30, FLAG_ENABLE)
	CLK_GATED_FLAGS("ebi2", 31, FLAG_ENABLE)
};

struct clk *clk_get(struct device *dev, const char *id)
{
	int i;
	struct clk *clk = ERR_PTR(-ENOENT);
	struct clk *clock;

	if (!id)
		return NULL;

	mutex_lock(&clocks_mutex);
	for (i = 0; i < ARRAY_SIZE(pnx8181_clocks); i++) {
		clock = &pnx8181_clocks[i];

		if (!strcmp(id, clock->name)) {
			clk = clock;
			break;
		}
	}
	mutex_unlock(&clocks_mutex);

	return clk;
}
EXPORT_SYMBOL(clk_get);

/*
 * This must be called with clocks_mutex held
 */
static const char *clk_enabled(struct clk *clk)
{
	u32 value = __raw_readl(registers.gatesc);

	if (value & (1 << clk->enable_bit))
		return "enabled";

	return "disabled";
}

/*
 * "put" a clock
 */
void clk_put(struct clk *clk)
{
	/* Check for running clock */
	BUG_ON(__raw_readl(registers.gatesc) & (1 << clk->enable_bit));
}
EXPORT_SYMBOL(clk_put);

/* /proc/clocks information */
static int proc_read(char *buf, char **start, off_t offset, int size,
			int *eof, void *data)
{
	int i;
	int ret;
	int bytes_written = 0;

	mutex_lock(&clocks_mutex);
	for (i = 0; i < ARRAY_SIZE(pnx8181_clocks); i++) {
		ret = snprintf(buf + bytes_written, (size-bytes_written),
			"[%s] %s\n", pnx8181_clocks[i].name,
			clk_enabled(&pnx8181_clocks[i]));
		bytes_written += (ret > (size-bytes_written)) ?
			(size - bytes_written) : ret;
	}
	*eof = 1;
	mutex_unlock(&clocks_mutex);

	return bytes_written;
}
static int __init clk_init(void)
{
	int i;
	struct proc_dir_entry *proc_file;

	/* Run through all the clocks, and enable the ones
	 * needed during early bootup, like serial and INTC */
	for (i = 0; i < ARRAY_SIZE(pnx8181_clocks); i++) {
		struct clk *clock = &pnx8181_clocks[i];

		/* The PLL outputs should be setup by uboot */
		if (clock->flags == FLAG_PLL)
			continue;

		/* Enable the need clocks, we don't disable unneeded ones */
		if (clock->flags & FLAG_ENABLE)
			clk_enable(clock);
		else
			clk_disable(clock);
	}

	/* create proc entry */
	proc_file = create_proc_entry("clocks", S_IRUGO, NULL);
	if (proc_file) {
		proc_file->read_proc = proc_read;
		proc_file->data = NULL;
	}
	return 0;
}
arch_initcall(clk_init);
