1.设备号的分配
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
dev:获取的第一个设备号
baseminor:次设备号的起始值
count:连续分配设备号的个数
name:主设备号的名字    //cat /proc/devices
注：多次调用，会分配多个主设备号
int register_chrdev_region(dev_t first,unsigned int count,char *name)
first :已知的起始设备号的值,MKDEV(TTY_MAJOR, 0);
count:连续编号范围.
name:编号相关联的设备名称. (/proc/devices);
sample:
#define CHAR_BASE 50
register_chrdev_region(MKDEV(CHAR_BASE, 0), 1, "devno_char0");
register_chrdev_region(MKDEV(CHAR_BASE, 1), 3, "devno_char1");
//cat /proc/devices
50 devno_char0
50 devno_char1		//连续3个分配也是统一一起表示

2.注册字符设备
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *cdev, dev_t dev, unsigned count)
注：cdev_add中连续添加count个的设备号，共享同一个cdev

4.字符设备的删除和设备号的注销
void cdev_del(struct cdev *cdev)
void unregister_chrdev_region(dev_t from, unsigned count)

5.以前的字符设备注册（一般用于知道设备号）
int register_chrdev (unsigned int major, const  char *name, struct file_operations*fops)
major:主设备号；如果等于0，则表示采用系统动态分配的主设备号。
注：函数调用__register_chrdev(major, 0, 256, name, fops);包含次设备号为0~256的设备号

void unregister_chrdev(unsigned int major, const char *name);

2. 查看设备号
2.1 设备号长度为32位，12位表示主设备号，20位表示次设备号,主次设备号范围均为：0~255
cat /proc/devices   //查看分配了的主设备号，及设备号的名字
ls -l /dev/devfile        //查看设备文件的主设备号和次设备号

2.2 设备号中获取主次设备号
MKDEV：  是用来将主设备号和次设备号，转换成设备号。(主设备号其实是次设备号为零的设备号)
MAJOR：  从设备号里面提取出来主设备号。
MINOR： 从设备号中提取出来次设备号。

2.3 从设备节点获取主次设备号
static inline unsigned iminor(const struct inode *inode)
{
	return MINOR(inode->i_rdev);
}

static inline unsigned imajor(const struct inode *inode)
{
	return MAJOR(inode->i_rdev);
}

3. 驱动中动态创建设备节点
struct class *my_class;
struct class *class_create(struct module *owner, const char *name)
struct device *device_create(struct class *class, struct device *parent, dev_t devt,
   void *drvdata, const char *fmt, ...)
dev_t devt ：设备号
sample:
display_dev = device_create(disp_class, NULL, devid, NULL, "disp");

void device_destroy(struct class *class, dev_t devt)
void class_destroy(struct class *cls)
