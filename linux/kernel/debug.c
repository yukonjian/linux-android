1. Oops:错误
Linux内核在发生kernel panic时会打印出Oops信息，把目前的寄存器状态、堆栈内容、以及完整的Call trace都show给我们看，
这样就可以帮助我们定位错误。

oops的错误信息：
1）Oops首先描述了这是一个什么样的bug
BUG: unable to handle kernel NULL pointer dereference at (null)
2）然后指出了发生bug的位置，即“IP: [<f82d2005>] hello_init+0x5/0x11 [hello]”。
IP: [<f82d2005>] hello_init+0x5/0x11 [hello]
3）显示oops的错误号
Oops: 0002 [#1] SMP

解决方法：
1）使用objdump工具进行反汇编
objdump -S hello.o
2)在反汇编中查找错误的地方
*p = 1;
5:   c7 05 00 00 00 00 01    movl   $0x1,0x0
