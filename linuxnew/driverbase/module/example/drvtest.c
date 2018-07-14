#include <linux/module.h>
#include <linux/init.h>
#include "drvtest.h"


static int __init drvtest_init(void)
{
	printk_dbg("init \n");
	return 0;
}

static void __exit drvtest_exit(void)
{
	printk_dbg("exit \n");
}

module_init(drvtest_init);
module_exit(drvtest_exit);

MODULE_LICENSE("GPL");


