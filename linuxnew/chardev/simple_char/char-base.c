1.设备的注册和注销
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *p, dev_t dev, unsigned count)

void cdev_del(struct cdev *p)
void unregister_chrdev_region(dev_t from, unsigned count)

2.驱动中动态创建设备节点
struct class *my_class;
struct class *class_create(struct module *owner, const char *name)
struct device *device_create(struct class *class, struct device *parent, dev_t devt,
   void *drvdata, const char *fmt, ...)
dev_t devt ：设备号
sample:
display_dev = device_create(disp_class, NULL, devid, NULL, "disp");

void device_destroy(struct class *class, dev_t devt)
void class_destroy(struct class *cls)

3. file指针操作
struct file {
    struct inode  *inode;
    void			*private_data;
    loff_t			f_pos;
};

struct inode {

};

static inline struct inode *file_inode(struct file *f)
{
	return f->f_inode;
}
