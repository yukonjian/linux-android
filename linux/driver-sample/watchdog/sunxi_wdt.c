/*
 *	sunxi Watchdog Driver
 *
 *
 * Copyright(c) 2013-2015 Allwinnertech Co., Ltd. 
 *      http://www.allwinnertech.com
 *
 * Author: huangshr <huangshr@allwinnertech.com>
 *
 * allwinner sunxi SoCs Watchdog driver.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Based on xen_wdt.c
 * (c) Copyright 2010 Novell, Inc.
 *
 * Known issues:
 *  * A Watchdog's function is to return an unresponsive system to 
 *  * operational state. It does this by periodically checking the 
 *  * system's pulse and issuing a reset if it can't detect any.
 *  * Application software is responsible for registering this pulse 
 *  * periodically petting the watchdong using the services of a 
 *  * watchdog device driver.
 */
 
#define DRV_NAME	"sunxi_wdt"
#define DRV_VERSION	"1.0"
#define PFX		DRV_NAME ": "

#include <linux/bug.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/resource.h>
#include <linux/uaccess.h>
#include <linux/watchdog.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/semaphore.h>



#define WATCHDOG_DBG

#ifdef WATCHDOG_DBG
#define wdt_dbg(x,arg...) printk(KERN_DEBUG"[VFE_DBG],line %d"x,__LINE__,##arg)
#else
#define wdt_dbg(x,arg...)
#endif



#define SUNXI_WATCHDOG_BASE	(0x01c20c00 + 0x0090)

#define SUNXI_WATCHDOG_CTRL_OFFSET	(0)
#define SUNXI_WATCHDOG_MODE_OFFSET	(4)

#define WDOG_RSTART_BIT		(0)
#define WDOG_RSTART_MASK	(1<<WDOG_RSTART_BIT)

#define WDOG_EN_BIT			(0)
#define WDOG_EN_MASK		(1<<WDOG_EN_BIT)

#define WDOG_RST_BIT		(1)
#define WDOG_RST_MASK		(1<<WDOG_RST_BIT)

#define WDOG_INTV_VALUE_BIT		(3)
#define WDOG_INTV_VALUE_MASK	(0x0f<<WDOG_INTV_VALUE_BIT)



struct sunxi_watchdog_info{
	void __iomem *wdt_virtual_addr;
	struct semaphore reg_sema;	
};




struct sunxi_watchdog_info wdt_info;


#define MAX_TIMEOUT 		16 	/* max 16 seconds */

static struct platform_device *platform_device;
static bool is_active, expect_release;

struct sunxi_watchdog_interv{
	u32 	timeout;
	u32 	interv;
};

static const struct sunxi_watchdog_interv g_timeout_interv[] = {
	{.timeout = 0.5, .interv = 0b0000},
	{.timeout = 1  , .interv = 0b0001},
	{.timeout = 2  , .interv = 0b0010},
	{.timeout = 3  , .interv = 0b0011},
	{.timeout = 4  , .interv = 0b0100},
	{.timeout = 5  , .interv = 0b0101},
	{.timeout = 6  , .interv = 0b0110},
	{.timeout = 8  , .interv = 0b0111},
	{.timeout = 10 , .interv = 0b1000},
	{.timeout = 12 , .interv = 0b1001},
	{.timeout = 14 , .interv = 0b1010},
	{.timeout = 16 , .interv = 0b1011},
};

static unsigned int g_timeout = MAX_TIMEOUT; /* watchdog timeout in second */
module_param(g_timeout, uint, S_IRUGO);
MODULE_PARM_DESC(g_timeout, "Watchdog g_timeout in seconds "
			"(default=" __MODULE_STRING(MAX_TIMEOUT) ")");

static bool g_nowayout = WATCHDOG_NOWAYOUT;
module_param(g_nowayout, bool, S_IRUGO);
MODULE_PARM_DESC(g_nowayout, "Watchdog cannot be stopped once started "
			"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
	
static struct resource sunxi_wdt_res[] = {
	{
		.start	= SUNXI_WATCHDOG_BASE,
		.end	= SUNXI_WATCHDOG_BASE + 0x08 -1, 
		.flags	= IORESOURCE_MEM,
	},
};

static inline
u32 reg_readl(volatile void __iomem * addr)
{
	return readl(addr);
}

static inline
void reg_writel(volatile void __iomem *addr, u32 reg_value)
{
	writel(reg_value, addr);
}


static inline
void wdt_reg_clr( volatile void __iomem * reg, u32 clr_bits)
{
	u32 v = (u32)reg_readl(reg);
	reg_writel(reg, v & ~clr_bits);
}

static inline
void wdt_reg_set(volatile void __iomem * reg, u32 set_bits)
{
	u32 v = reg_readl(reg);
	reg_writel(reg, v | set_bits);
}

static inline
void wdt_reg_clr_set(volatile void __iomem * reg, u32 clr_bits, u32 set_bits)
{
	u32 v = (u32)reg_readl(reg);	
	reg_writel(reg, (v & ~clr_bits) | (set_bits & clr_bits));
}


static int wdt_irq_en(bool enable)
{

	return 0;
}

static int wdt_clr_irq_pend(void)
{
	return 0;
}

static int timeout_to_interv(int timeout_in_sec)
{
	int 	temp;
	int 	array_sz;

	array_sz = ARRAY_SIZE(g_timeout_interv);
	if(timeout_in_sec > g_timeout_interv[array_sz - 1].timeout)
		return g_timeout_interv[array_sz - 1].interv;
	else if(timeout_in_sec < g_timeout_interv[0].timeout)
		return g_timeout_interv[0].interv;
	else {
		for(temp = 0; temp < array_sz; temp++) {
			if(timeout_in_sec >= g_timeout_interv[temp].timeout)
				continue;
			else
				return g_timeout_interv[temp - 1].interv;
		}
		pr_info("%s, line %d\n", __func__, __LINE__);
		return g_timeout_interv[array_sz - 1].interv; /* the largest one */
	}
}

static int interv_to_timeout(int interv)
{
	int 	temp;
	int 	array_sz;

	array_sz = ARRAY_SIZE(g_timeout_interv);
	if(interv > g_timeout_interv[array_sz - 1].interv)
		return g_timeout_interv[array_sz - 1].timeout;
	else if(array_sz < g_timeout_interv[0].interv)
		return g_timeout_interv[0].timeout;
	else {
		for(temp = 0; temp < array_sz; temp++) {
			if(interv >= g_timeout_interv[temp].interv)
				continue;
			else
				return g_timeout_interv[temp - 1].timeout;
		}
		pr_info("%s, line %d\n", __func__, __LINE__);
		return g_timeout_interv[array_sz - 1].timeout; /* the largest one */
	}
}


static int wdt_config(void)
{
	wdt_reg_clr_set(wdt_info.wdt_virtual_addr + SUNXI_WATCHDOG_MODE_OFFSET, WDOG_RST_MASK, 1<<WDOG_RST_BIT);
	return 0;
}


static int wdt_set_tmout(int timeout_in_sec)
{
	int 	temp2 = 0;
	int 	interv = 0;

	interv = timeout_to_interv(timeout_in_sec);
	if(interv < 0)
		return interv;
	wdt_reg_clr_set(wdt_info.wdt_virtual_addr + SUNXI_WATCHDOG_MODE_OFFSET, WDOG_INTV_VALUE_MASK, interv<<WDOG_INTV_VALUE_BIT);

	temp2 = interv_to_timeout(interv);
	pr_info("%s, write 0x%08x to mode reg , actual timeout is %d sec\n",
		__func__, interv,  temp2);
	return temp2;
}

static void wdt_enable(void)
{
	wdt_reg_clr_set(wdt_info.wdt_virtual_addr + SUNXI_WATCHDOG_MODE_OFFSET, WDOG_EN_MASK, 1<<WDOG_EN_BIT);
}

static void wdt_disable(void)
{
	wdt_reg_clr_set(wdt_info.wdt_virtual_addr + SUNXI_WATCHDOG_MODE_OFFSET, WDOG_EN_MASK, 0<<WDOG_EN_BIT);
}

static int wdt_restart(void)
{

	wdt_disable();
	msleep(1);
	wdt_reg_clr_set(wdt_info.wdt_virtual_addr + SUNXI_WATCHDOG_CTRL_OFFSET, WDOG_RSTART_MASK, (1<<WDOG_RSTART_BIT));
	msleep(1);
	wdt_enable();

	return 0;
}


static int watchdog_start(void)
{
	int temp = -1;
	
	temp = wdt_set_tmout(g_timeout);
	if(temp < 0)
		return temp;

	g_timeout = temp;
	wdt_enable();
	return 0;
}

static int watchdog_stop(void)
{	 
	wdt_disable();
	return 0;
}


static int watchdog_probe_init(void)
{
	int 	temp = -1;
        
	/* disable watchdog */
	//wdt_enable(false);
	 
	/* disable irq */
	wdt_irq_en(false);

	/* clear irq pending */
	wdt_clr_irq_pend();

	/* watchdog function initial */
	wdt_config();

	/* set max timeout */
	temp = wdt_set_tmout(g_timeout);
	if(temp < 0)
		return temp;

	g_timeout = temp;
	return 0;
}

static int watchdog_kick(void)
{	 
	return wdt_restart();
}

static int watchdog_set_timeout(int timeout)
{
	int temp = -1;

	temp = wdt_set_tmout(timeout);
	if(temp < 0)
		return temp;
	g_timeout = temp;
	return 0;

}

static int sunxi_wdt_open(struct inode *inode, struct file *file)
{
	int err;

	/* /dev/watchdog can only be opened once */
	if(xchg(&is_active, true))
		return -EBUSY;

	err = watchdog_start();
	
	return err ?: nonseekable_open(inode, file);
}

static int sunxi_wdt_release(struct inode *inode, struct file *file)
{
	if(expect_release)
		watchdog_stop();
	else {
		pr_info("%s: unexpected close, not stopping watchdog!\n", __func__);
//		watchdog_kick(); 
	}

	is_active = false;
	expect_release = false;
	return 0;
}

static ssize_t sunxi_wdt_write(struct file *file, const char __user *data,
			size_t len, loff_t *ppos)
{
	/* See if we got the magic character 'V' and reload the timer */
	if(len) {
		if(!g_nowayout) {
			size_t i;

			/* in case it was set long ago */
			expect_release = false;

			/* scan to see whether or not we got the magic character */
			for(i = 0; i != len; i++) {
				char c;
				if(get_user(c, data + i))
					return -EFAULT;
				if(c == 'V')
					expect_release = true;
			}
		}

		/* someone wrote to us, we should reload the timer */
		watchdog_kick();
	}
	return len;
}

static long sunxi_wdt_ioctl(struct file *file, unsigned int cmd,
			unsigned long arg)
{
	int new_options, retval = -EINVAL;
	int new_timeout;
	int __user *argp = (void __user *)arg;
	
	static const struct watchdog_info ident = {
		.options 		= WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
		.firmware_version 	= 0,
		.identity 		= DRV_NAME,
	};

	switch (cmd) {
		
	case WDIOC_GETSUPPORT: 
		return copy_to_user(argp, &ident, sizeof(ident)) ? -EFAULT : 0;

	case WDIOC_GETSTATUS:
		
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, argp);

	case WDIOC_SETOPTIONS:
		if(get_user(new_options, argp))
			return -EFAULT;
		down(&wdt_info.reg_sema);
		
		if(new_options & WDIOS_DISABLECARD)
			retval = watchdog_stop();
		if(new_options & WDIOS_ENABLECARD)
			retval = watchdog_start();
		up(&wdt_info.reg_sema);
		return retval;

	case WDIOC_KEEPALIVE:  
		down(&wdt_info.reg_sema);
		
		watchdog_kick();
		up(&wdt_info.reg_sema);
		return 0;

	case WDIOC_SETTIMEOUT:
		if(get_user(new_timeout, argp))
			return -EFAULT;
		if(!new_timeout || new_timeout > MAX_TIMEOUT) {
			pr_err("%s err, line %d\n", __func__, __LINE__);
			return -EINVAL;
		}
		down(&wdt_info.reg_sema);
		
		watchdog_set_timeout(new_timeout);
		up(&wdt_info.reg_sema);
		
	case WDIOC_GETTIMEOUT:
		return put_user(g_timeout, argp);
	}

	return -ENOTTY;
}
static const struct file_operations sunxi_wdt_fops = {
	.owner =		THIS_MODULE,
	.llseek =		no_llseek,
	.write =		sunxi_wdt_write,
	.unlocked_ioctl =	sunxi_wdt_ioctl,
	.open =			sunxi_wdt_open,
	.release =		sunxi_wdt_release,
};

static struct miscdevice sunxi_wdt_miscdev = {
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&sunxi_wdt_fops,
};

static int  sunxi_wdt_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *res;

	if(!g_timeout || g_timeout > MAX_TIMEOUT) {
		g_timeout = MAX_TIMEOUT;
		pr_info("%s: timeout value invalid, using %d\n", __func__, g_timeout);
	}

	/*
	 * As this driver only covers the global watchdog case, reject
	 * any attempts to register per-CPU watchdogs.
	 */
	if(pdev->id != -1)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if(unlikely(!res)) {
		ret = -EINVAL;
		goto err_get_resource;
	}

	if(!devm_request_mem_region(&pdev->dev, res->start,
				resource_size(res), DRV_NAME)) {
		ret = -EBUSY;
		goto err_request_mem_region;
	}

	wdt_info.wdt_virtual_addr = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if(!wdt_info.wdt_virtual_addr) {
		ret = -ENXIO;
		goto err_ioremap;
	}
	pr_info("%s: devm_ioremap return wdt_reg 0x%08x, res->start 0x%08x, res->end 0x%08x",
		__func__, (u32)wdt_info.wdt_virtual_addr, (u32)res->start, (u32)res->end);

	ret = misc_register(&sunxi_wdt_miscdev);
	if(ret) {
		pr_err("%s: cannot register miscdev on minor=%d (%d)\n",
			__func__, WATCHDOG_MINOR, ret);
		goto err_misc_register;
	}

	pr_info("%s: initialized (g_timeout=%ds, g_nowayout=%d)\n",
		__func__, g_timeout, g_nowayout);

	sema_init(&wdt_info.reg_sema, 1);


	//watchdog_kick(); /* give userspace a bit more time to settle if watchdog already running */
	watchdog_probe_init(); 	
	return ret;

err_misc_register:
	devm_iounmap(&pdev->dev, wdt_info.wdt_virtual_addr);
err_ioremap:
	devm_release_mem_region(&pdev->dev, res->start, resource_size(res));
err_request_mem_region:
err_get_resource:
	return ret;
}

static int  sunxi_wdt_remove(struct platform_device *pdev)
{
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	/* Stop the timer before we leave */
	watchdog_stop();

	misc_deregister(&sunxi_wdt_miscdev); 
	devm_iounmap(&pdev->dev, wdt_info.wdt_virtual_addr);   
	devm_release_mem_region(&pdev->dev, res->start, resource_size(res));

	return 0;
}

static void sunxi_wdt_shutdown(struct platform_device *pdev)
{
	watchdog_stop();
}

static int sunxi_wdt_suspend(struct platform_device *dev, pm_message_t state)
{
	if(is_active)
		return watchdog_stop();
	else
		return 0;
}

static int sunxi_wdt_resume(struct platform_device *dev)
{
	if(is_active)
		return watchdog_start();
	else
		return 0;
}

static struct platform_driver sunxi_wdt_driver = {
	.probe          = sunxi_wdt_probe,
	.remove         = sunxi_wdt_remove,
	.shutdown       = sunxi_wdt_shutdown,
	.suspend        = sunxi_wdt_suspend,
	.resume         = sunxi_wdt_resume,
	.driver         = {
		.owner  = THIS_MODULE,
		.name   = DRV_NAME,
	},
};

static int __init sunxi_wdt_init_module(void)
{
	int err;

	pr_info("%s: sunxi WatchDog Timer Driver v%s\n", __func__, DRV_VERSION);

	err = platform_driver_register(&sunxi_wdt_driver);
	if(err)
		goto err_driver_register;

	platform_device = platform_device_register_simple(DRV_NAME, -1, sunxi_wdt_res, ARRAY_SIZE(sunxi_wdt_res));
	if(IS_ERR(platform_device)) {
		err = PTR_ERR(platform_device);
		goto err_platform_device;
	}

	return err;

err_platform_device:
	platform_driver_unregister(&sunxi_wdt_driver);
err_driver_register:
	return err;
}

static void __exit sunxi_wdt_cleanup_module(void)
{
	platform_device_unregister(platform_device);
	platform_driver_unregister(&sunxi_wdt_driver);
	pr_info("%s: module unloaded\n", __func__);
}

module_init(sunxi_wdt_init_module);
module_exit(sunxi_wdt_cleanup_module);

MODULE_AUTHOR("huangshr <huangshr@allwinnertech.net>");
MODULE_DESCRIPTION("sunxi Watchdog Timer Driver");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(WATCHDOG_MINOR);

