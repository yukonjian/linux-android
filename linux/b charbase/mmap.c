1. 虚拟内存区域(virtual memory areas)
进程的虚拟内存空间会被分成不同的若干区域,linux内核中，这样的区域被称之为虚拟内存区域
其中的每一个vma节点对应着一段连续的进程内存。这里的连续是指在进程空间中连续，物理空间中不一定连续。
如果使用malloc等申请一段内存，则内核会给进程增加vma节点。
struct vm_area_struct {
	unsigned long vm_start;    /* vma的起始地址 */
	unsigned long vm_end;		/* vma的结束地址 */
  pgprot_t vm_page_prot;		/* vma的访问权限 */
  unsigned long vm_flags;    /* 标识集 */

  unsigned long vm_pgoff;		/* 映射文件的偏移量，以PAGE_SIZE为单位 */
  struct file * vm_file;		    /* 映射的文件，没有则为NULL */
}

2. map
void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
int munmap(void* start,size_t length);

mmap()必须以PAGE_SIZE为单位进行映射，而内存也只能以页为单位进行映射，若要映射非
PAGE_SIZE整数倍的地址范围，要先进行内存对齐，强行以PAGE_SIZE的倍数大小进行映射。
#define PAGE_ALIGN(addr)    (((addr)+PAGE_SIZE-1)&PAGE_MASK)
start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
length:
port可以通过or运算合理地组合在一起
length：映射区的长度。//长度单位是 以字节为单位，不足一内存页按一内存页处理
prot：(protect)期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理
地组合在一起
PROT_EXEC //页内容可以被执行
PROT_READ //页内容可以被读取
PROT_WRITE //页可以被写入
PROT_NONE //页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。
MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。
off_t offset：被映射对象内容的起点。offset参数一般设为0，表示从文件头开始映射。

不成功返回MAP_FAILED ((void*)-1)

example : mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);

static int glcdfb_mmap(struct fb_info *info, struct file *file,
	struct vm_area_struct *vma)
{
	unsigned long start, len, off = vma->vm_pgoff << PAGE_SHIFT;

	start = info->fix.smem_start;
	len = PAGE_ALIGN((start & ~PAGE_MASK) + info->fix.smem_len);

	if ((vma->vm_end - vma->vm_start + off) > len)
	return -EINVAL;

	off += start & PAGE_MASK;
	vma->vm_pgoff >>= PAGE_SHIFT;
	vma->vm_flags |= VM_IO;

	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
		vma->vm_end - vma->vm_start,
		vma->vm_page_prot);
}
