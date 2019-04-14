1. mmap
/**
 * remap_pfn_range - remap kernel memory to userspace
 * @vma: user vma to map to
 * @addr: target user address to start at
 * @pfn: physical address of kernel memory(以页为单位, phy_addr >> PAGE_SHIFT)
 * @size: size of map area
 * @prot: page protection flags for this mapping
 *
 *  Note: this is only safe if the mm semaphore is held when called.
 */
int remap_pfn_range(struct vm_area_struct *vma, unsigned long virt_addr, unsigned long pfn, unsigned long size, pgprot_t prot);

instance :

2.ioctal
long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
_IO(type,nr) //没有参数的命令
_IOR(type,nr,size) //该命令是从驱动读取数据
_IOW(type,nr,size) //该命令是从驱动写入数据
_IOWR(type,nr,size) //双向数据传输
type:幻数  nr:序数  size:数据大小，只需要填写数据类型 example:int,struct test;

注：
1、由于在内核驱动中都没有看到数据的判断，故可以不加判断
2、驱动中直接使用 _IO 号，而不必是nr
3、幻数type，我们一般使用 ‘x’ ,其在内核中并未使用
