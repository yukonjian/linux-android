1. 3.10后的新内核中，proc_dir_entry的定义从include/linuc/proc_fs.h挪到了fs/proc/internal.h
  但是驱动总还是应该包含头文件proc_fs.h

2. 在proc下创建目录
struct proc_dir_entry *mytest_dir = proc_mkdir("mytest", NULL);

3. 在创建的目录下创建文件
static inline struct proc_dir_entry *proc_create(const char *name, mode_t mode,
 struct proc_dir_entry *parent, const struct file_operations *proc_fops);
name就是要创建的文件名。
mode是文件的访问权限，以UGO的模式表示。
parent与proc_mkdir中的parent类似。也是父文件夹的proc_dir_entry对象。
proc_fops就是该文件的操作函数了。
struct proc_dir_entry *mytest_file = proc_create("mytest", 0x0644, mytest_dir, &mytest_proc_fops);
4. 删掉创建的目录
remove_proc_entry(name, parent);
