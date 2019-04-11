1. 虚拟内存区域(virtual memory areas)
进程的虚拟内存空间会被分成不同的若干区域,linux内核中，这样的区域被称之为虚拟内存区域
其中的每一个vma节点对应着一段连续的进程内存。这里的连续是指在进程空间中连续，物理空间中不一定连续。
如果使用malloc等申请一段内存，则内核会给进程增加vma节点。
struct vm_area_struct {
	struct mm_struct * vm_mm;	/* 所属的内存描述符 */
	unsigned long vm_start;    /* vma的起始地址 */
	unsigned long vm_end;		/* vma的结束地址 */
  pgprot_t vm_page_prot;		/* vma的访问权限 */
  unsigned long vm_flags;    /* 标识集 */

  unsigned long vm_pgoff;		/* 映射文件的偏移量,相对于映射的物理地址开始的偏移量，以PAGE_SIZE为单位 */
  struct file * vm_file;		    /* 映射的文件，没有则为NULL */
}

static int remap_pfn_mmap(struct file *file, struct vm_area_struct *vma)
{
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
    unsigned long pfn_start = (virt_to_phys(kbuff) >> PAGE_SHIFT) + vma->vm_pgoff;
    unsigned long virt_start = (unsigned long)kbuff + offset;
    unsigned long size = vma->vm_end - vma->vm_start;
    int ret = 0;

    printk("phy: 0x%lx, offset: 0x%lx, size: 0x%lx\n", pfn_start << PAGE_SHIFT, offset, size);

    ret = remap_pfn_range(vma, vma->vm_start, pfn_start, size, vma->vm_page_prot);
    if (ret)
        printk("%s: remap_pfn_range failed at [0x%lx  0x%lx]\n",
            __func__, vma->vm_start, vma->vm_end);
    else
        printk("%s: map 0x%lx to 0x%lx, size: 0x%lx\n", __func__, virt_start,
            vma->vm_start, size);

    return ret;
}
remap_pfn_range将物理页帧号pfn_start对应的物理内存映射到用户空间的vm->vm_start处，映射长度为该虚拟内存区的长度。
由于这里的内核缓冲区是用kzalloc分配的，保证了物理地址的连续性，
所以会将物理页帧号从pfn_start开始的（size >> PAGE_SHIFT）个连续的物理页帧依次按序映射到用户空间。
