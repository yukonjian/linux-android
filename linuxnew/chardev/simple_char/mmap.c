1. remap_pfn_range  (io_remap_pfn_range)
int remap_pfn_range(struct vm_area_struct *vma, unsigned long virt_addr, unsigned long pfn,
    unsigned long size, pgprot_t prot);
vma:用户层使用的vma
addr:用户的起始地址
pfn:内核空间的物理地址,以页为单位
size:映射大小
prot：页保护标志
关于虚存管理的最基本的管理单元应该是struct vm_area_struct了，它描述的是一段连续的、具有相同访问属性的虚存空间，
该虚存空间的大小为物理内存页面的整数倍。
在将地址映射到用户空间，需先将其设置为保留页。
