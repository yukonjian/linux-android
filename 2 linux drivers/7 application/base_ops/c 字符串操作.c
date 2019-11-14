/* linux c 中的头文件 */
#include <string.h>
/* linux 驱动中的头文件 */
#include <linux/string.h>
1. snprintf sscanf
1.1. snprintf(char *str, size_t size, const char *format, ...)
(1) 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')；
(2) 如果格式化后的字符串长度 >= size，则只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。
1.2 int sscanf(const char *buffer, const char *format, [ argument ] ... )
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
5. char *strcat(char *dest, const char *src)；
dest -- 指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串。
src -- 指向要追加的字符串，该字符串不会覆盖目标字符串。
该函数返回一个指向最终的目标字符串 dest 的指针。

三、字符串和数据的转换
1. int atoi(const char *nptr);
atoi (表示 ascii to integer), 把字符串转换成整型数的一个函数
如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0
