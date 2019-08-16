1. uboot的基本操作
1.1 uboot的编译
  make xxx_config
  make
1.2 bootloader打补丁
  cd uboot目录
  patch -p1 < xxx_patch   /* p1忽略掉一级目录 */
2. uboot的配置
bootloader配置会在include目录下生成config.h和config.mk文件
config.h头文件中主要包含实际用到的config文件（#include <config/100ask24x0.h>）及以下CONFIG_XXX配置
config.mk文件主要包含ARCH,CPU，BOARD,SOC的宏定义
ARCH    = arm
CPU     = arm920t
BOARD   = 100ask24x0
SOC     = s3c24x0
3. uboot源码分析
2.1 第一阶段的启动
arck/arm/cpu/arm920t/start.S   /* 硬件相关初始化，拷贝uboot到sdram中，并调用start_armboot */
2.2 第二阶段的启动
board/arm/lib/board.c
start_armboot();
  /* 一些初始化 */
  main_loop();
    /* 启动内核阶段 */
    s = getenv("bootcmd");
    run_command(s);
    /* uboot界面阶段 */
    readline()  /* 读入串口的数据 */
    run_command();
注：uboot的核心是命令，一个一个的命令
2.3 uboot的命令实现
只需要使用U_BOOT_CMD宏定义一个结构体即可
2.4 uboot启动内核
2.4.1 uImage
内核uImage = 64字节的头部 + 正真的内核
头部包括：ih_load(加载地址)和ih_ep(入口地址)
加载地址:正真的内核存放的地址，并不包括头部；
入口地址:直接跳转运行内核的地址；
2.3.2 启动内核
bootm
do_bootm_linux:
设置启动参数（告诉内核一些参数）
在某个地址：bd->bi_boot_params
按照某种格式：TAG
保存数据
跳到入口地址：
theKernel = (void (*)(int, int, uint))ntohl(hdr->ih_ep);
theKernel(0, bd->bi_arch_number, bd->bi_boot_params)
bd->bi_arch_number = MACH_TYPE_S2c2440; (机器ID)
在内核中会进行匹配，看是否支持该SOC;
