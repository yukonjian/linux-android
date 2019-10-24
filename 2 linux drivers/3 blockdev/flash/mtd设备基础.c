产考文档：
Linux MTD系统剖析
https://blog.csdn.net/chungle2011/article/details/80585542
mtd子系统----设备层
https://www.cnblogs.com/ken-song2016/articles/5627505.html

一、 MTD总体介绍

1. MTD设备通常可分为四层，从上到下依次是：设备节点、MTD设备层、MTD原始设备层、硬件驱动层。
1.1 设备节点：
通过mknod在/dev子目录下建立MTD块设备节点（主设备号为31）和MTD字符设备节点（主设备号为90）。
通过访问此设备节点即可访问MTD字符设备和块设备
1.2 MTD设备层：
基于MTD原始设备，linux系统可以定义出MTD的块设备（主设备号31）和字符设备（设备号90）。
其中mtdchar.c :  MTD字符设备接口相关实现，mtdblock.c : MTD块设备接口相关实现。
1.3 MTD原始设备层：
用于描述MTD原始设备的数据结构是mtd_info，它定义了大量的关于MTD的数据和操作函数。
其中mtdcore.c:  MTD原始设备接口相关实现，mtdpart.c :  MTD分区接口相关实现。
1.4 Flash硬件驱动层：
Flash硬件驱动层负责对Flash硬件的读、写和擦除操作。MTD设备的Nand Flash芯片的驱动则
drivers/mtd/nand/子目录下,Nor Flash芯片驱动位于drivers/mtd/chips/子目录下。

二、MTD设备层：
设备层是实现了文件系统与Flash之间的桥梁，其基于MTD原始层提供了两种上层访问Flash的方式：
MTD的字符设备和块设备，字符设备通过向内核注册字符设备的file_operations结构实现了对MTD设备
的读写和控制，提供了对闪存的原始字符访问，关联的设备是/dev/mtd*；
而MTD块设备则是定义了一个描述MTD块设备mtdblock_tr的结构，关联的设备是/dev/mtdblock*。

三、mtd设备的内核配置
1. 选择mtd设备
2. 选择mtd设备下的MTD_BLOCK和MTD_BLKDEVS
