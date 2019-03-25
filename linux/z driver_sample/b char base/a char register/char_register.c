#include <linux/module.h>		/* 模块必须的头问题 */
#include <linux/init.h>			/* 模块初始化会使用到，module_init */

#include <linux/fs.h>		/* struct file_operations */
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
MODULE_AUTHOR("yu konjian");
MODULE_VERSION("1.0");
