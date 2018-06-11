/************************************************************
** �������� 
*************************************************************/

/*�ļ�����*/
struct file_operations {
	struct module *owner;
	int (*open) (struct inode *, struct file *);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);	
//long (*ioctl) (struct file *, unsigned int, unsigned long);			//�ϵ��ں�ʹ��
  loff_t (*llseek) (struct file *, loff_t, int);
}
/*************************************************************/
/* ���Դ�ӡ */
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
/* BUF_SIZE 10; data[BUF_SIZE]; *offset��Сֵ��0�����ֵ��BUF_SIZE����ȡ�ɹ���*offset += count; */
copy_to_user(void __user *to, const void *from, unsigned long n)
copy_from_user(void *to, const void __user *from, unsigned long n)
���أ��ɹ���ȡ���ֽ���

/*************************************************************/
/* write */
ssize_t test_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)  
/* ��д��*offset����һ�� */
���أ��ɹ�д����ֽ���

/*************************************************************/
/* llseek */
loff_t test_llseek (struct file *filp, loff_t offset, int whence)
#define SEEK_SET	0	/* seek relative to beginning of file */
#define SEEK_CUR	1	/* seek relative to current file position */
#define SEEK_END	2	/* seek relative to end of file */

/*************************************************************/
/* ioctal */
int test_ioctl (struct inode *node, struct file *filp, unsigned int cmd, unsigned long arg)
_IO(type,nr) //û�в���������
_IOR(type,nr,size) //�������Ǵ�������ȡ����
_IOW(type,nr,size) //�������Ǵ�����д������
_IOWR(type,nr,size) //˫�����ݴ���
type:����  nr:����  size:���ݴ�С��ֻ��Ҫ��д�������� example:int,struct test;
_IOC_DIR(cmd) //����������ȡ����
_IOC_TYPE(cmd) //����������ȡ����
_IOC_NR(cmd) //����������ȡ����
_IOC_SIZE(cmd) //����������ȡ���ݴ�С
����arg���Դ��� ���ݻ�ָ�룬�ڴ���ָ��ʱҪ�������ݵĿ�����copy_from_user, copy_to_user
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
/* �ڴ������ڴ�ӳ�� */
static inline void *kmalloc(size_t s, gfp_t gfp)   !!
static inline void kfree(void *p)
static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
static inline void iounmap(void __iomem *addr)

/*************************************************************/
/* �ж� */
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
��ʾ��/proc/interrupts	
17: 11 s3c-ext0 key INT_EINT1 ��ʾ��ע����ж�����
��һ����S3C2440���е��жϺ���ԭ���Ļ�ֵ�ϼ���16�����жϺ�
�ڶ��С�11���Ƕ�Ӧ��������Ӧ���жϵĴ�����
�����С�s3c-ext0���Ǵ�������жϵ��жϿ�����
������һ����֪������irq_request()ʱ������ж����֡�
�йصڶ��У����ж���Ӳ�������ʱ�򣬵ڶ���Ϊ�����жϺţ�Ҳ����ֱ��ʹ���ں˷ֿ����жϺţ���ͨ���жϺ����ĵ�һ����������
dev_id:
�����жϣ�flags Ҫ���� IRQF_SHARED, ���벻ͬ��dev_idע���ж�
����ֵ��
�ɹ�����0��ʧ�ܷ��ش�����

void free_irq(unsigned int irq, void *dev_id)

/*************************************************************/
/* �������� */
�������������ڽ��̿ռ䣬��������
1.�����������У��ڶ������ڶ��ں�
struct workqueue_struct *create_workqueue(const char *name)
struct workqueue_struct *create_singlethread_workqueue(const char *name)
2.��������
	��̬����,���岢��ʼ��һ��work_struct�����ṹ��
#define	DECLARE_WORK(work_struct,func)
static void func(struct work_struct *work);
	��̬����,��Ҫ�ȶ���һ��struct work_struct �����ṹ�壬�ٽ���ָ�������г�ʼ��
#define INIT_WORK(work_structp, func)	
3.���ȹ���
int queue_work(struct workqueue_struct *wq, struct work_struct *work)
4.��ж��ģ���ǣ���ˢ�²�ע����������
void flush_workqueue(struct workqueue_struct *wq)
void destroy_workqueue(struct workqueue_struct *wq)
5.ʹ��ϵͳ�Ĺ�������
static inline bool schedule_work(struct work_struct *work)
{
	return queue_work(system_wq, work);
}

/*************************************************************/
/* �ȴ����� */
�ó���������ߣ��ȴ������ٴα�����
1.���岢��ʼ���ȴ�����ͷ
typedef struct __wait_queue_head wait_queue_head_t;
#define init_waitqueue_head(qp)
2.���̽�������
#define wait_event_interruptible(wq, condition)	
����0�����������ѣ�
���ط�0�����߱��жϣ��������� -ERESTARTSYS
wait_event_interruptible_timeout(wq, condition, timeout) //timeout = s*HZ;
����0�����������Ѻ�ʱ�䳬ʱ��
���ط�0�����߱��жϣ��������� -ERESTARTSYS
3.���ѽ���
void wake_up_interruptible(wait_queue_head_t *queue);

/*************************************************************/
/* �ں�ʱ���붨ʱ�� */
jiffies(unsigned long)�� jiffies/HZ(�룩��

#define time_before_eq(a,b) time_after_eq(b,a)
time_before(jiffies, delay)  //delay = jiffies + HZ;
while(time_before(jiffies, delay))
schedule(); //�ó�������

set_current_state(TASK_INTERRUPTIBLE);
schedule_timeout(s*HZ);

void udelay(unsigned long usecs);	//������ʱ����æ�ȴ�
void mdelay(unsigned long msecs);

struct timer_list {
	unsigned long expires; //������ִ�ж�ʱ����������ʱ��
	void (*function)(unsigned long); //��ʱ��������
	unsigned long data; //�������Ĵ���
}

1.���岢��ʼ����ʱ��
#include <linux/timer.h>
struct timer_list mytimer;
#define init_timer(timerp)
2.��ʼ����ʱ���ṹ��� ��ʱʱ�� ��ʱ�������� ����������
void timer_func(unsigned long data) //���嶨ʱ��������
my_timer.expires = jiffies + 5*HZ; 
my_timer.function = timer_func; 
my_timer.data = (unsigned long)99;
3.���ʱ����ִֻ��һ�δ�����
void add_timer(struct timer_list *timer)

printk("time out![%d] [%s]\n", (int)data, current->comm);  //��ӡ��ǰ����

4.�ٴμ��ʱ��
my_timer.expires = jiffies + 5*HZ; 
add_timer(&my_timer); 
or:
int mod_timer(struct timer_list *timer, unsigned long expires)
5.�����ڶ�ʱ��û�г�ʱǰȡ����ʱ��,ע��ģ��ʱҪʹ��
int del_timer(struct timer_list *timer)

/*************************************************************/
/* �ź��� */
1.���岢��ʼ��
struct semaphore sem;
sema_init(&sem, count);
2.ʹ���ź���
voud down(struct semaphore *sem)	//������ܻ�ȡ���л�״̬��TASK_UNINTERRUPTIBLE*/
int down_interruputible(struct semaphore *sem)	//������ܻ�ȡ���л�״̬��TASK_INTERRUPTIBLE�����˯���ڼ䱻�жϴ�ϣ��������ط�0ֵ*/
�����践�� �CERESTARTSYS;
void up(struct semaphore *sem);

/*************************************************************/
/* platform */
struct platform_device {
	const char * name; //�豸�����֣��⽫����device->dev_id������sys/device����ʾ��Ŀ¼��
	int id; //�豸id�����ڸ�����������߲��Ҿ�����ͬname���豸��ţ����ֻ��һ���豸�Ļ���-1��
	struct device dev; //�ṹ������Ƕ��device�ṹ�塣
	u32 num_resources; //��Դ����
	struct resource * resource; //���ڴ����Դ�����顣
};
int platform_device_register(struct platform_device *pdev) //ͬ���ģ���Ҫ�жϷ���ֵ
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
flags ��IORESOURCE_MEM  IORESOURCE_IRQ



