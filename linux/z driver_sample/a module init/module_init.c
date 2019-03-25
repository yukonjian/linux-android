#include <linux/module.h>
#include <linux/init.h>
#include "drvtest.h"


static int __init xxx_init(void)
{
	printk_dbg("init \n");
	return 0;
}

static void __exit xxx_exit(void)
{
	printk_dbg("exit \n");
}

module_init(xxx_init);
module_exit(xxx_exit);

MODULE_LICENSE("GPL");
