一. proc下的文件的创建
1. 文件的创建
static ssize_t xxxx_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	return 0;
}

static ssize_t xxxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	unsigned int lednum,addr,value;
	unsigned int virt_addr;
	sscanf(buf, "%d 0x%x", &lednum, &value);
	printk("cmd:%d;value:0x%x;\n", lednum, value);
  return count;
｝

static struct file_operations xxxx_fops = {
	.owner		= THIS_MODULE,
	.read           = xxxx_read,
	.write           = xxxx_write,
};

void xxxxdebug_proc_init(void)
{
	struct proc_dir_entry *xxxxdebug_dir;

	xxxxdebug_dir = proc_mkdir("xxxxdebug", NULL);

	proc_create("regrw", 00644, xxxxdebug_dir, &xxxx_fops);
}

2. 文件的删除
remove_proc_entry("xxxxdebug/regrw", NULL);
remove_proc_entry("xxxxdebug", NULL);

二、sys下的文件创建
