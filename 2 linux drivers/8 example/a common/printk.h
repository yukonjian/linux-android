/*******************************************************************************************/
/* print */
#define CONFIG_DRVTEST_DEBUG

#ifdef  CONFIG_DRVTEST_DEBUG
#define dprintk(fmt, args...)  printk(KERN_DEBUG"[DRVTEST] : ""Fun is %s; Line: %d;" fmt, __FUNCTION__, __LINE__, ##args)
#else
#define dprintk(fmt, args...)  do{ }while(0)
#endif

#define eprintk(fmt, args...)  printk(KERN_ERR"[DRVTEST] : "fmt, ##args)
#define iprintk(fmt, args...)  printk(KERN_INFO"[DRVTEST] : "fmt, ##args)
/*******************************************************************************************/
