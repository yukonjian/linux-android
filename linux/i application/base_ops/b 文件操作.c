#include <stdio.h>
1. 文件的打开
FILE * fopen(const char * path, const char * mode);
1) mode
rb : 以只读方式打开一个二进制文件
wb : 以只写方式打开或新建一个二进制文件，只允许写数据
wb+ : 以读/写方式打开或建立一个二进制文件，允许读和写。
w  : 打开只写文件，若文件存在则长度清为 0，即该文件内容消失，若不存在则创建该文件。
2) 二进制和文本模式的区别
  a) 在Windows系统中，文本模式下，文件以"\r\n"代表换行。若以文本模式打开文件，并用 fputs 等函数写入换行符"\n"时，函数会自动在"\n"前面加上"\r"。即实际写入文件的是"\r\n"。
  b) 在类 Unix/Linux 系统中文本模式下，文件以"\n"代表换行。所以 Linux 系统中在文本模式和二进制模式下并无区别。
2. 读取文件
size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
size ： 要读的每个数据项的字节数，单位是字节
count ：要读count个数据项，每个数据项size个字节
stream ： 输入流
return ： 返回真实读取的项数（小于或等于count）
3. 写文件
size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
返回值：返回实际写入的数据块数目
4. 设置文件指针stream的位置
int fseek(FILE *stream, long offset, int fromwhere);
成功:返回0; stream将指向以fromwhere（偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）
为基准，偏移offset（指针偏移量）个字节的位置。
失败:返回非0值; (比如offset超过文件自身大小)，则不改变stream指向的位置。
