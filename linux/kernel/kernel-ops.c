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
