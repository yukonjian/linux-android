参考网页：shell菜鸟教程
https://www.runoob.com/linux/linux-tutorial.html

1. #!/bin/sh
#! 是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。
在一般情况下，人们并不区分 Bourne Shell (/bin/sh) 和 Bourne Again Shell (/bin/bash)，所以，像 #!/bin/sh，它同样也可以改为 #!/bin/bash。

2. 变量
2.1 变量的定义，变量名和等号之间不能有空格,变量的值和等号之间不能有空格；
your_name="runoob.com"
2.2 变量的使用，变量名外面的花括号是可选的，加不加都行，加花括号是为了帮助解释器识别变量的边界
echo "I am good at ${skill}Script"
3）unset variable_name
4）shell的类型只有字符串（字符串可以用单引号，也可以用双引号，也可以不用引号。）
   a. 有空格的字符串必须用引号括起来。
   b. 纯数字的字符串（数字中间不行有空格，两边可以）可以使用let来进行运算操作。
   c. 单引号里的任何字符都会原样输出（单引号中的单引号无法输出，可以使用双引号包含单引号来输出单引号），单引号字符串中的变量是无效的；
   d. 双引号里可以有变量,双引号里可以出现转义字符。
4. 获取当前脚本的所在目录
BUILD_DIR="$( cd "$(dirname "$0")" && pwd  )"
5. 输出重定向
https://www.cnblogs.com/ultranms/p/9353157.html
