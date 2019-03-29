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
flags:
IRQF_TRIGGER_RISING; IRQF_TRIGGER_FALLING; IRQF_TRIGGER_HIGH; IRQF_TRIGGER_LOW; IRQF_SHARED;

void free_irq(unsigned int irq, void *dev_id)

查看中断信息：cat /proc/interrupts

设备树中的中断的使用

unsigned int irq_of_parse_and_map(struct device_node *dev, int index)；
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
    struct of_phandle_args oirq;
    if (of_irq_parse_one(dev, index, &oirq))－－－－分析device node中的interrupt相关属性
        return 0;
    return irq_create_of_mapping(&oirq);－－－－－创建映射，并返回对应的IRQ number
}

2. 中断的低半步操作 tasklet
#include <linux/interrupt.h>
tasklet是使用软中断实现的，无法睡眠
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
tasklet_schedule(struct tasklet_struct *tasklet);
