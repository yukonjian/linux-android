1. 打印例子
#ifdef  CONFIG_XXX_DEBUG
#define xxx_printd(fmt, args...)  printk(KERN_DEBUG"FLAG""Fun is %s; Line: %s;" fmt, __FUNCTION__, __LINE__, ##args)
#else
#define xxx_printd(fmt, args...)  { }
#endif

#define xxx_printe(fmt, args...)  printk(KERN_ERR"FLAG", fmt, ##args)
#define xxx_printi(fmt, args...)  printk(KERN_INFO"FLAG", fmt, ##args)
