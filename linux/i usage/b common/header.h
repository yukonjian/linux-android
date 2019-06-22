#include <linux/module.h>		/* 模块必须的头问题 */
#include <linux/init.h>			/* 模块初始化会使用到，module_init */
#include <linux/fs.h>		/* struct file_operations */
#include <linux/interrupt.h> /* request_irq 和 tasklet */
