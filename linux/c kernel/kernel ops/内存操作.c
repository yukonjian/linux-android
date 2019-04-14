1.kmalloc kfree vmalloc
1) kmalloc保证分配的内存在物理上是连续的
2) vmalloc保证的是在虚拟地址空间上的连续
3) kmalloc能分配的大小有限,vmalloc能分配的大小相对较大
4) 内存只有在要被DMA访问的时候才需要物理上连续
5) vmalloc比kmalloc要慢
port = kmalloc(sizeof(struct hp300_port), GFP_KERNEL);
if (!port)
	return -ENOMEM;

kfree(port);
1.2 kmalloc和get_free_page申请的内存位于物理内存映射区域，
而且在物理上也是连续的，它们与真实的物理地址只有一个固定的偏移，因此存在较简单的转换关系
1) unsigned long virt_to_phys(volatile void * address)
2) void * phys_to_virt(unsigned long address)

2.io映射操作
void __iomem *of_iomap(struct device_node *node, int index);
通过设备结点直接进行设备内存区间的 ioremap()，index是内存段的索引。若设备结点的reg属性有多段，
可通过index标示要ioremap的是哪一段，只有1段的情况，    index为0。采用Device Tree后，
大量的设备驱动通过of_iomap()进行映射，而不再通过传统的ioremap。
of_iomap(pdev->dev.of_node, counter)

static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
static inline void iounmap(void __iomem *addr)

3.内核与用户空间的数据拷贝
unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
unsigned long copy_to_user(void __user *to, const void *from, unsigned long n)
Returns number of bytes that could not be copied.
On success, this will be zero.
if (copy_from_user(&ax25_ctl, arg, sizeof(ax25_ctl)))
  return -EFAULT;

get_user(x, ptr); put_user(x, ptr);
复制的内存是简单类型，如char,int ,long等
int val;
put_user(val, (int __user *)arg);
get_user(val, (int __user *)arg);
Returns zero on success, or -EFAULT on error.
