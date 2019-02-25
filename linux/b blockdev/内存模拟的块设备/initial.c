1. 块设备书写步骤
1.1在入口函数中:

1)使用register_blkdev()创建一个块设备
2) blk_init_queue()使用分配一个申请队列,并赋申请队列处理函数
3)使用alloc_disk()分配一个gendisk结构体
4)设置gendisk结构体的成员
  ->4.1)设置成员参数(major、first_minor、disk_name、fops)
  ->4.2)设置queue成员,等于之前分配的申请队列
  ->4.3)通过set_capacity()设置capacity成员,等于扇区数
5)使用kzalloc()来获取缓存地址,用做扇区
6)使用add_disk()注册gendisk结构体
1.2在申请队列的处理函数中

1) while循环使用elv_next_request()获取申请队列中每个未处理的申请
2)使用rq_data_dir()来获取每个申请的读写命令标志,为 0(READ)表示读, 为1(WRITE)表示写
3)使用memcp()来读或者写扇区(缓存)
4)使用end_request()来结束获取的每个申请
1.3在出口函数中

1)使用put_disk()和del_gendisk()来注销,释放gendisk结构体
2)使用kfree()释放磁盘扇区缓存
3)使用blk_cleanup_queue()清除内存中的申请队列
4)使用unregister_blkdev()卸载块设备

//详细请参考以下链接
http://www.cnblogs.com/lifexy/p/7661454.html

2. flash设备的书写步骤
2.1 在init入口函数中

1)通过kzalloc()来分配结构体: mtd_info和nand_chip
2)通过ioremap()来分配获取nand flash 寄存器虚拟地址
3)设置mtd_info结构体成员
4)设置nand_chip结构体成员
5)设置硬件相关
     ->5.1) 通过clk_get()和clk_enable()来使能nand flash 时钟
     ->5.2)设置时序
     ->5.3)关闭片选,并开启nand flash 控制器
6)通过nand_scan()来扫描nandflash
7)通过add_mtd_partitions()来添加分区,创建MTD字符/块设备
2.2 在exit入口函数中

1)卸载分区,卸载字符/块设备
2)释放mtd
3)释放nand flash寄存器
4)释放nand_chip
