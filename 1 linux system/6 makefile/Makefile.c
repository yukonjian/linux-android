1. makefile的命令前面添加@，可以忽略掉命令的打印
例如：
1) echo "build alsa dsp"
输出：
echo "build alsa dsp"
build alsa dsp

2) @echo "build alsa dsp"
输出：
build alsa dsp

2. .PHONY
声明假的目标；
.PHONY clean
clean:
  xxxx;
1) 即使该目录下有一个clean文件；执行make clean会执行xxxx命令；
2) 如果没有将clean声明为.PHONY，目录下有个clean文件；执行make clean将

3. Makefile 中:= ?= += =的区别
https://www.cnblogs.com/zgq0/p/8716150.html
= 是最基本的赋值
:= 是覆盖之前的值
?= 是如果没有被赋值过就赋予等号后面的值
+= 是添加等号后面的值
下面用例子来看看 = 和 := 区别
3.1、“=”
make会将整个makefile展开后，再决定变量的值。也就是说，变量的值将会是整个makefile中最后被指定的值。看例子：
      x = foo
      y = $(x) bar
      x = xyz
在上例中，y的值将会是 xyz bar ，而不是 foo bar 。
3.2、“:=”
“:=”表示变量的值决定于它在makefile中的位置，而不是整个makefile展开后的最终值。
      x := foo
      y := $(x) bar
      x := xyz
在上例中，y的值将会是 foo bar ，而不是 xyz bar 了。
