通过/dev/fb，应用程序的操作主要有这几种：
1．读/写（read/write）/dev/fb：相当于读/写屏幕缓冲区。例如用 cp /dev/fb0 tmp 命令可
将当前屏幕的内容拷贝到一个文件中，而命令 cp tmp > /dev/fb0 则将图形文件tmp显示在屏幕上。
2．映射（map）操作：由于 Linux工作在保护模式，每个应用程序都有自己的虚拟地址空间，在应用
程序中是不能直接访问物理缓冲区地址的。为此，Linux 在文件操作file_operations 结构中提供了
mmap函数，可将文件的内容映射到用户空间。对于帧缓冲设备，则可通过映射操作，可将屏幕缓冲区的
物理地址映射到用户空间的一段虚拟地址中，之后用户就可以通过读写这段虚拟地址访问屏幕缓冲区，在屏幕上绘图了。
3．I/O控制：对于帧缓冲设备，对设备文件的 ioctl操作可读取/设置显示设备及屏幕的参数，如分辨率，
显示颜色数，屏幕大小等等。ioctl 的操作是由底层的驱动程序来完成的。


显示模式是1280*720-8位色
4.执行dd if=/dev/zero of=/dev/graphics/fb0 bs=1280 count=720* 实现清屏



文件：tft600_1024.c
struct disp_panel_para；

文件：disp_display.c
s32 bsp_disp_get_panel_info(u32 disp, disp_panel_para *info)
struct disp_device｛
  int (*get_panel_info)(struct disp_device* dispdev, disp_panel_para *info);
｝；

文件：lcd_source.c
s32 sunxi_lcd_dsi_clk_enable(u32 screen_id) -> sunxi_disp_source_ops


Gralloc模块头文件  androidm\hardware\libhardware\include\hardware\gralloc.h

disp_init
------bsp_disp_init(para);
      ------disp_init_al
      ------disp_init_lcd struct disp_device *lcd;
------lcd_init(); struct sunxi_disp_source_ops *src_ops
------bsp_disp_open();  return DIS_SUCCESS;
------fb_init(pdev); fb0,fb1



struct disp_device {
	struct list_head list;
	/* data fields */
	char name[32];
	u32 disp;
	u32 hwdev_index;//indicate the index of hw device(timing controller)
	u32 fix_timing;
	enum disp_output_type type;
	struct disp_manager *manager;
	struct disp_video_timings timings;
	struct work_struct close_eink_panel_work;
	void* priv_data;

	/* function fileds  */
	/* init: script init && clock init && pwm init && register irq
	 * exit: clock exit && unregister irq
	 */
	s32 (*init)(struct disp_device *dispdev);
	s32 (*exit)(struct disp_device *dispdev);

	s32 (*set_manager)(struct disp_device *dispdev, struct disp_manager *mgr);
	s32 (*unset_manager)(struct disp_device *dispdev);

	s32 (*enable)(struct disp_device *dispdev);
	s32 (*fake_enable)(struct disp_device *dispdev);
	s32 (*sw_enable)(struct disp_device *dispdev);
	s32 (*disable)(struct disp_device *dispdev);
	s32 (*is_enabled)(struct disp_device *dispdev);
	s32 (*is_used)(struct disp_device *dispdev);
	s32 (*get_resolution)(struct disp_device *dispdev, u32 *xres, u32 *yres);
	s32 (*get_dimensions)(struct disp_device *dispdev, u32 *width, u32 *height);
	s32 (*set_timings)(struct disp_device *dispdev, struct disp_video_timings *timings);
	s32 (*get_timings)(struct disp_device *dispdev, struct disp_video_timings *timings);
	s32 (*check_timings)(struct disp_device *dispdev, struct disp_video_timings *timings);
	s32 (*detect)(struct disp_device *dispdev);
	s32 (*set_detect)(struct disp_device *dispdev, bool hpd);
	s32 (*get_status)(struct disp_device *dispdev);
	s32 (*get_fps)(struct disp_device *dispdev);

	s32 (*get_input_csc)(struct disp_device *dispdev);
	s32 (*get_input_color_range)(struct disp_device *dispdev);
	s32 (*is_interlace)(struct disp_device *dispdev);

	/* power manager */
	s32 (*early_suspend)(struct disp_device *dispdev);
	s32 (*late_resume)(struct disp_device *dispdev);
	s32 (*suspend)(struct disp_device *dispdev);
	s32 (*resume)(struct disp_device *dispdev);

	s32 (*dump)(struct disp_device *dispdev, char *buf);

	/* HDMI /TV */
	s32 (*set_mode)(struct disp_device *dispdev, u32 mode);
	s32 (*get_mode)(struct disp_device *dispdev);
	s32 (*check_support_mode)(struct disp_device* dispdev, u32 mode);
	s32 (*set_func)(struct disp_device*  dispdev, struct disp_device_func * func);
	s32 (*set_tv_func)(struct disp_device*  dispdev, struct disp_tv_func * func);
	s32 (*set_enhance_mode)(struct disp_device *dispdev, u32 mode);

	/* LCD */
	s32 (*set_bright)(struct disp_device *dispdev, u32 bright);
	s32 (*get_bright)(struct disp_device *dispdev);
	s32 (*backlight_enable)(struct disp_device *dispdev);
	s32 (*backlight_disable)(struct disp_device *dispdev);
	s32 (*pwm_enable)(struct disp_device *dispdev);
	s32 (*pwm_disable)(struct disp_device *dispdev);
	s32 (*power_enable)(struct disp_device *dispdev, u32 power_id);
	s32 (*power_disable)(struct disp_device *dispdev, u32 power_id);
	s32 (*tcon_enable)(struct disp_device *dispdev);
	s32 (*tcon_disable)(struct disp_device *dispdev);
	s32 (*set_bright_dimming)(struct disp_device *dispdev, u32 dimming);
	disp_lcd_flow *(*get_open_flow)(struct disp_device *dispdev);
	disp_lcd_flow *(*get_close_flow)(struct disp_device *dispdev);
	s32 (*pin_cfg)(struct disp_device *dispdev, u32 bon);
	s32 (*set_gamma_tbl)(struct disp_device* dispdev, u32 *tbl, u32 size);
	s32 (*enable_gamma)(struct disp_device* dispdev);
	s32 (*disable_gamma)(struct disp_device* dispdev);
	s32 (*set_panel_func)(struct disp_device *lcd, char *name, disp_lcd_panel_fun * lcd_cfg);
	s32 (*set_open_func)(struct disp_device* lcd, LCD_FUNC func, u32 delay);
	s32 (*set_close_func)(struct disp_device* lcd, LCD_FUNC func, u32 delay);
	int (*gpio_set_value)(struct disp_device* dispdev, unsigned int io_index, u32 value);
	int (*gpio_set_direction)(struct disp_device* dispdev, unsigned int io_index, u32 direction);
	int (*get_panel_info)(struct disp_device* dispdev, disp_panel_para *info);
};



s32 bsp_disp_lcd_set_panel_funs(char *name, disp_lcd_panel_fun * lcd_cfg)
{
	struct disp_device* lcd;
	u32 num_screens;
	u32 screen_id;
	u32 registered_cnt = 0;

	num_screens = bsp_disp_feat_get_num_screens();
	for (screen_id=0; screen_id<num_screens; screen_id++) {
		lcd = disp_get_lcd(screen_id);
		if (lcd && (lcd->set_panel_func)) {
			if (!lcd->set_panel_func(lcd, name, lcd_cfg)) {
				gdisp.lcd_registered[screen_id] = 1;
				registered_cnt ++;
				DE_INF("panel driver %s register\n", name);
			}
		}
	}

	return 0;
}

lcdp->lcd_panel_fun.cfg_open_flow = lcd_cfg->cfg_open_flow;

disp_lcd_enable
disp_lcd_fake_enable

work
bsp_disp_device_switch
disp_device_attached_and_enable
mgr->device->disable(mgr->device);
