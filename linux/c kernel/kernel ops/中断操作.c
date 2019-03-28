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
