typedef struct
{
	struct device           *dev;
	uintptr_t               reg_base[DISP_MOD_NUM];  //从设备树中获取各寄存器的基地址
	u32                     irq_no[DISP_MOD_NUM];  //从设备树中获取中断号
	struct clk              *mclk[DISP_MOD_NUM]; //从设备树中获取时钟

	disp_init_para          disp_init;
	struct disp_manager     *mgr[DISP_SCREEN_NUM]; //指向显示管理的指针
	struct disp_eink_manager *eink_manager[1];
	struct proc_list        sync_proc_list;
	struct proc_list        sync_finish_proc_list;
	struct ioctl_list       ioctl_extend_list;
	struct ioctl_list       compat_ioctl_extend_list;
	struct standby_cb_list  stb_cb_list;
	struct mutex            mlock;
	struct work_struct      resume_work[DISP_SCREEN_NUM];
	struct work_struct      start_work;

	u32    		              exit_mode;//0:clean all  1:disable interrupt
	bool			              b_lcd_enabled[DISP_SCREEN_NUM];
	bool                    inited;//indicate driver if init
	disp_bsp_init_para      para;
#if defined(CONFIG_ION_SUNXI)
	struct ion_client *client;
	struct ion_handle *handle;
#endif
}disp_drv_info;
disp_drv_info g_disp_drv;
