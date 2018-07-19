1. 中断申请
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
