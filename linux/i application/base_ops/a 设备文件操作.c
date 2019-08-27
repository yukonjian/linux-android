#include <unistd.h>
1. open
int open(const char *pathname, int oflag, ... );
oflag:
O_RDONLY　　只读模式
O_WRONLY　　只写模式
O_RDWR　　读写模式

2. read
ssize_t read(int filedes, void *buf, size_t nbytes);
返回：若成功则返回读到的字节数，若已到文件末尾则返回0，若出错则返回-1
filedes：文件描述符
buf:读取数据缓存区
nbytes:要读取的字节数

3. write
ssize_t write(int filedes, void *buf, size_t nbytes);
返回：若成功则返回写入的字节数，若出错则返回-1
filedes：文件描述符
buf:待写入数据缓存区
nbytes:要写入的字节数

4. ioctl
int ioctl( int fd, int cmd, int arg );
返回：若成功则返回0，若出错则返回-1
fd：文件描述符
cmd:ioctl命令
arg:带入的参数

5. fcntl
fcntl是计算机中的一种函数，通过fcntl可以改变已打开的文件性质。fcntl针对描述符提供控制。
参数fd是被参数cmd操作的描述符。针对cmd的值，fcntl能够接受第三个参数int arg。
int fcntl(int fd, int cmd, long arg);

6. lseek
off_t lseek(int fildes,off_t offset ,int whence);
返回：距离文件开头多少个字节。若有错误则返回-1
fildes: 为已打开的文件描述词，
offset: 为根据参数whence来移动读写位置的位移数。
whence: 为下列其中一种:（SEEK_SET,SEEK_CUR和SEEK_END和依次为0，1和2）
SEEK_SET 将读写位置指向文件头后再增加offset个位移量。
SEEK_CUR 以目前的读写位置往后增加offset个位移量。
SEEK_END 将读写位置指向文件尾后再增加offset个位移量。


3. linux c下执行shell命令
system 相当简单：
int system(const char *command);
sample:
system("ps -aux");
