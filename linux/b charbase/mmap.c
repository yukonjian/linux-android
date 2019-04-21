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

3. remap_pfn_range  (io_remap_pfn_range)
int remap_pfn_range(struct vm_area_struct *vma, unsigned long virt_addr, unsigned long pfn,
    unsigned long size, pgprot_t prot);
vma:用户层使用的vma
virt_addr:用户的起始地址
pfn:内核空间的物理地址,以页为单位
size:映射大小
prot：页保护标志
关于虚存管理的最基本的管理单元应该是struct vm_area_struct了，它描述的是一段连续的、具有相同访问属性的虚存空间，
该虚存空间的大小为物理内存页面的整数倍。
在将地址映射到用户空间，需先将其设置为保留页。
sample:
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
