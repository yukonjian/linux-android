1.定时器
#include <linux/timer.h>
struct timer_list mytimer;
void init_timer(struct timer_list *timer);
初始化定时器结构体的 超时时间 定时器处理函数 处理函数传参
void timer_func(unsigned long data) //定义定时器处理函数
my_timer.expires = jiffies + 5*HZ;
my_timer.function = timer_func;
my_timer.data = (unsigned long)99;
激活定时器，只执行一次处理函数
void add_timer(struct timer_list *timer)

再次激活定时器
my_timer.expires = jiffies + 5*HZ;
add_timer(&my_timer);
or:
int mod_timer(struct timer_list *timer, unsigned long expires)
可以修改并未结束的定时器相当于：
del_timer(timer); timer->expires = expires; add_timer(timer);
return ：mod_timer() of an inactive timer returns 0, mod_timer() of an  active timer returns 1
若想在定时器没有超时前取消定时器,注销模块时要使用
int del_timer(struct timer_list *timer)
return : del_timer() of an inactive timer returns 0, del_timer() of an  active timer returns 1

2. 时间延时
1) delay 忙等待
void udelay(unsigned long usecs);	//该种延时属于忙等待
void mdelay(unsigned long msecs);
2) sleep 睡眠等待
void msleep(unsigned int msecs)
void usleep_range(unsigned long min, unsigned long max)

3. 得到系统时间
void do_gettimeofday(struct timeval *tv);
