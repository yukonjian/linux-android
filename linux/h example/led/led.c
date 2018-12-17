#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/timer.h>
#include <linux/io.h>



#include <linux/slab.h>
#include <linux/device.h>


#define PIO_BASE_ADDR	0x01C20800
#define PH_BASE_ADDR	(PIO_BASE_ADDR+(7*0x24))

#define PH_CFG0_OFF		0x00
#define PH_CFG1_OFF		0x04
#define PH_CFG2_OFF		0x08
#define PH_CFG3_OFF		0x0c
#define PH_DATA_OFF		0x10

#define PH2_CFG0		(7<<8)	
#define PH9_CFG1		(7<<4)		
#define PH10_CFG1		(7<<8)		
#define PH11_CFG1		(7<<12)		
#define PH12_CFG1		(7<<16)		
#define PH13_CFG1		(7<<20)		
#define PH14_CFG1		(7<<24)		
#define PH15_CFG1		(7<<28)	

#define PH2_OUT			(1<<8)
#define PH9_OUT			(1<<4)
#define PH10_OUT		(1<<8)
#define PH11_OUT		(1<<12)
#define PH12_OUT		(1<<16)
#define PH13_OUT		(1<<20)
#define PH14_OUT		(1<<24)
#define PH15_OUT		(1<<28)

#define PH2_DATA_MASK	(1<<2)
#define PH9_DATA_MASK	(1<<9)
#define PH10_DATA_MASK	(1<<10)
#define PH11_DATA_MASK	(1<<11)
#define PH12_DATA_MASK	(1<<12)
#define PH13_DATA_MASK	(1<<13)
#define PH14_DATA_MASK	(1<<14)
#define PH15_DATA_MASK	(1<<15)


#define PH2_DATA_BIT	(2)
#define PH9_DATA_BIT	(9)
#define PH10_DATA_BIT	(10)
#define PH11_DATA_BIT	(11)
#define PH12_DATA_BIT	(12)
#define PH13_DATA_BIT	(13)
#define PH14_DATA_BIT	(14)
#define PH15_DATA_BIT	(15)

#define LED_ON			(0)
#define LED_OFF			(1)

#define C72_LED_IOCTL			(0xa000)
#define C72_LED_SOUND_ON		(C72_LED_IOCTL + 1)
#define C72_LED_SOUND_OFF		(C72_LED_IOCTL + 2)
#define C72_LED_PHONE_ON		(C72_LED_IOCTL + 3)
#define C72_LED_PHONE_OFF		(C72_LED_IOCTL + 4)
#define C72_LED_MEETING_ON		(C72_LED_IOCTL + 5)
#define C72_LED_MEETING_OFF		(C72_LED_IOCTL + 6)
#define C72_LED_LOCK_ON			(C72_LED_IOCTL + 7)
#define C72_LED_LOCK_OFF		(C72_LED_IOCTL + 8)
#define C72_LED_POWER_ON		(C72_LED_IOCTL + 9)
#define C72_LED_POWER_OFF		(C72_LED_IOCTL + 10)
#define C72_LED_MESSAGE_ON		(C72_LED_IOCTL + 11)
#define C72_LED_MESSAGE_OFF		(C72_LED_IOCTL + 12)
#define C72_LED_ALARM_RED_ON	(C72_LED_IOCTL + 13)
#define C72_LED_ALARM_BLUE_ON	(C72_LED_IOCTL + 14)
#define C72_LED_ALARM_OFF		(C72_LED_IOCTL + 15)




static int c72_led_debug_enable = 1;
#define dprintk(fmt, arg...) \
	do { if (c72_led_debug_enable) printk(KERN_DEBUG fmt, ##arg); } while (0)


struct c72_led_info{
	struct cdev cdev;
	dev_t devno;
	struct class * led_class;
	volatile void __iomem *led_virtual_addr;
};

struct c72_led_info * c72_led_infop;

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
void port_reg_clr( volatile void __iomem * reg, u32 clr_bits)
{
	u32 v = (u32)reg_readl(reg);
	reg_writel(reg, v & ~clr_bits);
}

static inline
void port_reg_set(volatile void __iomem * reg, u32 set_bits)
{
	u32 v = reg_readl(reg);
	reg_writel(reg, v | set_bits);
}

//clr_bits for mask
static inline
void port_reg_clr_set(volatile void __iomem * reg, u32 clr_bits, u32 set_bits)
{
	u32 v = (u32)reg_readl(reg);
	reg_writel(reg, (v & ~clr_bits) | (set_bits & clr_bits));
}

static void led_config_set(void)
{
	//PH2
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_CFG0_OFF, PH2_CFG0, PH2_OUT);
	//PH2,PH9~15
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_CFG1_OFF, PH9_CFG1 | PH10_CFG1 | PH11_CFG1 | PH12_CFG1 | PH13_CFG1 | PH14_CFG1 | PH15_CFG1,\
					PH9_OUT | PH10_OUT | PH11_OUT | PH12_OUT | PH13_OUT | PH14_OUT | PH15_OUT);	
}
/*
static void led_light(void)
{
	//led_port1~4 -> PH9~12
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH9_DATA_MASK, LED_ON<<PH9_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH10_DATA_MASK, LED_ON<<PH10_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH11_DATA_MASK, LED_ON<<PH11_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH12_DATA_MASK, LED_ON<<PH12_DATA_BIT);	
}

static void led_flicker(void)
{
	//LEDboard_1~4 -> PH13~15,PH2
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH13_DATA_MASK, flicker_status<<PH13_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH14_DATA_MASK, (!flicker_status)<<PH14_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH15_DATA_MASK, LED_ON<<PH15_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH2_DATA_MASK, LED_ON<<PH2_DATA_BIT);	
	
}

static void ph_led_timer_func(unsigned long data)
{
	printk(KERN_ERR"ph_led_timer_func starting\n");

	led_flicker();
	flicker_status = !flicker_status;
	mod_timer(&ph_led_timer, jiffies + HZ*5);
}
*/





int c72_led_open(struct inode * indoe, struct file * filp)
{
	return 0;
}
int c72_led_release(struct inode * inode, struct file * filp)
{
	return 0;
}
void c72_led_sound_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH9_DATA_MASK, LED_ON<<PH9_DATA_BIT);
}
void c72_led_sound_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH9_DATA_MASK, LED_OFF<<PH9_DATA_BIT);
}
void c72_led_phone_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH10_DATA_MASK, LED_ON<<PH10_DATA_BIT);
}
void c72_led_phone_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH10_DATA_MASK, LED_OFF<<PH10_DATA_BIT);
}
void c72_led_meeting_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH11_DATA_MASK, LED_ON<<PH11_DATA_BIT);
}
void c72_led_meeting_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH11_DATA_MASK, LED_OFF<<PH11_DATA_BIT);
}
void c72_led_lock_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH12_DATA_MASK, LED_ON<<PH12_DATA_BIT);
}
void c72_led_lock_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH12_DATA_MASK, LED_OFF<<PH12_DATA_BIT);
}
void c72_led_power_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH15_DATA_MASK, LED_ON<<PH15_DATA_BIT);
}
void c72_led_power_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH15_DATA_MASK, LED_OFF<<PH15_DATA_BIT);
}
void c72_led_message_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH2_DATA_MASK, LED_ON<<PH2_DATA_BIT);
}
void c72_led_message_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH2_DATA_MASK, LED_OFF<<PH2_DATA_BIT);
}
void c72_led_alarm_red_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH13_DATA_MASK, LED_OFF<<PH13_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH14_DATA_MASK, LED_ON<<PH14_DATA_BIT);
}
void c72_led_alarm_blue_on(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH13_DATA_MASK, LED_ON<<PH13_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH14_DATA_MASK, LED_OFF<<PH14_DATA_BIT);
}
void c72_led_alarm_off(void)
{
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH13_DATA_MASK, LED_OFF<<PH13_DATA_BIT);
	port_reg_clr_set(c72_led_infop->led_virtual_addr+PH_DATA_OFF, PH14_DATA_MASK, LED_OFF<<PH14_DATA_BIT);

}

void c72_all_led_off(void)
{
	c72_led_sound_off();
	c72_led_phone_off();
	c72_led_meeting_off();
	c72_led_lock_off();
	c72_led_power_off();
	c72_led_message_off();
	c72_led_alarm_off();
}





long c72_led_ioctl(struct file * filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case C72_LED_SOUND_ON: 
			c72_led_sound_on();
			break;
		case C72_LED_SOUND_OFF:
			c72_led_sound_off();
			break;
		case C72_LED_PHONE_ON:
			c72_led_phone_on();
			break;
		case C72_LED_PHONE_OFF:
			c72_led_phone_off();
			break;			
		case C72_LED_MEETING_ON:
			c72_led_meeting_on();
			break;
		case C72_LED_MEETING_OFF:
			c72_led_meeting_off();
			break;
		case C72_LED_LOCK_ON:
			c72_led_lock_on();
			break;
		case C72_LED_LOCK_OFF:
			c72_led_lock_off();
			break;
		case C72_LED_POWER_ON:
			c72_led_power_on();
			break;
		case C72_LED_POWER_OFF:
			c72_led_power_off();
			break;			
		case C72_LED_MESSAGE_ON:
			c72_led_message_on();
			break;
		case C72_LED_MESSAGE_OFF:
			c72_led_message_off();
			break;
		case C72_LED_ALARM_RED_ON:
			c72_led_alarm_red_on();
			break;
		case C72_LED_ALARM_BLUE_ON:
			c72_led_alarm_blue_on();
			break;
		case C72_LED_ALARM_OFF:
			c72_led_alarm_off();
			break;
		default :
			printk("Error command\n");
		
	}
	return 0;
}


struct file_operations c72_led_fops = {	
	.open  = c72_led_open,
	.release = c72_led_release,
	.unlocked_ioctl = c72_led_ioctl,
};

static int __init c72_led_init(void)
{
	int retval = 0;

	c72_led_infop = kmalloc(sizeof(struct c72_led_info), GFP_KERNEL);
	if(!c72_led_infop)
		return -ENOMEM;

	retval = alloc_chrdev_region(&c72_led_infop->devno, 0, 1, "c72_led");
	if(IS_ERR_VALUE(retval))
		goto free_mem;
	cdev_init(&c72_led_infop->cdev, &c72_led_fops);
	c72_led_fops.owner = THIS_MODULE;
	retval = cdev_add(&c72_led_infop->cdev, c72_led_infop->devno, 1);
	if(IS_ERR_VALUE(retval))
		goto unregister_devno;		

	c72_led_infop->led_virtual_addr = ioremap(PH_BASE_ADDR, 20);
	c72_all_led_off();
	led_config_set();	
	c72_all_led_off();

	c72_led_infop->led_class = class_create(THIS_MODULE,"led_class");
	if(IS_ERR(c72_led_infop->led_class)){
		retval = PTR_ERR(c72_led_infop->led_class);
		dprintk("The class allocate faiulre.\n");
		goto delete_cdev;	
	}	
	device_create(c72_led_infop->led_class,NULL,c72_led_infop->devno,NULL,"c72_led");
	dprintk("The led init.\n");

	return 0;
	
	delete_cdev:
		cdev_del(&c72_led_infop->cdev);	
	unregister_devno:
		unregister_chrdev_region(c72_led_infop->devno,1);
	free_mem:
		kfree(c72_led_infop);
		
	return retval;
}

static void __exit c72_led_exit(void)
{
	device_destroy(c72_led_infop->led_class,c72_led_infop->devno);
	class_destroy(c72_led_infop->led_class);
	cdev_del(&c72_led_infop->cdev);
	unregister_chrdev_region(c72_led_infop->devno,1);
	kfree(c72_led_infop);
	iounmap(c72_led_infop->led_virtual_addr);	
}
module_init(c72_led_init);
module_exit(c72_led_exit);
MODULE_LICENSE("GPL");
