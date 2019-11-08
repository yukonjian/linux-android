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
