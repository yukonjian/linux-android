1. 文件的打开
FILE * fopen(const char * path, const char * mode);
1) mode
rb : 以只读方式打开一个二进制文件
2. 读取文件
size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
size ： 要读的每个数据项的字节数，单位是字节
count ：要读count个数据项，每个数据项size个字节
stream ： 输入流
return ： 返回真实读取的项数（小于或等于count）
