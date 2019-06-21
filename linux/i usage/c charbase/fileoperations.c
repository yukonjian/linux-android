static int test_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int test_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t test_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static ssize_t test_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static int test_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}


const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= test_open,
	.read		= test_read,
	.write		= test_write,
	.unlocked_ioctl = test_ioctl,
	.release	= test_release,
};
