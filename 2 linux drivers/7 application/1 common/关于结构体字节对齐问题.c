该问题是由于读取bmp图片的头部而引发的。
将读取到的bmp数据直接转换为struct bmp_header的指针后获取的数据不正确，
是由于struct bmp_header结构体中的数据安装4字节对齐而造成的。

1. 修改编译的对齐方式
添加-fpack-struct[=n]选项
$(CC) $(CFLAGS) $(LDFLAGS) -fpack-struct=2  -L. -I. -o $@ $(OBJS)
2. 在程序中指定结构体的对齐方式
添加 #pragma pack(n)
#pragma pack (1) /*指定按1字节对齐*/
#pragma pack () /*取消指定对齐，恢复缺省对齐*/
