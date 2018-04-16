1.kmalloc kfree
port = kmalloc(sizeof(struct hp300_port), GFP_KERNEL);
if (!port)
	return -ENOMEM;

kfree(port);

2.用于函数返回值的错误检查。
在linux/err.h中包含了这一机制的处理，主要通过IS_ERR, PTR_ERR, ERR_PTR几个宏。
#define MAX_ERRNO       4095
#define IS_ERR_VALUE(x) unlikely((x) >= (unsigned long)-MAX_ERRNO)
/* 将错误号转化为指针，由于错误号在-1000~0间，返回的指针会落在最后一页  */
static inline void *ERR_PTR(long error)
{
         return (void *) error;
}
/* 将指针转化为错误号  */
static inline long PTR_ERR(const void *ptr)
{
         return (long) ptr;
}
/* 判断返回的指针是错误信息还是实际地址，即指针是否落在最后一页 */
static inline long IS_ERR(const void *ptr)
{
         return IS_ERR_VALUE((unsigned long)ptr);
}
对于内核中返回的指针，检查错误的方式是if( IS_ERR(retptr) 或 If( IS_ERR_VALUE(retptr) )。
static inline long __must_check IS_ERR_OR_NULL(const void *ptr)
{
       return !ptr || IS_ERR_VALUE((unsigned long)ptr);
}
sample：
对于指针类型的返回函数，在函数中将错误号转化为指针；
若函数返回的指针不合格，则将指针转换为错误号。
if (IS_ERR(dev))
  return PTR_ERR(dev);
对于错误号的返回函数，直接对返回值进行判断
if (IS_ERR_VALUE(rval))
	return rval;

3.io映射操作
void __iomem *of_iomap(struct device_node *node, int index);
通过设备结点直接进行设备内存区间的 ioremap()，index是内存段的索引。若设备结点的reg属性有多段，
可通过index标示要ioremap的是哪一段，只有1段的情况，    index为0。采用Device Tree后，
大量的设备驱动通过of_iomap()进行映射，而不再通过传统的ioremap。
of_iomap(pdev->dev.of_node, counter)

static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
static inline void iounmap(void __iomem *addr)


4.有关err的跳转操作命名，可以使用err_xxx(xxx表示发生错误的函数)

5.#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

6.信号量
struct semaphore sem;
sema_init(&sem, count);
void down(struct semaphore *sem)	//如果不能获取，切换状态至TASK_UNINTERRUPTIBLE*/
void up(struct semaphore *sem);

7.互斥量
struct mutex xxx_mutex;
void mutex_init(struct mutex *lock);
void mutex_lock(struct mutex *lock);
void mutex_unlock(struct mutex *lock);

8.定时器
struct timer_list mytimer;
void init_timer(struct timer_list *timer);
初始化定时器结构体的 超时时间 定时器处理函数 处理函数传参
void timer_func(unsigned long data) //定义定时器处理函数
my_timer.expires = jiffies + 5*HZ;
my_timer.function = timer_func;
my_timer.data = (unsigned long)99;
激活定时器，只执行一次处理函数
void add_timer(struct timer_list *timer)

再次激活定时器
my_timer.expires = jiffies + 5*HZ;
add_timer(&my_timer);
or:
int mod_timer(struct timer_list *timer, unsigned long expires)
可以修改并未结束的定时器相当于：
del_timer(timer); timer->expires = expires; add_timer(timer);
return ：mod_timer() of an inactive timer returns 0, mod_timer() of an  active timer returns 1
若想在定时器没有超时前取消定时器,注销模块时要使用
int del_timer(struct timer_list *timer)
return : del_timer() of an inactive timer returns 0, del_timer() of an  active timer returns 1

9.简单的延时，属于忙等待
void udelay(unsigned long usecs);	//该种延时属于忙等待
void mdelay(unsigned long msecs);

10.工作与工作队列
struct work_struct  commit_work;
INIT_WORK(struct work_struct * work, work_func);
typedef void (*work_func_t)(void *work);

struct workqueue_struct *Display_commit_work;
struct workqueue_struct *create_singlethread_workqueue(const char *name)

int queue_work(struct workqueue_struct *wq, struct work_struct *work)
在卸载模块是，需刷新并注销工作队列
void flush_workqueue(struct workqueue_struct *wq)
void destroy_workqueue(struct workqueue_struct *wq)

11.中断
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
IRQF_TRIGGER_RISING; IRQF_TRIGGER_FALLING; IRQF_TRIGGER_HIGH; IRQF_TRIGGER_LOW; IRQF_SHARED;

void free_irq(unsigned int irq, void *dev_id)

查看中断信息：cat /proc/interrupts

设备树中的中断的使用

unsigned int irq_of_parse_and_map(struct device_node *dev, int index)；
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
    struct of_phandle_args oirq;
    if (of_irq_parse_one(dev, index, &oirq))－－－－分析device node中的interrupt相关属性
        return 0;
    return irq_create_of_mapping(&oirq);－－－－－创建映射，并返回对应的IRQ number
}

12.内核与用户空间的数据拷贝
unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
unsigned long copy_to_user(void __user *to, const void *from, unsigned long n)
Returns number of bytes that could not be copied.
On success, this will be zero.
if (copy_from_user(&ax25_ctl, arg, sizeof(ax25_ctl)))
  return -EFAULT;

get_user(to, pfrom); put_user(to, pfrom);
复制的内存是简单类型，如char,int ,long等
int val;
return put_user(val, (int __user *)arg);
Returns zero on success, or -EFAULT on error.

13.调试打印信息
cat /proc/sys/kernel/printk
4 4 1 7
第一个“4”表示内核打印函数printk的打印级别
不够打印级别的信息会被写到日志中可通过dmesg 命令来查看
KERN_DEBUG; KERN_INFO; KERN_WARNING; KERN_ERR;
#define xxx_inf(fmt,msg...)     do { printk(KERN_WARNING "[XXX] %s,line:%d:"fmt,__func__,__LINE__,##msg);}while(0)

14.链表
struct list_head {
	struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}
list_add和list_add_tail分别是插在表头和表尾，但是都是通过__list_add实现，因为内核实现的链表是双向链表，
所以head->prev之后就是表尾，而head->next之后就是表头。
static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

 /**
  * list_entry - get the struct for this entry
  * @ptr:	the &struct list_head pointer.
  * @type:	the type of the struct this is embedded in.
  * @member:	the name of the list_struct within the struct.
  */
 #define list_entry(ptr, type, member) \
 	container_of(ptr, type, member)

  /**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

  devp = container_of(inode->i_cdev, struct test_t, test_cdev);

15.延时
#include <linux/delay.h>
void msleep(unsigned int msecs);
void usleep_range(unsigned long min, unsigned long max);
mdelay
udelay
ndelay
#include <linux/timer.h>
jiffies  HZ

16.拷贝strlcpy
函数原型声明：size_t strlcpy(char *dst, const char *src, size_t size)
头文件引用：#include <string.h>
