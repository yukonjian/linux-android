#include <linux/module.h>
#include <linux/init.h>

static int __init xxxx_init(void)
{
	printk("init \n");
	return 0;
}

static void __exit xxxx_exit(void)
{
	printk("exit \n");
}

module_init(xxxx_init);
module_exit(xxxx_exit);

MODULE_LICENSE("GPL");
