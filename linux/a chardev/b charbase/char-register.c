1.设备号的分配
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
dev:获取的第一个设备号
baseminor:次设备号的起始值
count:连续分配设备号的个数
name:主设备号的名字    //cat /proc/devices
注：多次调用，会分配多个主设备号
int register_chrdev_region(dev_t first,unsigned int count,char *name)
first :要分配的设备编号范围的初始值(次设备号常设为0);
count:连续编号范围.
name:编号相关联的设备名称. (/proc/devices);

2.注册字符设备
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *p, dev_t dev, unsigned count)

4.字符设备的删除和设备号的注销
void cdev_del(struct cdev *p)
void unregister_chrdev_region(dev_t from, unsigned count)

3.注册字符设备（一般用于知道设备号）
int register_chrdev (unsigned int major, const  char *name, struct file_operations*fops)
major:主设备号；如果等于0，则表示采用系统动态分配的主设备号。

void unregister_chrdev(unsigned int major, const char *name); 

2. 查看设备号
设备号长度为32位，12位表示主设备号，20位表示次设备号
cat /proc/devices   //查看分配了的主设备号
ls -al /dev/        //查看设备文件的主设备号和次设备号

MKDEV：  是用来将主设备号和次设备号，转换成一个主次设备号的。(设备号)
MAJOR：   从设备号里面提取出来主设备号的。
MINOR宏：从设备号中提取出来次设备号的。