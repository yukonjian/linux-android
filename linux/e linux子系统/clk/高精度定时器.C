参考文档
hrtimer的简单使用 + 原理和实现
https://blog.csdn.net/lqxandroid2012/article/details/51471188
第10章　中断与时钟之内核定时器
https://blog.csdn.net/xiezhi123456/article/details/80421246
1. 高精度配置
CONFIG_HIGH_RES_TIMERS:                                                                                                                                            |
  |                                                                                                                                                                    |
  | This option enables high resolution timer support. If your                                                                                                         |
  | hardware is not capable then this option only increases                                                                                                            |
  | the size of the kernel image.                                                                                                                                      |
  |                                                                                                                                                                    |
  | Symbol: HIGH_RES_TIMERS [=y]                                                                                                                                       |
  | Prompt: High Resolution Timer Support                                                                                                                              |
  |   Defined at kernel/time/Kconfig:16                                                                                                                                |
  |   Depends on: GENERIC_TIME [=y] && GENERIC_CLOCKEVENTS [=y]                                                                                                        |
  |   Location:                                                                                                                                                        |
  |     -> Kernel Features                                                                                                                                             |
  |   Selects: TICK_ONESHOT [=y]

2. 包含头文件
#include <linux/hrtimer.h>

3. 基本使用
#define BACKLIGHT_POOL_NS	(1000*200*1)
struct hrtimer backlight_hrt; // 内核高精度定时器


static enum hrtimer_restart backlight_hrtimer_callback(struct hrtimer *hrt)
{
	hrtimer_forward_now(hrt, ns_to_ktime(BACKLIGHT_POOL_NS));//把hrtimer的时间前移了time_ns纳秒

	return HRTIMER_RESTART;
}

static int backlight_hrtimer_init(void)
{
	printk("BACKLIGHT: init backlight_hrtimer_init;\n");

	hrtimer_init(&backlight_hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL); /* 初始化高精度定时器 */

	printk("BACKLIGHT: init backlight_hrtimer_init;\n");
	backlight_hrt.function = backlight_hrtimer_callback;

	hrtimer_start(&backlight_hrt, ns_to_ktime(BACKLIGHT_POOL_NS), HRTIMER_MODE_REL);// 启动hrtimer
}
