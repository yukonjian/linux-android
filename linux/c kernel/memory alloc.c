1. kmalloc vmalloc

1) kmalloc保证分配的内存在物理上是连续的
2) vmalloc保证的是在虚拟地址空间上的连续
3) kmalloc能分配的大小有限,vmalloc能分配的大小相对较大
4) 内存只有在要被DMA访问的时候才需要物理上连续
5) vmalloc比kmalloc要慢

2. kmalloc和get_free_page申请的内存位于物理内存映射区域，
而且在物理上也是连续的，它们与真实的物理地址只有一个固定的偏移，因此存在较简单的转换关系
1) unsigned long virt_to_phys(volatile void * address)
2) void * phys_to_virt(unsigned long address)
