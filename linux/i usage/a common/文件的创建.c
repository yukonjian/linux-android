一. proc下的文件的创建
1. 文件的创建
static ssize_t reg_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	return 0;
}

static ssize_t reg_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	unsigned int lednum,addr,value;
	unsigned int virt_addr;
	sscanf(buf, "%d 0x%x", &lednum, &value);
	printk("cmd:%d;value:0x%x;\n", lednum, value);
  return count;
｝

static struct file_operations reg_fops = {
	.owner		= THIS_MODULE,
	.read           = reg_read,
	.write           = reg_write,
};

void leddebug_proc_init(void)
{
	struct proc_dir_entry *leddebug_dir;

	leddebug_dir = proc_mkdir("leddebug", NULL);

	proc_create("regrw", 00644, leddebug_dir, &reg_fops);
}

2. 文件的删除
remove_proc_entry("leddebug/regrw", NULL);
remove_proc_entry("leddebug", NULL);

二、sys下的文件创建
