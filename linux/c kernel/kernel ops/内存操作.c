1.kmalloc kfree
port = kmalloc(sizeof(struct hp300_port), GFP_KERNEL);
if (!port)
	return -ENOMEM;

kfree(port);

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

get_user(to, pfrom); put_user(to, pfrom);
复制的内存是简单类型，如char,int ,long等
int val;
return put_user(val, (int __user *)arg);
Returns zero on success, or -EFAULT on error.
