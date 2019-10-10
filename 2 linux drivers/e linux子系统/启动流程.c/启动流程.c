内核传参解析
https://blog.csdn.net/funkunho/article/details/51967137

rootfs的挂载流程
https://www.cnblogs.com/bhlsheji/p/4204586.html

bootargs解析
https://blog.csdn.net/zhangjikuan/article/details/22091335

uboot移植之tag传参
https://blog.51cto.com/11674570/1925587
bootcmd1=run chk_mtdparts && setenv bootargs ${bootargs} ${mtdparts} && ${readcmd} 0x20200000 ${bootpart} && run chk_bootaddr && bootm ${bootaddr}

uboot启动内核
https://www.cnblogs.com/lifexy/p/7310279.html

uboot环境变量保存位置
sample:
include/configs/mini2440.h头文件
#define CONFIG_ENV_OFFSET 0X40000

内核中保留内存的方式
https://blog.csdn.net/weixin_33881041/article/details/89830388

根文件系统启动
https://blog.csdn.net/qq_33160790/article/details/79244480

uboot CMD命令的使用
U_BOOT_CMD(name,maxargs,repeatable,command,"usage","help")
name：命令名，非字符串，但在U_BOOT_CMD中用“#”符号转化为字符串
maxargs：命令的最大参数个数
repeatable：是否自动重复（按Enter键是否会重复执行，1表示会重复执行）
command：该命令对应的响应函数指针
usage：简短的使用说明（字符串）
help：较详细的使用说明（字符串）
#define U_BOOT_CMD(name,maxargs,rep,cmd,usage,help) \
　　　　cmd_tbl_t __u_boot_cmd_##name Struct_Section = {#name, maxargs, rep, cmd, usage, help}




bootargs=console=ttyS1,115200n8 root=/dev/mtdblock3 rootfstype=squashfs noalign

mtdparts=mtdparts=spi_flash:196608(u-boot),65536(u-bootenv),1441792(kernel),1572864(rootfs),393216(config),131072(basic),-(app)

sf read 0x20200000  kernel


izkare # mtdparts
device nor0 <spi_flash>, # parts = 7
 #: name                size            offset          mask_flags
 0: u-boot              0x00030000      0x00000000      0
 1: u-bootenv           0x00010000      0x00030000      0
 2: kernel              0x00160000      0x00040000      0
 3: rootfs              0x00180000      0x001a0000      0
 4: config              0x00060000      0x00320000      0
 5: basic               0x00020000      0x00380000      0
 6: app                 0x00460000      0x003a0000      0

active partition: nor0,0 - (u-boot) 0x00030000 @ 0x00000000

defaults:
mtdids  : nor0=spi_flash
mtdparts: mtdparts=spi_flash:196608(u-boot),65536(u-bootenv),1441792(kernel),1572864(rootfs),393216(config),131072(basic),-(app)
