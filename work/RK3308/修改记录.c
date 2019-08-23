1. bootloader 修改
common/android_bootloader.c

	/* 强制指定boot的启动模式为normal */
	mode = ANDROID_BOOT_MODE_NORMAL;
	printf("ANDROID: reboot reason: \"%s\"\n", android_boot_mode_str(mode));

2. 网路驱动
./drivers/net/ethernet/stmicro/stmmac/dwmac-rk.c

3. 编译的板子配置
/home/project/device/rockchip/.BoardConfig.mk

4. mtd分区修改位置
 kernel/drivers/rkflash/sfc_nor_mtd.c
