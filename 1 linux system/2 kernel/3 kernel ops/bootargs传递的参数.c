参考文档：
https://blog.csdn.net/funkunho/article/details/51967137

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>


static char *cmdline = NULL;

static int deviceid_setup(char *s)
{
	cmdline = s;
	if(cmdline == NULL)
		printk("DEVICEID is NULL\n;");
	else
		printk("DEVICEID:%s;\n", cmdline);

	return 1;
}

/* 当bootargs有 DEVICEID的参数时，会运行deviceid_setup函数 */
__setup("DEVICEID", deviceid_setup);


int deviceid_get(char *data, int count)
{
	if(cmdline == NULL)
		return -1;

}

static int __init deviceid_get_init(void)
{
	printk("deviceid module init \n");
	return 0;
}

static void __exit deviceid_get_exit(void)
{
	printk("deviceid module exit \n");
}

module_init(deviceid_get_init);
module_exit(deviceid_get_exit);

MODULE_LICENSE("GPL");
