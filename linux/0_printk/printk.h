#define CONFIG_XXX_DEBUG

#ifdef  CONFIG_XXX_DEBUG
static int debug  = 1;
#else
static int debug  = 0;
#endif

#define dprintk(fmt, args...) \
do { \
	if (debug) \
		printk(KERN_DEBUG"[XXX]""Fun is %s; Line: %d;" fmt, __FUNCTION__, __LINE__, ##args); \
} while (0)

#define eprintk(fmt, args...)  printk(KERN_ERR"[XXX]"fmt, ##args)
#define iprintk(fmt, args...)  printk(KERN_INFO"[XXX]"fmt, ##args)
