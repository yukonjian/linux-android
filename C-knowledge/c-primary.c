1. 指针和数据的相加，指针加1相当于加4
如：
  int a = 300;
  int *b = 500;

  int tmp = a + b;
  其中输出tmp = 1700;

2. C++ 中的string 类型转换未char型使用
srting name; //定义srting类型
name.c_str(); //将string转换未char类型

3. 字符转义
\t 表示跳转到下一个制表位的位置，一般在dos显示，8个字符为一个制表位，相当于按下tab键
\r 是回车，相当于enter键。
\b 就是往后倒退一次，就相当于按下 backspace键
