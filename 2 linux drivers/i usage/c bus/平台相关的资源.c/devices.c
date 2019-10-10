/*
 *  linux/arch/arm/mach-pnx8181/devices.c - device specification
 *
 *  Copyright (C) 2007 NXP Semiconductors, Nuremberg
 *  (c) 2007,2008, Juergen Schoew, emlix GmbH <js@emlix.com>
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
#include <linux/platform_device.h>
#include <linux/serial.h>
#include <linux/serial_8250.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/physmap.h>
#include <linux/leds.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <video/ili9222fb.h>
#include <net/ip3912.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <asm/gpio.h>
#include <mach/serial.h>
#include <mach/platform.h>
#include <mach/hardware.h>
#include <mach/pnx8181_keyboard.h>
#include <mach/pnx8181-udc.h>
#include <mach/pnx8181-dmau.h>
#include <mach/hardware.h>
//#define CONFIG_MTD_NAND_PNX8181_RB_GPIO 1

/* UART */
static struct plat_serial8250_port uart_platform_data[] = {
	{
		.membase	= (void *)__iomem(0xC2004000),
		.mapbase	= 0xC2004000,
		.irq		= 24,
		.flags		= (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
					UPF_BUGGY_UART),
		.iotype		= UPIO_MEM,
		.regshift	= 2, /* registers are 32bit */
		.uartclk	= BASE_BAUD * 16,
	},
	{
		.membase	= (void *)__iomem(0xC2005000),
		.mapbase	= 0xC2005000,
		.irq		= 23,
		.flags		= (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
					UPF_BUGGY_UART),
		.iotype		= UPIO_MEM,
		.regshift	= 2, /* registers are 32bit */
		.uartclk	= BASE_BAUD * 16,
	},
	{ },
};

static struct platform_device uart_device = {
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= {
		.platform_data	= uart_platform_data,
	},
};

/* Heartbeat LED */
static struct gpio_led pnx8181_leds[] = {
	{	.name		= "led1",
		.gpio		= GPIO_PORTA(9),
		.active_low	= 1,
	},
	{	.name		= "led2",
		.gpio		= GPIO_PORTA(0),
		.active_low	= 1,
		.default_trigger = "heartbeat"
	},
};
static const struct gpio_led_platform_data pnx8181_leds_data = {
	.num_leds	= ARRAY_SIZE(pnx8181_leds),
	.leds		= (void *) &pnx8181_leds,
};
static struct platform_device pnx8181_gpio_leds = {
	.name = "leds-gpio",
	.id = -1,
	.dev = {
		.platform_data = (void *) &pnx8181_leds_data,
	}
};

#ifdef CONFIG_MTD_NAND

/* hardware specific access to control-lines */
static void pnx8181_nand_cmd_ctl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;
	unsigned long IO_ADDR_W = (unsigned long)this->IO_ADDR_W;

	if (ctrl & NAND_CLE)
		IO_ADDR_W += PNX8181_NAND_CLE_ADDR;

	if (ctrl & NAND_ALE)
		IO_ADDR_W += PNX8181_NAND_ALE_ADDR;

	if (dat != NAND_CMD_NONE) {
		if (this->options & NAND_BUSWIDTH_16)
			writew((unsigned short)dat, IO_ADDR_W);
		else
			writeb((unsigned char)dat, IO_ADDR_W);
	}
}

static void pnx8181_lc_nand_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;
	unsigned long IO_ADDR_W = (unsigned long)this->IO_ADDR_W;

	if (ctrl & NAND_CLE)
		IO_ADDR_W += PNX8181_LC_NAND_CLE_ADDR;

	if (ctrl & NAND_ALE)
		IO_ADDR_W += PNX8181_LC_NAND_ALE_ADDR;

	if (dat != NAND_CMD_NONE) {
		if (this->options & NAND_BUSWIDTH_16)
			writew((unsigned short)dat, IO_ADDR_W);
		else
			writeb((unsigned char)dat, IO_ADDR_W);
	}
}

/* read device ready pin */
static int pnx8181_nand_device_ready(struct mtd_info *mtd)
{
	return gpio_get_value(GPIO_PORTB(18))  ? 1 : 0;
}

#ifdef CONFIG_MTD_NAND_PNX8181_RB_GPIO
static int pnx8181_lc_nand_device_ready(struct mtd_info *mtd)
{
	return gpio_get_value(GPIO_PORTC(12))  ? 1 : 0;
}
#endif

static void pnx8181_nand_select_chip(struct mtd_info *mtd, int chip)
{
	if (chip < 0) /* deselect */
		gpio_set_value(GPIO_PORTA(7), 1);
	else          /* select */
		gpio_set_value(GPIO_PORTA(7), 0);
}

static void pnx8181_lc_nand_select_chip(struct mtd_info *mtd, int chip)
{
#if 0
	if (chip < 0) /* deselect */
		gpio_set_value(GPIO_PORTC(29), 1);
	else          /* select */
		gpio_set_value(GPIO_PORTC(29), 0);
#endif
}

static const char *pnx8181_part_probes[] = { "cmdlinepart", NULL };

struct platform_nand_data pnx8181_nand_platdata = {
	.chip = {
		.chip_offset = 0,
		.chip_delay = 20,
		.part_probe_types = pnx8181_part_probes,
		.options = NAND_USE_FLASH_BBT | NAND_BBT_CREATE
#ifdef CONFIG_MTD_NAND_PNX8181	
                            | NAND_BBT_WRITE | NAND_BBT_VERSION | NAND_NO_READRDY,
#else
                            | NAND_BBT_WRITE | NAND_BBT_VERSION,
#endif 
	},
	.ctrl = {
		.hwcontrol = 0,
		.dev_ready = pnx8181_nand_device_ready,
		.select_chip = pnx8181_nand_select_chip,
		.cmd_ctrl = pnx8181_nand_cmd_ctl,
	},
};

static struct resource pnx8181_nand_resource[] = {
	[0] = {
		.start = PNX8181_FLASH_BASE,
		.end   = PNX8181_FLASH_BASE + PNX8181_NAND_CLE_ADDR,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device pnx8181_nand = {
#ifdef CONFIG_MTD_NAND_PNX8181	
        .name           = "pnx8181_nand",
#else        
        .name           = "gen_nand",
#endif         
        .num_resources  = ARRAY_SIZE(pnx8181_nand_resource),
	.resource       = pnx8181_nand_resource,
	.id             = -1,
	.dev            = {
		.platform_data = &pnx8181_nand_platdata,
	}
};

#endif

#ifdef CONFIG_MTD_CFI
static struct resource cfi_flash_resources[] = {
	{
		.start	= PNX8181_FLASH_BASE,
		.end	= PNX8181_FLASH_BASE + PNX8181_FLASH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct physmap_flash_data cfi_flash_data = {
	.width		= 2,
};

static struct platform_device cfi_flash = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= {
		.platform_data = &cfi_flash_data,
	},
	.resource	= cfi_flash_resources,
	.num_resources	= ARRAY_SIZE(cfi_flash_resources),
};
#endif

/* display */
static struct ili9222fb_pdata ili9222fb_pdata = {
	.backlight_gpio = GPIO_PORTA(16),
};

static struct resource ili9222_resources[] = {
	{
		.start = 0x90000000, /* we only need adresses 0x90000000 and */
		.end   = 0x900000ff, /* 0x90000020 */
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device ili9222_device = {
	.name = "ili9222fb",
	.resource = ili9222_resources,
	.num_resources = ARRAY_SIZE(ili9222_resources),
	.dev = {
		.platform_data = &ili9222fb_pdata,
	},
};

static struct resource backlight_resources[] = {
	{
		.start = 0xC2000000,
		.end   = 0xC2000000 + SZ_4K,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device backlight_device = {
	.name = "drf1902-bl",
	.resource = backlight_resources,
	.num_resources = ARRAY_SIZE(backlight_resources),
	.dev = {
		//.platform_data = &backlight_pdata,
	},
};

#if defined(CONFIG_KEYBOARD_PNX8181) || defined(CONFIG_KEYBOARD_PNX8181_MODULE)
/* keyboard scanner */
static struct pnx8181_keyboard_platform_data pnx8181_keyboard_pdata = {
	.nr_rows    = 5,
	.nr_cols    = 5,
	.debounce   = 7,
	.irq	    = 16,
	.keycodes = { /* [row][col] */
		{KEY_1,     KEY_2,     KEY_3,     KEY_LEFT,  KEY_OPEN },
		{KEY_4,     KEY_5,     KEY_6,     KEY_RIGHT, KEY_FORWARD },
		{KEY_7,     KEY_8,     KEY_9,     KEY_UP,    KEY_REWIND },
		{KEY_PROG1, KEY_0,     KEY_PROG2, KEY_DOWN,  KEY_DELETE },
		{KEY_R,     KEY_CLOSE, KEY_ENTER, BTN_1,     BTN_2 }
	},
	.static_keycode1 = KEY_PAGEUP,
	.static_gpio1    = GPIO_PORTA(10),
	.static_keycode2 = KEY_PAGEDOWN,
	.static_gpio2    = GPIO_PORTA(2),
	.delay	    = (HZ / 20),
	.clock = "kbs",
};


static struct resource pnx8181_keyboard_resource[] = {
	{
		.start	= PNX8181_KBS_DEB,
		.end	= PNX8181_KBS_DATA7,
		.flags	= IORESOURCE_MEM,
		.name	= "pnx8181-keyboard-io",
	},
	{
		.start	= 16,
		.end	= 16,
		.flags	= IORESOURCE_IRQ,
		.name	= "pnx8181-keyboard-irq",
	},
};

static struct platform_device pnx8181_keyboard_device = {
	.name = "pnx8181-keyboard",
	.resource = pnx8181_keyboard_resource,
	.num_resources = ARRAY_SIZE(pnx8181_keyboard_resource),
	.dev = {
		.platform_data = &pnx8181_keyboard_pdata,
	},
};
#endif

struct pnx_phy_data {
	enum firetux_revisions board;
	unsigned long features;
	const char *phy;
};

static struct pnx_phy_data pnx_phy_data_etn1[] = {
	{ EZ_MCP_PNX8181,              0,                   "0:01" },
	{ Vega_PNX8181_BaseStation_V1, 0,                   "0:01" },
	{ Vega_PNX8181_BaseStation_LC, FEATURE_LC_LAN87820, "0:00" },
	{ Vega_PNX8181_BaseStation_LC, FEATURE_LC_KSZ8873,  NULL   },
	{ Vega_PNX8181_BaseStation_LC, FEATURE_LC_RTL8863SB,NULL   },
};

static struct ip3912_pdev ip3912_etn1_pdata = {
	.irq = 22,
	.phy = "0:1e",
	.clock = "etn1",
};

static struct resource ip3912_etn1_resources[] = {
	{
		.start = 0xC1600000,
		.end   = 0xC1600FFC,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device ip3912_etn1_device = {
	.name = "ip3912",
	.id = 0,
	.resource = ip3912_etn1_resources,
	.num_resources = ARRAY_SIZE(ip3912_etn1_resources),
	.dev = {
		.platform_data = &ip3912_etn1_pdata,
	},
};

#ifdef CONFIG_REALTEK_8863SB
static struct rtl8863_mdata rtl8863_pdata = {
	.gpio_clk   =  GPIO_PORTC(24),
	.gpio_data  =  GPIO_PORTC(22),
	.gpio_reset =  GPIO_PORTC(28)
};
static struct platform_device rtl8863sb_l2_device = {
	.name = "rtl8863sb-pnx8181",
	.id = 0,
	.dev = {
		.platform_data = &rtl8863_pdata,
	},
};
#endif

#ifdef CONFIG_IP3912_ETN2
static struct pnx_phy_data pnx_phy_data_etn2[] = {
	{ EZ_MCP_PNX8181, 0, "0:02" },
	{ Vega_PNX8181_BaseStation_V1, 0, "0:02" },
};

static struct ip3912_pdev ip3912_etn2_pdata = {
	.irq = 21,
	.phy = "0:1d",
	.clock = "etn2",
};

static struct resource ip3912_etn2_resources[] = {
	{
		.start = 0xC1700000,
		.end   = 0xC1700FFC,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device ip3912_etn2_device = {
	.name = "ip3912",
	.id = 1,
	.resource = ip3912_etn2_resources,
	.num_resources = ARRAY_SIZE(ip3912_etn2_resources),
	.dev = {
		.platform_data = &ip3912_etn2_pdata,
	},
};
#endif


static struct pnx8181udc_pdata pnx8181_udc_pdata = {
};

static struct resource pnx8181_udc_resources[] = {
	{
		.start = 0x0,
		.end = 0x0,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = PNX8181_ID_USBIRQ,
		.flags = IORESOURCE_IRQ,
		.name  = "pnx8181udc-irq-usb",
	},
	{
		.start = PNX8181_ID_USBVBUS,
		.flags = IORESOURCE_IRQ,
		.name  = "pnx8181udc-irq-vbus",
	},
	{
		.start = PNX8181_ID_USBNEEDCLK,
		.flags = IORESOURCE_IRQ,
		.name  = "pnx8181udc-irq-needclk",
	},
};

static struct platform_device pnx8181_udc = {
	.name          = "pnx8181_udc",
	.id            = -1,
	.dev           = {
		.platform_data = &pnx8181_udc_pdata,
	},
	.resource      = pnx8181_udc_resources,
	.num_resources = ARRAY_SIZE(pnx8181_udc_resources),
};

static struct resource pnx8181_dmau_resources[] = {
	{
		.name = "dmau-registers",
		.start = 0xC1000000,
		.end = 0xC1000273,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = PNX8181_ID_DMAU,
		.flags = IORESOURCE_IRQ,
		.name  = "pnx8181dmau-irq",
	},

};


static struct pnx8181dmau_pdata pnx8181_dmau_pdata = {
	.clock = "dmau",
};



static struct platform_device pnx8181_dmau = {
	.name          = "pnx8181_dmau",
	.id            = -1,
	.dev           = {
		.platform_data = &pnx8181_dmau_pdata,
		.coherent_dma_mask = 0xFFFFFFFF,
	},
	.resource      = pnx8181_dmau_resources,
	.num_resources = ARRAY_SIZE(pnx8181_dmau_resources),
};
/* list of devices */
static struct platform_device *platform_devs[] __initdata = {
	&pnx8181_dmau,
	&uart_device,
#ifdef CONFIG_MTD_NAND
	&pnx8181_nand,
#endif
#ifdef CONFIG_MTD_CFI
	&cfi_flash,
#endif
	&pnx8181_gpio_leds,
	&ili9222_device,
#if defined(CONFIG_KEYBOARD_PNX8181) || defined(CONFIG_KEYBOARD_PNX8181_MODULE)
	&pnx8181_keyboard_device,
#endif
	&ip3912_etn1_device,
#ifdef CONFIG_REALTEK_8863SB
	&rtl8863sb_l2_device,
#endif
#ifdef CONFIG_IP3912_ETN2
	&ip3912_etn2_device,
#endif
	&pnx8181_udc,
};

/* register all devices */
static int __init pnx8181_devices_init(void)
{
	int i;
	unsigned char board = firetux_get_boardrevision();
	unsigned long features = firetux_get_boardfeatures();

	/* Allow different phy address for different boards */
	for (i = 0 ; i < ARRAY_SIZE(pnx_phy_data_etn1); i++) {
		if (pnx_phy_data_etn1[i].board != board)
			continue;
		if ((pnx_phy_data_etn1[i].features & features) !=
		    pnx_phy_data_etn1[i].features)
			continue;

		ip3912_etn1_pdata.phy = pnx_phy_data_etn1[i].phy;
		break;
	}

#ifdef CONFIG_IP3912_ETN2
	/* Allow different phy address for different boards */
	for (i = 0 ; i < ARRAY_SIZE(pnx_phy_data_etn2); i++) {
		if (pnx_phy_data_etn2[i].board != board)
			continue;
		if ((pnx_phy_data_etn2[i].features & features) !=
		    pnx_phy_data_etn2[i].features)
			continue;

		ip3912_etn2_pdata.phy = pnx_phy_data_etn2[i].phy;
		break;
	}
#endif

#ifdef CONFIG_MTD_NAND
	if (board == Vega_PNX8181_BaseStation_LC) {
		pnx8181_nand_platdata.chip.chip_delay = 50;
#ifdef CONFIG_MTD_NAND_PNX8181_RB_GPIO
		pnx8181_nand_platdata.ctrl.dev_ready = pnx8181_lc_nand_device_ready;
#else
		pnx8181_nand_platdata.ctrl.dev_ready = NULL;
#endif
		pnx8181_nand_platdata.ctrl.select_chip = pnx8181_lc_nand_select_chip;
		pnx8181_nand_platdata.ctrl.cmd_ctrl = pnx8181_lc_nand_cmd_ctrl;

		pnx8181_nand_resource[0].start = PNX8181_LC_FLASH_BASE;
		pnx8181_nand_resource[0].end   = PNX8181_LC_FLASH_BASE +
		                                 PNX8181_LC_NAND_ALE_ADDR;
	}
#endif

#if defined(CONFIG_KEYBOARD_PNX8181) || defined(CONFIG_KEYBOARD_PNX8181_MODULE)
	if (board == Vega_PNX8181_BaseStation_LC) {
		int keycodes[MAXROW][MAXCOLS] = { /* [row][col] */
			{KEY_3,               KEY_2,               KEY_1,
			 KEY_VOLUMEDOWN,      KEY_VOLUMEUP,        KEY_FORWARD },
			{KEY_6,               KEY_5,               KEY_4,
			 KEY_F2 /* SWKEY2 */, KEY_F1 /* SWKEY1 */, KEY_REWIND },
			{KEY_9,               KEY_8,               KEY_7,
			 KEY_OPEN /* ON */,   KEY_CLOSE /* OFF */, BTN_2 /* M2 */},
			{KEY_PROG2,           KEY_0,               KEY_PROG1,
			 KEY_UP,              KEY_DOWN,            BTN_1 /* M1 */ },
			{KEY_I,               KEY_R,               KEY_H,
			 KEY_RIGHT,           KEY_LEFT,            KEY_CLOSE /* HOOK */ },
		};
		pnx8181_keyboard_pdata.nr_rows = 6;
		pnx8181_keyboard_pdata.nr_cols = 6;
		memcpy(pnx8181_keyboard_pdata.keycodes, keycodes, sizeof(keycodes));
	}
#endif

	return platform_add_devices(platform_devs, ARRAY_SIZE(platform_devs));
}
module_init(pnx8181_devices_init);
