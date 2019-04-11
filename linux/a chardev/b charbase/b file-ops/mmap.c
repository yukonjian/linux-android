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

  unsigned long vm_pgoff;		/* 映射文件的偏移量，以PAGE_SIZE为单位 */
  struct file * vm_file;		    /* 映射的文件，没有则为NULL */
}
