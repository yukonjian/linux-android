1. map
void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
int munmap(void* start,size_t length);

mmap()必须以PAGE_SIZE为单位进行映射，而内存也只能以页为单位进行映射，若要映射非
PAGE_SIZE整数倍的地址范围，要先进行内存对齐，强行以PAGE_SIZE的倍数大小进行映射。
start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
length:
port可以通过or运算合理地组合在一起
length：映射区的长度。//长度单位是 以字节为单位，不足一内存页按一内存页处理
prot：(protect)期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理
地组合在一起
PROT_EXEC //页内容可以被执行
PROT_READ //页内容可以被读取
PROT_WRITE //页可以被写入
PROT_NONE //页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。
MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。
off_t offset：被映射对象内容的起点。offset参数一般设为0，表示从文件头开始映射。

不成功返回MAP_FAILED ((void*)-1)

example : mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);

2. open
int open(const char *pathname, int oflag, ... );
oflag:
O_RDONLY　　只读模式
O_WRONLY　　只写模式
O_RDWR　　读写模式

3. read
ssize_t read(int filedes, void *buf, size_t nbytes);
返回：若成功则返回读到的字节数，若已到文件末尾则返回0，若出错则返回-1
filedes：文件描述符
buf:读取数据缓存区
nbytes:要读取的字节数

4. write
ssize_t write(int filedes, void *buf, size_t nbytes);
返回：若成功则返回写入的字节数，若出错则返回-1
filedes：文件描述符
buf:待写入数据缓存区
nbytes:要写入的字节数

5. ioctl
int ioctl( int fd, int cmd, int arg );
返回：若成功则返回0，若出错则返回-1
fd：文件描述符
cmd:ioctl命令
arg:带入的参数

2. fcntl
fcntl是计算机中的一种函数，通过fcntl可以改变已打开的文件性质。fcntl针对描述符提供控制。
参数fd是被参数cmd操作的描述符。针对cmd的值，fcntl能够接受第三个参数int arg。
int fcntl(int fd, int cmd, long arg);
