/********************************************************************************/
/* rk3308录音接口添加 */
struct proc_dir_entry *sounddbg_dir = NULL;
extern int rk3308_sound_capture_status;

ssize_t capture_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	printk("Usage: echo 0/1(start capture/stop capture) > /proc/sounddbg/capture \n");
	printk("value: %d;\n", rk3308_sound_capture_status);
	return 0;
}

ssize_t capture_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	unsigned int value;
	sscanf(buf, "%d ", &value);

	if(value == 0)
	{
		rk3308_sound_capture_status = value;
		printk("rk3308 stop sound capture;\n");
	}
	else if(value == 1)
	{
		rk3308_sound_capture_status = value;
		printk("rk3308 stop sound capture;\n");
	}
	else
		return -1;

	return count;
}

static struct file_operations capture_fops = {
	.owner		= THIS_MODULE,
	.read           = capture_read,
	.write           = capture_write,
};

int rk3308_sound_debug_init(void)
{
	sounddbg_dir = proc_mkdir("sounddbg", NULL);

	proc_create("capture", 00644, sounddbg_dir, &capture_fops);

	return 0;
}

int rk3308_sound_debug_exit(void)
{
	if(sounddbg_dir == NULL)
		return -1;

	remove_proc_entry("capture", sounddbg_dir);
	remove_proc_entry("sounddbg", NULL);

	return 0;
}

/*******************************************************************************/
/* 内核中文件的操作 */
static int snd_pcm_play_store_data(char *buffer, int size)
{

	mm_segment_t fs;

	if(0 == get_pcm_data_status) {
		if (NULL != fp_paly) {
			filp_close(fp_paly, NULL);
			fp_paly = NULL;
		}
		return 0;
	}


	if (fp_paly == NULL) {
		fp_paly = filp_open("/tmp/capture_play.pcm", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (IS_ERR(fp_paly)) {
			printk("create file error\n");
			return -1;
		}
	}

	fs = get_fs();		/* 获取当前线程的thread_info->addr_limit */
	set_fs(KERNEL_DS);

//	printk(KERN_ERR"........................,!!!!The play pos is %lld;\n", fp_paly->f_pos);
	vfs_write(fp_paly, buffer, size, &fp_paly->f_pos);

	set_fs(fs);		/* 将thread_info->addr_limit切换回原来值 */

	return 0;
}
