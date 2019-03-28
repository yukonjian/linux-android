1. 中断请求函数 request_irq()
int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,const char *name, void *dev)；
参数：
irq：中断编号（每个中断源有唯一编号）,这里的中断编号不是看硬件手册，与裸机不同。由内核分配。
可以在如下文件中查找
irqs.h \linux-3.5\arch\arm\mach-exynos\include\mach
handler：中断服务函数指针，原型typedef irqreturn_t (*irq_handler_t)(int, void *);
中断名name：
中断名字，在cat /proc/interrupts中可以看到此名称，同时会出现/proc/irq/
irq号/name文件夹出现
dev_id:
硬件中断号共享：
在中断服务程序中读取寄存器的状态判断是哪一个中断。
分享中断号：
里与硬件上的共享中断不一样，当一个中断信号来了，一个中断的到来可以调用多个中断处理程序，每个中断处理函数均会被调用。
