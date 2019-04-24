1. 第一个启动函数 _start
 _start位于arch/arm/cpu/arm920t/start.S
 注：可以在顶层目录/system.map找到函数的地址
2. 进入第一个C函数:board_init_f() 一般是在board.c的文件中
