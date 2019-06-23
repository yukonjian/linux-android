1.设备的注册和注销
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *p, dev_t dev, unsigned count)

void cdev_del(struct cdev *p)
void unregister_chrdev_region(dev_t from, unsigned count)



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
