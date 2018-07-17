#include <linux/module.h>   /* MODULE_LICENSE 相关的宏定义 */
#include <linux/init.h>     /* module_init 函数定义 */
#include <linux/fs.h>       /* file_operations 需要的头文件 */
#include <linux/cdev.h>     /* 初始化字符设备需要的头文件 */

#include <linux/slab.h>		  /* kmalloc，分配内存需要的头文件 */
#include <linux/mm.h>       /* SetPageReserved,设置为保留页时用到 */
#include <linux/device.h>   /* 设备文件创建所需 */
#include <linux/timer.h>    /* 定时器所需 */
#include <linux/delay.h>    /* 包含mdelay, msleep延时函数 */

#include <linux/mutex.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>

#include <linux/videodev2.h>
