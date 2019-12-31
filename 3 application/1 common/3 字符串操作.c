/* linux c 中的头文件 */
#include <string.h>
/* linux 驱动中的头文件 */
#include <linux/string.h>
一. snprintf sscanf
1 snprintf(char *str, size_t size, const char *format, ...)
	 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')；
	 如果格式化后的字符串长度 >= size，则只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。
2 int sscanf(const char *buffer, const char *format, [ argument ] ... )
https://blog.csdn.net/a_Treasure/article/details/82085937
/* 下面参数可以得到正确的结果 */
	unsigned int a,b,c;
	sscanf(str, "%2x:%2x:%2x",&a,&b,&c);
/* 下面参数不可以得到正确的结果 */
	unsigned char a,b,c;
	sscanf(str, "%2x:%2x:%2x",&a,&b,&c);
使用%x获取数据必须要使用unsigned int定义的变量
注：sscanf会以空格作为断点，加%*d则是忽略读取的数据）
char buf[10];
sscanf("12 aaa", "%*d%s", buf);
2.1 %[^&] ，使用&替代空格作为断点
%[^&]的意思是指输入的数据要遇上&才结束；
比如说在处理字符串中的scanf("%s",a);如果普通的话遇上了空格或者回车就结束了；
但把它改成这个样子scanf("%[^=]",a);就表示在输入数据中是以‘=’为结束标志的。在遇到空格和回车都不结束当前输入。
这句话有意思的地方就在于当使用这种特殊结束标志以后，这个标志不但不会被存储在对应的存储空间里，而且输出的时候按照普通方法即可输出所输入的字符；
2.2 该参数可以是一个或多个 {%[*] [width] [{h | I | I64 | L}]type | ' ' | '\t' | '\n' | 非%符号}
sscanf(buffer, "%4s", des);	//指定长度为4

二、字符串操作
1. strlen( const char string[] );
注意：strlen函数的功能是计算字符串的实际长度，不包括'\0'在内。
另外，strlen函数也可以直接测试字符串常量的长度，如：strlen("Welcome")。
2. void *memset(void *dest, int c, size_t count);
将dest前面count个字符置为字符c.  返回dest的值.
3. int strcmp(const char firststring[], const char secondstring);
比较两个字符串firststring和secondstring
若str1==str2，则返回零；
若str1<str2，则返回负数；
若str1>str2，则返回正数。
4. char *strcpy(char *strDestination, const char *strSource);
复制源串strSource到目标串strDestination所指定的位置, 包含NULL结束符. 不能处理源串与目标串重叠的情况.函数返回strDestination值.
4.1 char *strncpy(char *destinin, char *source, int maxlen);
如果strlen(source) + 1 <= maxlen; 则会将整个source复制到destinin中；
否则只复制maxlen字符到destinin；destinin中并不会有'\0',需要使用'\0',替换最后一个字符。
5. char *strcat(char *dest, const char *src)；
dest -- 指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串。
src -- 指向要追加的字符串，该字符串不会覆盖目标字符串。
该函数返回一个指向最终的目标字符串 dest 的指针。
5.1 char * strncat(char *dest, const char *src, size_t n);
n: 需要追加的最大字符的长度

三、字符串和数据的转换
1. int atoi(const char *nptr);
atoi (表示 ascii to integer), 把字符串转换成整型数的一个函数
如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0

四、gets, puts， fgets, fputs
https://blog.csdn.net/qq_41453285/article/details/88853801
