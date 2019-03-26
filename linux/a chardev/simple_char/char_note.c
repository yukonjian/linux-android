/************************************************************
** 驱动部分
*************************************************************/

/*文件操作*/
struct file_operations {
	struct module *owner;
	int (*open) (struct inode *, struct file *);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
//long (*ioctl) (struct file *, unsigned int, unsigned long);			//老的内核使用
  loff_t (*llseek) (struct file *, loff_t, int);
}
/*************************************************************/
/* 调试打印 */
static int pat_debug_enable = 1;
#define dprintk(fmt, arg...) \
	do { if (pat_debug_enable) printk(KERN_DEBUG fmt, ##arg); } while (0)

/*************************************************************/
/* open */
static int test_open(struct inode *inode, struct file *file)
/**
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)
example:
devp = container_of(inode->i_cdev, struct test_t, test_cdev);
filp->private_data = devp;

/*************************************************************/
/* close */
static int test_close(struct inode *node, struct file *filp)

/*************************************************************/
/* read */
ssize_t test_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
/* BUF_SIZE 10; data[BUF_SIZE]; *offset最小值是0，最大值是BUF_SIZE，读取成功后*offset += count; */
copy_to_user(void __user *to, const void *from, unsigned long n)
copy_from_user(void *to, const void __user *from, unsigned long n)
返回：成功读取的字节数

/*************************************************************/
/* write */
ssize_t test_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
/* 读写对*offset处理一样 */
返回：成功写入的字节数

/*************************************************************/
/* llseek */
loff_t test_llseek (struct file *filp, loff_t offset, int whence)
#define SEEK_SET	0	/* seek relative to beginning of file */
#define SEEK_CUR	1	/* seek relative to current file position */
#define SEEK_END	2	/* seek relative to end of file */

/*************************************************************/
/* ioctal */
int test_ioctl (struct inode *node, struct file *filp, unsigned int cmd, unsigned long arg)
_IO(type,nr) //没有参数的命令
_IOR(type,nr,size) //该命令是从驱动读取数据
_IOW(type,nr,size) //该命令是从驱动写入数据
_IOWR(type,nr,size) //双向数据传输
type:幻数  nr:序数  size:数据大小，只需要填写数据类型 example:int,struct test;
_IOC_DIR(cmd) //从命令中提取方向
_IOC_TYPE(cmd) //从命令中提取幻数
_IOC_NR(cmd) //从命令中提取序数
_IOC_SIZE(cmd) //从命令中提取数据大小
参数arg可以传递 数据或指针，在传递指针时要进行数据的拷贝：copy_from_user, copy_to_user
copy_from_user(&val, (struct ioctl_data *)arg, sizeof(struct ioctl_data))

/*************************************************************/
/* init */
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,
			const char *name)
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *p, dev_t dev, unsigned count)
void cdev_del(struct cdev *p)
void unregister_chrdev_region(dev_t from, unsigned count)

/*************************************************************/
/* 内存分配和内存映射 */
static inline void *kmalloc(size_t s, gfp_t gfp)   !!
static inline void kfree(void *p)
static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
static inline void iounmap(void __iomem *addr)

/*************************************************************/
/* 中断 */
int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev_id)
typedef irqreturn_t (*irq_handler_t)(int, void *);
static irqreturn_t intr_handler(int irq, void *dev_id)
enum irqreturn {
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
};
typedef enum irqreturn irqreturn_t;
flags:
#define IRQF_TRIGGER_RISING	0x00000001
#define IRQF_TRIGGER_FALLING	0x00000002
#define IRQF_TRIGGER_HIGH	0x00000004
#define IRQF_TRIGGER_LOW	0x00000008
name:
显示在/proc/interrupts
17: 11 s3c-ext0 key INT_EINT1 显示我注册和中断名字
第一处：S3C2440所有的中断号在原来的基值上加了16构成中断号
第二列“11”是对应处理器响应该中断的次数。
第三列“s3c-ext0”是处理这个中断的中断控制器
第四列一看就知道调用irq_request()时定义的中断名字。
有关第二列，当中断是硬件共享的时候，第二列为共享中断号（也可以直接使用内核分开的中断号），通过中断函数的第一个参数带入
dev_id:
分享中断，flags 要设置 IRQF_SHARED, 带入不同的dev_id注册中断
返回值：
成功返回0，失败返回错误码

void free_irq(unsigned int irq, void *dev_id)

/*************************************************************/
/* 工作队列 */
工作队列运行在进程空间，可以休眠
1.创建工作队列，第二个用于多内核
struct workqueue_struct *create_workqueue(const char *name)
struct workqueue_struct *create_singlethread_workqueue(const char *name)
2.创建工作
	静态创建,定义并初始化一个work_struct工作结构体
#define	DECLARE_WORK(work_struct,func)
static void func(struct work_struct *work);
	动态创建,需要先定义一个struct work_struct 工作结构体，再将其指针带入进行初始化
#define INIT_WORK(work_structp, func)
3.调度工作
int queue_work(struct workqueue_struct *wq, struct work_struct *work)
4.在卸载模块是，需刷新并注销工作队列
void flush_workqueue(struct workqueue_struct *wq)
void destroy_workqueue(struct workqueue_struct *wq)
5.使用系统的工作队列
static inline bool schedule_work(struct work_struct *work)
{
	return queue_work(system_wq, work);
}

/*************************************************************/
/* 等待队列 */
让程序进入休眠，等待程序再次被唤醒
1.定义并初始化等待队列头
typedef struct __wait_queue_head wait_queue_head_t;
#define init_waitqueue_head(qp)
2.进程进入休眠
#define wait_event_interruptible(wq, condition)
返回0：正常被唤醒；
返回非0：休眠被中断，驱动返回 -ERESTARTSYS
wait_event_interruptible_timeout(wq, condition, timeout) //timeout = s*HZ;
返回0：正常被唤醒和时间超时；
返回非0：休眠被中断，驱动返回 -ERESTARTSYS
3.唤醒进程
void wake_up_interruptible(wait_queue_head_t *queue);

/*************************************************************/
/* 内核时间与定时器 */
jiffies(unsigned long)， jiffies/HZ(秒）；

#define time_before_eq(a,b) time_after_eq(b,a)
time_before(jiffies, delay)  //delay = jiffies + HZ;
while(time_before(jiffies, delay))
schedule(); //让出处理器

set_current_state(TASK_INTERRUPTIBLE);
schedule_timeout(s*HZ);

void udelay(unsigned long usecs);	//该种延时属于忙等待
void mdelay(unsigned long msecs);

struct timer_list {
	unsigned long expires; //设置在执行定时器处理函数的时间
	void (*function)(unsigned long); //定时器处理函数
	unsigned long data; //处理函数的传参
}

1.定义并初始化定时器
#include <linux/timer.h>
struct timer_list mytimer;
#define init_timer(timerp)
2.初始化定时器结构体的 超时时间 定时器处理函数 处理函数传参
void timer_func(unsigned long data) //定义定时器处理函数
my_timer.expires = jiffies + 5*HZ;
my_timer.function = timer_func;
my_timer.data = (unsigned long)99;
3.激活定时器，只执行一次处理函数
void add_timer(struct timer_list *timer)

printk("time out![%d] [%s]\n", (int)data, current->comm);  //打印当前进程

4.再次激活定时器
my_timer.expires = jiffies + 5*HZ;
add_timer(&my_timer);
or:
int mod_timer(struct timer_list *timer, unsigned long expires)
5.若想在定时器没有超时前取消定时器,注销模块时要使用
int del_timer(struct timer_list *timer)

/*************************************************************/
/* 信号量 */
1.定义并初始化
struct semaphore sem;
sema_init(&sem, count);
2.使用信号量
voud down(struct semaphore *sem)	//如果不能获取，切换状态至TASK_UNINTERRUPTIBLE*/
int down_interruputible(struct semaphore *sem)	//如果不能获取，切换状态至TASK_INTERRUPTIBLE，如果睡眠期间被中断打断，函数返回非0值*/
驱动需返回 –ERESTARTSYS;
void up(struct semaphore *sem);

/*************************************************************/
/* platform */
struct platform_device {
	const char * name; //设备的名字，这将代替device->dev_id，用作sys/device下显示的目录名
	int id; //设备id，用于给插入给该总线并且具有相同name的设备编号，如果只有一个设备的话填-1。
	struct device dev; //结构体中内嵌的device结构体。
	u32 num_resources; //资源数。
	struct resource * resource; //用于存放资源的数组。
};
int platform_device_register(struct platform_device *pdev) //同样的，需要判断返回值
void platform_device_unregister(struct platform_device *pdev)

struct platform_driver {
	int (*probe)(struct platform_device *);
	int (*remove)(struct platform_device *);
	struct device_driver driver;
}
int platform_driver_register(struct platform_driver *drv)
void platform_driver_unregister(struct platform_driver *drv)

./sys/devices/platform/plat_usb_mouse.0
./sys/bus/platform/devices/plat_usb_mouse.0
./sys/bus/platform/drivers/plat_usb_mouse
./sys/bus/platform/drivers/plat_usb_mouse/plat_usb_mouse.0

struct resource {
	 resource_size_t start;
	 resource_size_t end;
	 unsigned long flags;
}
flags ：IORESOURCE_MEM  IORESOURCE_IRQ
