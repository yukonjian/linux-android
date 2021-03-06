1. 3.10后的新内核中，proc_dir_entry的定义从include/linuc/proc_fs.h挪到了fs/proc/internal.h
  但是驱动总还是应该包含头文件proc_fs.h

2. 在proc下创建目录
struct proc_dir_entry *mytest_dir = proc_mkdir("mytest", NULL);
成功：返回目录指针
失败：返回 NULL

3. 在创建的目录下创建文件
static inline struct proc_dir_entry *proc_create(const char *name, mode_t mode,
 struct proc_dir_entry *parent, const struct file_operations *proc_fops);
成功：返回目录指针
失败：返回 NULL
name就是要创建的文件名。
mode是文件的访问权限，以UGO的模式表示。
parent与proc_mkdir中的parent类似。也是父文件夹的proc_dir_entry对象。
proc_fops就是该文件的操作函数了。
sample: struct proc_dir_entry *mytest_file = proc_create("mytest", 00644, mytest_dir, &mytest_proc_fops);
4. 删掉创建的目录
remove_proc_entry(char *, struct proc_dir_entry *);
/* 删除 /proc/base/base 文件，dir_base为/proc/base目录entry指针 */
remove_proc_entry("base/base", NULL);
remove_proc_entry("base", dir_base);
/* 删除/Proc/base目录 */
remove_proc_entry("base", NULL);

5. 使用echo和cat操作文件
cat 命令：先打开文件，再调用read函数，一直调用read函数，直到read函数返回0（read读取到文件末尾会返回0）；
echo 命令：先打开文件，再调用write函数，一直调用write函数，直到wriet返回的值的和 与 写入的字节数一致；
注：1.cat和echo无法在串口调用/dev/xxx的文件节点。只能在app中用system("cat /dev/xxx")调用
    2. 在cat /sys/device/file（读sys系统下的文件）下的文件时，只会触发一次read函数，read函数返回的值，
    即为有效的读取个数，会被显示出来。

6. 2.6.x内核的创建方法
#define  MKENTRY(name,rp,wp,pri,parent)     \
    do{                                     \
struct proc_dir_entry *proc;        \
    proc=create_proc_entry(name,S_IRUGO | S_IWUGO | S_IXUGO, parent); \
    if (proc)                       \
{                               \
    proc->read_proc  = rp;      \
    proc->write_proc = wp;      \
    proc->data       = pri;     \
}                               \
    }while(0)

#define  RMENTRY(name,parent)          \
    remove_proc_entry(name, parent)

/* 文件的读写函数 */
static int glcd_proc_read_refresh(char *page, char **start, off_t off,int count, int *eof, void *data)
{
	return 0;
}

static int glcd_proc_write_contrast(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
	return count;
}
