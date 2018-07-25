#include <string.h>
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
