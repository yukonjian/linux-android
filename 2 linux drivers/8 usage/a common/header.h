#include <linux/module.h>   /* MODULE_LICENSE 相关的宏定义 */
#include <linux/init.h>     /* module_init 函数定义 */
#include <linux/fs.h>       /* file_operations 需要的头文件 */
#include <linux/proc_fs.h> /* proc文件系统 */
#include <linux/cdev.h>     /* 初始化字符设备需要的头文件 */

#include <linux/slab.h>		  /* kmalloc，分配内存需要的头文件 */
#include <linux/mm.h>       /* SetPageReserved,设置为保留页时用到 */

#include <linux/timer.h>    /* 定时器所需 */
#include <linux/delay.h>    /* 包含mdelay, msleep延时函数 */

#include <linux/mutex.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>

#include <linux/interrupt.h> /* request_irq 和 tasklet */
#include <linux/workqueue.h>  /* 工作队列需要 */

#include <linux/videodev2.h>
#include <linux/gpio.h>

#include <linux/kobject.h>   /* kobject 操作相关函数 */
#include <linux/device.h>   /* 设备文件创建所需 */
#include <linux/platform_device.h>  /* 平台设备需要的头文件 */
#include <linux/of.h>   /* 设备数操作需要的头文件 */
#include <linux/of_gpio.h> /* 读取设备数中的gpio号 */
#include <linux/sys_config.h> /* 包含struct gpio_config 结构体 */
