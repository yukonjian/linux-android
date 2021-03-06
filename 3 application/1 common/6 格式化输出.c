1. printf()的输出格式
format : %[标志][宽度][.精度][长度]类型

2. 类型
d或i	带符号十进制整形
u	无符号十进制整形
o	无符号八进制数
x	无符号十六进制整形 /* 当有符号数使用无符号输出时，会用符号位补全输出的长度，%x默认为sizeof(int)字节输出 */
X	无符号十六进制整形（大写）
f	十进制浮点数，小写
c	字符
s	字符串
p	指针地址
%	%% 输出%号

4. 宽度
(数字)	要打印的最小字符数。如果要打印的值长度小于此数字，结果将填充空格；若值长度大于此数字，该值也不会被截断。

3. 标志
0 在填充时，用零（0）替代空格（见宽度子说明符）。
# 与o，x或X说明符一起使用，会加上0，0x或0X的前缀；
-	在给定字段宽度内左对齐，右侧填入空格（注：不能再使用0标志，让右侧填入0）; 右对齐是默认的（见宽度子说明符）。

5. 长度
hh	signed char	unsigned char
h	short int	unsigned short int
l	long int	unsigned long int
ll	long long int	unsigned long long int
