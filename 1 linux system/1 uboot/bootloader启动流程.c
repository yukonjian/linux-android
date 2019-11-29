https://blog.csdn.net/eZiMu/article/details/54809184
uboot2017.09
1. Makefile从宏 LDSCRIPT 获取启动脚本(u-boot.lds)路径
1. 从链接脚本（u-boot.lds 位于根目录下）中得知，
第一个入口函数为: ENTRY(_start);位于arch/arm/lib/vectors.S
2. 第一个启动函数 _start
 _start位于arch/arm/cpu/arm920t/start.S
 注：可以在顶层目录/system.map找到函数的地址
2. 进入第一个C函数:board_init_f() 一般是在board.c的文件中
