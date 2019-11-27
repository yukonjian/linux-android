#include <stdio.h>
1. 文件的打开
FILE * fopen(const char * path, const char * mode);
1) mode
文件mode使用方式由r,w,a,t,b，+六个字符拼成，各字符的含义是：
r(read): 只读
w(write): 只写
a(append): 追加
t(text): 文本文件，可省略不写
b(binary): 二进制文件
+: 读和写
凡用“r”打开一个文件时，该文件必须已经存在，且只能从该文件读出。
用“w”打开的文件只能向该文件写入。若打开的文件不存在，则以指定的文件名建立该文件，若打开的文件已经存在，则将该文件删去，重建一个新文件。
若要向一个已存在的文件追加新的信息，用“a”方式打开文件。如果指定文件不存在则尝试创建该文件

r = rt : 打开一个文本文件，文件必须存在，只允许读
r+ = rt+ : 打开一个文本文件，文件必须存在，允许读写
rb : 打开一个二进制文件，文件必须存在，只允许读
rb+ : 打开一个二进制文件，文件必须存在，允许读写
w = wt : 新建一个文本文件，已存在的文件将内容清空，只允许写
w+ = wt+ : 新建一个文本文件，已存在的文件将内容清空，允许读写
wb : 新建一个二进制文件，已存在的文件将内容清空，只允许写
wb+ : 新建一个二进制文件，已存在的文件将内容清空，允许读写
a = at : 打开或新建一个文本文件，只允许在文件末尾追写
a+ = at+ : 打开或新建一个文本文件，可以读，但只允许在文件末尾追写
ab : 打开或新建一个二进制文件，只允许在文件末尾追写
ab+ : 打开或新建一个二进制文件，可以读，但只允许在文件末尾追写

return: 在打开一个文件时，如果出错，fopen将返回一个空指针值NULL。
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
