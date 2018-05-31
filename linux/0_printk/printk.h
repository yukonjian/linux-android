#define CONFIG_XXX_DEBUG

#ifdef  CONFIG_XXX_DEBUG
#define xxx_printd(fmt, args...)  printk(KERN_DEBUG"DEBUG""Fun is %s; Line: %d;" fmt, __FUNCTION__, __LINE__, ##args)
#else
#define xxx_printd(fmt, args...)  { }
#endif

#define xxx_printe(fmt, args...)  printk(KERN_ERR"ERROR"fmt, ##args)
#define xxx_printi(fmt, args...)  printk(KERN_INFO"WARNING"fmt, ##args)
