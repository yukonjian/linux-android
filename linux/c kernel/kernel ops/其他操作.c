1.用于函数返回值的错误检查。
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

13.调试打印信息
cat /proc/sys/kernel/printk
4 4 1 7
第一个“4”表示内核打印函数printk的打印级别
不够打印级别的信息会被写到日志中可通过dmesg 命令来查看
KERN_DEBUG; KERN_INFO; KERN_WARNING; KERN_ERR;
#define xxx_inf(fmt,msg...)     do { printk(KERN_WARNING "[XXX] %s,line:%d:"fmt,__func__,__LINE__,##msg);}while(0)

2.链表
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
