1.中断
int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev_id)
typedef irqreturn_t (*irq_handler_t)(int, void *);
static irqreturn_t intr_handler(int irq, void *dev_id)
enum irqreturn {
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
};
typedef enum irqreturn irqreturn_t;

1.1 参数
irq：中断编号（每个中断源有唯一编号）,这里的中断编号不是看硬件手册，与裸机不同。由内核分配。
可以在如下文件中查找: irqs.h \linux-3.5\arch\arm\mach-exynos\include\mach
flags:
IRQF_DISABLED; IRQF_TRIGGER_RISING; IRQF_TRIGGER_FALLING; IRQF_TRIGGER_HIGH; IRQF_TRIGGER_LOW; IRQF_SHARED;
name: 中断名字，在cat /proc/interrupts中可以看到此名称，同时会有/proc/irq/irq号/name的文件夹
dev_id:
硬件中断号共享：
在中断服务程序中读取寄存器的状态判断是哪一个中断。
分享中断号：
与硬件上的共享中断不一样，当一个中断信号来了，一个中断的到来可以调用多个中断处理程序，每个中断处理函数均会被调用。
1.2 中断的释放
void free_irq(unsigned int irq, void *dev_id)
1.3 设备树中的中断的使用
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)；
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
    struct of_phandle_args oirq;
    if (of_irq_parse_one(dev, index, &oirq))－－－－分析device node中的interrupt相关属性
        return 0;
    return irq_create_of_mapping(&oirq);－－－－－创建映射，并返回对应的IRQ number
}

2. 中断的低半步操作 tasklet
http://blog.chinaunix.net/uid-28236237-id-3450753.html
#include <linux/interrupt.h>
tasklet是使用软中断实现的，无法睡眠,同一个tasklet不能在两个CPU上同时运行，但是不同tasklet可能在不同CPU上同时运行，则需要注意共享数据的保护。
2.1 定义并初始化 struct tasklet_struct结构体
struct tasklet_struct
{
	void (*func)(unsigned long);	//tasklet处理函数
	unsigned long data;	//给处理函数的传参
}
2.1.1 静态定义
 #define DECLARE_TASKLET(name, func, data) \
 struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(0), func, data }
2.2.2 动态定义
struct tasklet_struct xxx_tasklet;
void tasklet_init(struct tasklet_struct *t, void (*func)(unsigned long), unsigned long data);
2.2 调度tasklet
void tasklet_schedule(struct tasklet_struct *tasklet);
