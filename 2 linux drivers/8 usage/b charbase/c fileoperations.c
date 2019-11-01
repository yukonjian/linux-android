static int xxxx_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int xxxx_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t xxxx_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static ssize_t xxxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static int xxxx_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}


const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= xxxx_open,
	.read		= xxxx_read,
	.write		= xxxx_write,
	.unlocked_ioctl = xxxx_ioctl,
	.release	= xxxx_release,
};
