1.
void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
int munmap(void* start,size_t length);

mmap()必须以PAGE_SIZE为单位进行映射，而内存也只能以页为单位进行映射，若要映射非
PAGE_SIZE整数倍的地址范围，要先进行内存对齐，强行以PAGE_SIZE的倍数大小进行映射。

start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
length:
port可以通过or运算合理地组合在一起
PROT_EXEC //页内容可以被执行
PROT_READ //页内容可以被读取
PROT_WRITE //页可以被写入
PROT_NONE //页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。
MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。
off_t offset：被映射对象内容的起点。offset参数一般设为0，表示从文件头开始映射。

不成功返回MAP_FAILED ((void*)-1)

example : mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
