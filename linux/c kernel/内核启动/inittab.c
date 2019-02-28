1.
init的进程号是1，init进程是系统所有进程的起点，Linux在完成核内引导以后，就开始运行init程序。
init程序需要读取配置文件/etc/inittab。inittab是一个不可执行的文本文件，它有若干行指令所组成。
