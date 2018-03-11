1.设备的注册和注销
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
int cdev_add(struct cdev *p, dev_t dev, unsigned count)

void cdev_del(struct cdev *p)
void unregister_chrdev_region(dev_t from, unsigned count)
