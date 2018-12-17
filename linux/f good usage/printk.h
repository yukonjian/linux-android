/*******************************************************************************************/
/* print */
#define CONFIG_DRVTEST_DEBUG

#ifdef  CONFIG_DRVTEST_DEBUG
#define printk_dbg(fmt, args...)  printk(KERN_DEBUG"[DRVTEST] : ""Fun is %s; Line: %d;" fmt, __FUNCTION__, __LINE__, ##args)
#else
#define printk_dbg(fmt, args...)  do{ }while(0)
#endif

#define printk_err(fmt, args...)  printk(KERN_ERR"[DRVTEST] : "fmt, ##args)
#define printk_info(fmt, args...)  printk(KERN_INFO"[DRVTEST] : "fmt, ##args)
/*******************************************************************************************/
