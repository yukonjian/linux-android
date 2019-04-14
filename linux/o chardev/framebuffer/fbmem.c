frame_buffer提供给应用程序的接口主要在文件fbmem.c中.
fbmem.c 处于Framebuffer设备驱动技术的中心位置.它为上层应用程序提供系统调用也为下一层的特定硬件驱动提供接口；
那些底层硬件驱动需要用到这儿的接口来向 系统内核注册它们自己.
fbmem.c 为所有支持FrameBuffer的设备驱动提供了通用的接口，避免重复工作.
1. 全局变量
struct fb_info *registered_fb[FB_MAX];
int num_registered_fb;
这两变量记录了所有fb_info 结构的实例，fb_info 结构描述显卡的当前状态，所有设备对应的fb_info结构都保存在这个数组中，
当一个FrameBuffer设备驱动向系统注册自己时，其对应的 fb_info结构就会添加到这个结构中，同时num_registered_fb 为自动加1.
2. 应用程序的接口
static const struct file_operations fb_fops = {
	.owner =	THIS_MODULE,
	.read =		fb_read,
	.write =	fb_write,
	.unlocked_ioctl = fb_ioctl,
	.mmap =		fb_mmap,
	.open =		fb_open,
	.release =	fb_release,
	.llseek =	default_llseek,
};
3. 驱动程序的接口
1) 注册和注销fb
register_framebuffer(struct fb_info *fb_info);
unregister_framebuffer(struct fb_info *fb_info);
这两个是提供给下层FrameBuffer设备驱动的接口，设备驱动通过这两函数向系统注册或注销自己。
几乎底层设备驱动所要做的所有事情就是填充 fb_info结构然后向系统注册或注销它。
