#include <linux/module.h>
#include <linux/init.h>

static int __init xxx_init(void)
{
    printk("hello world!\n");
	return 0;
}

static void __exit xxx_exit(void)
{
    printk("good bye!\n");
}

module_init(xxx_init);
module_exit(xxx_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yu konjian");
MODULE_VERSION("1.0");
