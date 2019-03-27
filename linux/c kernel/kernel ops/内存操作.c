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
