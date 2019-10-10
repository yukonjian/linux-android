1.用于函数返回值的错误检查。
#include <linux/err.h>
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
2. 计算机数字的表示
原码：将一个整数，转换成二进制，就是其原码。
      如单字节的5的原码为：0000 0101；-5的原码为1000 0101。
反码：正数的反码就是其原码；负数的反码是将原码中，除符号位以外，每一位取反。
      如单字节的5的反码为：0000 0101；-5的反码为1111 1010。
补码：正数的补码就是其原码；负数的反码+1就是补码。
      如单字节的5的补码为：0000 0101；-5的原码为1111 1011。
在计算机中，正数是直接用原码表示的，如单字节5，在计算机中就表示为：0000 0101。
              负数用补码表示，如单字节-5，在计算机中表示为1111 1011。
例如：
-1是1000 0001，那么把负号去掉，最大的数是111 1111，也就是127，所以负数中最小能表示的数据是-127。
-128是1000 0000，其与与-127的跨度过大，在用硬件进行运算时不方便。所以，计算机中，负数是采用补码表示。
单字节-1，原码为1000 0001，反码为1111 1110，补码为1111 1111，计算机中的单字节-1就表示为1111 1111。
单字节-127，原码是1111 1111，反码1000 0000，补码是1000 0001，计算机中单字节-127表示为1000 0001。
单字节-128，原码是1000 0000，除了符号为，最大的数只能是127了，其在计算机中的表示为1000 0000。
这样-128的补码最小，-1的补码最大
2.1 计算机的运算
运算中，减去一个数，等于加上它的相反数，如：A - 127，也就相当于：A + (-127)，
负数是以补码的形式保存的，也就是负数的真值是补码，既然这样，当我们要减一个数时，直接把其补码拿过来，加一下，就OK了，去掉了减法运算。
例如：
1 + 128， 真值的运算是 0000 0001 + 1000 0000 ，如果你将结果赋值给一个单字节有符号正数，编辑器会提示你超出了表示范围。
因为运算的两个数据是无符号的，其结果也是无符号的129，而有符号单字节变量最大可以表示的是127。
1 - 128，真值的运算是 0000 0001 + 1000 0000 ，因为-128是有符号，其运算结果也是有符号，1000 0001，刚好是-127在计算机中的真值。
涉及到减和负数运算，其计算结果均为有符号的。
13.调试打印信息
cat /proc/sys/kernel/printk
4 4 1 7
第一个“4”表示内核打印函数printk的打印级别
不够打印级别的信息会被写到日志中可通过dmesg 命令来查看
KERN_DEBUG; KERN_INFO; KERN_WARNING; KERN_ERR;
#define xxx_inf(fmt,msg...)     do { printk(KERN_WARNING "[XXX] %s,line:%d:"fmt,__func__,__LINE__,##msg);}while(0)
文件的4个数字值含义， 如下所示：
1) 控制台（一般是串口） 日志级别： 当前的打印级别， 优先级高于该值的消息将被打印至控制台。
2) 默认的消息日志级别： 将用该优先级来打印没有优先级前缀的消息， 也就是在直接写printk（“xxx”） 而不带打印
级别的情况下， 会使用该打印级别。
3) 最低的控制台日志级别： 控制台日志级别可被设置的最小值（一般都是1）。
4) 默认的控制台日志级别： 控制台日志级别的默认值。
echo >> /proc/sys/kernel/printk
>: 会重写文件，如果文件里面有内容会覆盖。
>>这个是将输出内容追加到目标文件中。如果文件不存在，就创建文件。

3.链表
#include <linux/list.h>
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

struct xxx_test
{
  struct list_head member;
}
struct list_head xxx_head;
struct xxx_test *pos;
head = INIT_LIST_HEAD(xxx_head);
list_add(&pos->member, xxx_head); /* 将其链表放入链表头 */
遍历xxx_head链表，获取xxx_test指针；
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

4. linux中likely()和unlikely()
likely()与unlikely()在2.6内核中，随处可见，那为什么要用它们？它们之间有什么区别呢？
首先明确：
if (likely(value))等价于if (value)
if (unlikely(value))等价于if (value)

也就是说likely()和unlikely()从阅读和理解的角度是一样的。
这两个宏在内核中定义如下：
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
这里的__built_expect()函数是gcc(version >= 2.96)的内建函数,提供给程序员使用的，目的是将"分支转移"的信息提供给编译器，这样编译器对代码进行优化，以减少指令跳转带来的性能下降。
__buildin_expect((x), 1)表示x的值为真的可能性更大.
__buildin_expect((x), 0)表示x的值为假的可能性更大.
也就是说，使用likely(),执行if后面的语句的机会更大，使用unlikely(),执行else后面的语句机会更大一些。

通过这种方式，编译器在编译过程中，会将可能性更大的代码紧跟着后面的代码，从而减少指令跳转带来的性能上的下降。

5. BUG_ON（）和WARN_ON（）
    内核中有许多地方调用类似BUG（）的语句，它非常像一个内核运行时的断言，意味着本来不该执行到BUG（）这条语句，一旦执行即抛出Oops。BUG（）的定义为：
include/asm-generic/bug.h
#define BUG() do { \
       printk("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
       panic("BUG!"); \
} while (0)
其中panic（）定义在kernel/panic.c中，会导致内核崩溃，并打印Oops。
