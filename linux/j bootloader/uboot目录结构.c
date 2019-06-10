1. 目录结构
https://blog.csdn.net/itxiebo/article/details/50935248
uboot/include/config.mk     //自动生成的ARCH灯信息
uboot/include/config.h      //自动生成的配置信息，在makefile中可以添加
uboot/include/configs/firetux.h //相应的开发版的配置头文件，大部分配置均在这里

uboot/arch/arm/lib/board.c //第二阶段运行的程序
uboot/arch/arm/cpu/arm926ejs/start.S //第一阶段运行的程序

uboot/board/dspg/firetux/config.mk //记录了程序运行地址TEXT_BASE = 0x20780000
uboot/board/dspg/firetux/u-boot.lds    //链接文件

1.1 架构相关
uboot/arch/arm/
1.2 CPU相关
uboot/arch/arm/cpu/arm926ejs/
1.3 板子相关
uboot/board/dspg/


2. uboot对于jffs2的支持
#define CONFIG_CMD_JFFS2
#define CONFIG_JFFS2_CMDLINE
3. uboot下的命令
3.1 帮助信息
?       - alias for 'help' ，显示所有的帮助信息
help xxx  //显示xxx命令的帮助信息
3.2 显示分区信息
mtdparts - define flash/nand partitions
3.3 改变当前分区
chpart  - change active partition
3.4 只有支持文件系统才有的功能
3.4.1 ls  - list files in a directory (default /)
3.4.2 从jffs2文件系统中加载文件
fsload  - load binary file from a filesystem image
3.5 md - memory display; b=1byte; w=2byte; l=4byte;
md[.b, .w, .l] address [of objects(读取的个数,不填会连续读取16次)]
3.6 mw - write memory
mw[.b, .w, .l] address value [count]
3.7 fsload - load binary file from a filesystem image
fsload addr(内存地址) 文件路径
fsload 0x20280000 /Uboot/ubootmap.bin
3.8 sf read - 从spi flash总读取数据
sf read addr(内存地址) offset(在flash中的地址) len(读取的字节长度)

一、uboot指令

1、printenv（pri） - 打印环境变量
2、setenv - 设置环境变量，和saveenv 配合使用
3、saveenv - 保存环境变量
4、run - 执行设置好的脚本，比如将uboot的指令A和指令B集合成指令C，则执行C需要在前面加上run；
5、boot - 从uboot进入内核执行；boot命令默认执行的命令式bootcmd；
6、bootm - 只能用来引导经过mkimage构建了镜像头的内核镜像文件以及根文件镜像；
7、fsload 可以将内核和文件系统从flash、读出来，放到内存中，使用的是jffs2文件系统；
8、tftp 下载镜像文件到内存中；tftp {addr} {uimage_name}； tftp 将某个文件下载到内存中，然后可以通过bootm引导；


二、环境变量

1、bootcmd  - 倒计时结束后，默认执行得指令；
2、bootargs - 传递给kernel启动执行的参数，比如选择使用jffs2文件系统还是NFS文件系统，例如：
bootargs=root=/dev/mtdblock6 rw rootfstype=jffs2  //使用nand flash上的jffs2文件系统，mtdblock6 表示第flash的6块分区（nor：0 1 2 3，nand：4 5 6）；
bootargs=root=/dev/nfs rw nfsroot=${serverip}:${nfsdir} //使用NFS文件系统；
3、ethact - 设置默认网卡  /* setenv ethact gemac1 设置网卡1为默认网卡，执行ping命令数据将从网卡1发出 */
