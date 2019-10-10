/*
 *  linux/arch/arm/mach-pnx8181/spi-devices.c - SPI-device definitions
 *
 *  Copyright (C) 2010 DSPG Technologies GmbH
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
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <asm/gpio.h>
#include <linux/spi/pnx8181_data.h>
#include <linux/mtd/partitions.h>
#include <linux/spi/flash.h>
#include <video/st7565fb.h>

/* This is pretty lame:
 * The linux spi interface defines chip_select != unsigned
 * this means it's not usable with the GPIO system. This is
 * why we use thie controller data here.
 */
static struct pnx8181_cdata spi_gpio29_cdata = {
	.chip_select = GPIO_PORTA(16),
	.mode = SPI_MODE_0,
	.bits_per_word = 8,
};

/* chip select for the st7565 LCD controller */
static struct pnx8181_cdata st7565_cdata = {
	.chip_select = GPIO_PORTA(16),	/* XXX change this */
	.mode = SPI_MODE_0,
	.bits_per_word = 8,
};

static struct pnx8181_cdata glcd_cdata = {
	.chip_select = GPIO_PORTA(30),	/* XXX change this */
	.mode = SPI_MODE_0,
	.bits_per_word = 8,
};

/* The FXS */
static struct pnx8181_cdata spi_gpio14_cdata = {
	.chip_select = GPIO_PORTB(25),
	.mode = SPI_MODE_3,
	.bits_per_word = 8,
};

static struct flash_platform_data  pnx8181_dataflash_platdata = {
	.name		= "spi_flash",
};

static struct st7565fb_pdata st7565_pdata = {
	.a0_gpio = GPIO_PORTA(31),	/* XXX change this */
#ifdef CONFIG_FB_ST7565_HAS_WR
	._wr_gpio = GPIO_PORTA(16),	/* XXX change this */
#endif
	.rst_gpio = GPIO_PORTA(5),
};

static struct spi_board_info spi_boards[] = {
	/* The Dataflash (a dummy in the V2) */
	{
		.modalias = "mtd_dataflash",
		.max_speed_hz = 20 * 1000 * 1000,
		.bus_num = 1,
		.chip_select = 16, /* We can't use GPIO_PORTA(29) here :( */
		/* .irq = 0, */
		.controller_data = &spi_gpio29_cdata,
		.platform_data=&pnx8181_dataflash_platdata,
	},
	{
		.modalias = "m25p80",
		.max_speed_hz = 20 * 1000 * 1000,
		.bus_num = 1,
		.chip_select = 17, /* We can't use GPIO_PORTA(29) here :( */
		/* .irq = 0, */
		.controller_data = &spi_gpio29_cdata,
		.platform_data=&pnx8181_dataflash_platdata,
	},
	{
		.modalias = "spidev",
		.max_speed_hz = 10000,
		.bus_num = 1,
		.chip_select = 14,
		.controller_data = &spi_gpio14_cdata,
	},
	{
		.modalias = "st7565fb",
		.max_speed_hz = 26 * 1000 * 1000,
		.bus_num = 1,
		.chip_select = 19,
		/* .irq = 0, */
		.controller_data = &st7565_cdata,
		.platform_data=&st7565_pdata,
	},
	{
		.modalias = "glcd",
		.max_speed_hz = 12 * 1000 * 1000,
		.bus_num = 1,
		/*.chip_select = GPIO_PORTA(30),*/
		.chip_select = 30,
		.controller_data = &glcd_cdata,
	},
};

/* The memory and IRQ mappings belong to here */
static struct resource pnx8181_spi2_resources[] = {
	{
		.name = "spi-registers",
		.flags = IORESOURCE_MEM,
		.start = 0xC2002000, /* spi2_global */
		.end =   0xC2002408, /* spi2_timer_status */
	},
	{
		.name = "spi-interrupt",
		.flags = IORESOURCE_IRQ,
		.start = 26,
		.end = 26,
	},
};

/*
 * The master data, this will help us to bring everything up
 * very fast
 */
struct pnx8181_mdata pnx8181_spi2_mdata = {
	.bus_num = 1,
	.num_chipselect = 100, /* We can have as much as we need */
	.cs_control = NULL, /* Use the GENERIC_GPIO mechanism */
	.clock = "spi1",
};

/* The platform device for the mater driver */
static struct platform_device pnx8181_spi2_master = {
	.name = "spi-pnx8181",
	.id = -1,
	.resource = pnx8181_spi2_resources,
	.num_resources = ARRAY_SIZE(pnx8181_spi2_resources),
	.dev = {
		.platform_data = &pnx8181_spi2_mdata,
	}
};

static __init int spi_init(void)
{
	/* Register the master and all devices on the SPI bus */
	int err, i;
	struct pnx8181_cdata *cdata;

	/* Register the master */
	err = platform_device_register(&pnx8181_spi2_master);
	if(err)
		return err;

	/* Now try to register the gpios */
	for(i = 0; i < ARRAY_SIZE(spi_boards); i++)
	{
		cdata = spi_boards[i].controller_data;
		if(!cdata)
			continue;

		err = gpio_request(cdata->chip_select, spi_boards[i].modalias);
		if(err)
			printk("%s: Can't register GPIO %X\n", __FUNCTION__,
						cdata->chip_select);

		/* This GPIO has to be an output and active HIGH */
		if(gpio_direction_output(cdata->chip_select, 1))
		{
			printk("%s: Setting GPIO %X to Output High failed\n",
					__FUNCTION__, cdata->chip_select);
		}
	}

	/* Register the modules */
	if(ARRAY_SIZE(spi_boards))
		err = spi_register_board_info(spi_boards, ARRAY_SIZE(spi_boards));

	return err;
}
module_init(spi_init);
