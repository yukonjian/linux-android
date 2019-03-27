

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
