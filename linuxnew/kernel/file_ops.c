1. struct file *filp_open(const char *, int, umode_t);
2. ssize_t vfs_read(struct file *, char __user *, size_t, loff_t *);
3. ssize_t vfs_write(struct file *, const char __user *, size_t, loff_t *);
4. int filp_close(struct file *, fl_owner_t id);
5.  set_fs和get_fs
KERNEL_DS范围很大，到0xffffffffffffffff。
而USER_DS范围较小，到0x7ffffffff000。
由Linux内存分布图可知，KERNEL_DS意味着可以访问整个内存所有空间，USER_DS只能访问用户空间内存。
通过set_fs可以改变thread_info->addr_limit的大小。
内核使用系统调用参数肯定是内核空间，为了不让这些系统调用检查参数所以必须设置  set_fs(KERNEL_DS)才能使用该系统调用。
vfs_write的流程可调用access_ok，而access_ok会判断访问的buf是否在0~addr_limit之间，如何是就ok；否则-EFAULT，这显然是为用户准备的检查。
addr_limit一般设为USER_DS，在内核空间，buf肯定>USER_DS，必须修改addr_limit，这就是set_fs的由来。


example:
static int snd_pcm_store_data(char *buffer, int size)
{
	struct file *fp =NULL;
	mm_segment_t fs;
	loff_t pos;

	fp = filp_open("/tmp/play.pcm", O_RDWR | O_CREAT, 0644);
	if (IS_ERR(fp)) {
		printk("create file error\n");
		return -1;
	}

	fs = get_fs();		/* 获取当前线程的thread_info->addr_limit */
	set_fs(KERNEL_DS);

	printk(KERN_ERR"...................................,store data;Enter the fun: %s; Line is %d;\n", __FUNCTION__, __LINE__);
	pos = fp->f_pos;
	printk(KERN_ERR"........................,The pos is %d;\n", pos);
	vfs_write(fp, buffer, sizeof(buffer), &pos);
	fp->f_pos = pos;

	set_fs(fs);		/* 将thread_info->addr_limit切换回原来值 */

	filp_close(fp, NULL);

	return 0;
}

代码分析
fp =filp_open("/home/jenkins/lubaoquan/test/kernel_file",O_RDWR | O_CREAT,0644);---------------------创建用户空间文件，获取文件句柄。
if (IS_ERR(fp)){
    printk("create file error\n");
    return -1;
}
fs =get_fs();----------------------------------------------------------------------------------------获取当前线程的thread_info->addr_limit。
set_fs(KERNEL_DS);-----------------------------------------------------------------------------------将能访问的空间thread_info->addr_limit扩大到KERNEL_DS。
pos =0;
vfs_write(fp,buf, sizeof(buf), &pos);----------------------------------------------------------------调用vfs_write写内容
pos =0;
vfs_read(fp,buf1, sizeof(buf), &pos);----------------------------------------------------------------调用vfs_read读取内容
printk("Write contet=%s\n",buf1);
filp_close(fp,NULL);---------------------------------------------------------------------------------关闭文件
set_fs(fs);------------------------------------------------------------------------------------------将thread_info->addr_limit切换回原来值
