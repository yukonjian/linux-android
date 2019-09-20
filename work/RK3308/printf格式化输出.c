【C】unsigned char printf 的格式是什么?
2019年03月18日 15:20:57 欧阳小俊 阅读数 1061更多
分类专栏： Qt/C++/C
版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
本文链接：https://blog.csdn.net/m0_37362454/article/details/88639668



今天想打印unsigned char 类型的值，但是不知道该用什么格式输出，所以就上网搜了一下，但是出现了五花八门的答案，比如说%c, %x, %u等等，就是没有看到正确的答案。



正确答案是%hhu。

1

2

3

4

5

6

7

#include <stdio.h>

int main()

{

    unsigned char ch = 23;

    printf("ch = %hhu\n", ch);

    return 0;

}

结果如图：


这个答案是因为我最近刚好在看APUE,然后知道里面有讲到printf的格式问题，所以查看一下就搞定了。虽然这个问题不算什么难的问题，但是查找起答案来，发现满意的答案并不多，所以我选择记下来。并且补上这个printf的格式原型，以及各个可选参数是什么。

%[flags][fldwidth][precision][lenmodifier]convtype

flags的可选参数是：
标志                                          说明
‘                            （撇号）将整数按千位分组字符
–                            在字段内左对齐输出
+                           总是显示带符号转换的正负号
（空格）              如果第一个字符不是正负号，则在其前面加上一个空格
#                           指定另外一种转换形式（例如，对于十六进制格式，加0x前缀）
0                           添加前导0（而非空格）进行填充

fidwidth说明最小字段宽度，转换后参数字符数若小于宽度，则多余字符位置用空格填充。字段宽度是一个非负十进制数，或是一个（*）。
precision说明整型转换后最少输出数字位数、浮点数转换后小数点的最少位数、字符串转换后最大字节数。精度是一个点（.），其后跟随一个可选的非负十进制数或一个星号（*）。

宽度和精度字段两者皆可为*。此时，一个整型参数指定宽度或者精度的值，该整型参数正好位于被转换的参数之前。
觉得有点抽象的话，下面我给出了一个例子供参考。

1

2

3

4

5

6

7

8

9

#include <stdio.h>





int main()

{

    int ch = 22342233;

    printf("ch = %*.*d\n", 3, 10, ch);

    return 0;

}

lenmodifier的可选参数：
长度修饰符                                          说明
hh                                将相应的参数按signed或unsigned char类型输出
h                                  将相应的参数按signed或unsigned short类型输出
l                                   将相应的参数按signed或unsigned long或宽字符类型输出
ll                                  将相应的参数按signed或unsigned long long类型输出
j                                    intmax_t或uintmax_t
z                                   size_t
t                                   ptrdiff_t
L                                  long double

convtype的可选参数：
转换类型                             说明
d、i                     有符号十进制
o                           无符号八进制
u                          无符号十进制
x、X                    无符号十六进制
f、F                     双精度浮点数
e、E                    指数格式双精度浮点数
g、G                   根据转换后的值解释为f、F、e或者E
a、A                   十六进制指数格式双精度浮点数
c                          字符（若带长度修饰符l，为宽字符）
s                           字符串（若带长度修饰符l，为宽字符）
p                          指向void的指针
n                        到目前为止，此printf调用的字符的数目将被写入到指针所指向的带符号整形中
%                         一个%字符
C                          宽字符（XSI扩展，等效于lc）
S                          宽字符串（XSI扩展，等效于ls）

这一篇文章搞定printf的输出格式问题。
