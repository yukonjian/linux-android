1. 内核定时器
1) 定义并初始化定时器
struct timer_list mytimer;
#define init_timer(timerp)
2) 初始化定时器结构体的 超时时间 定时器处理函数 处理函数传参
void timer_func(unsigned long data) //定义定时器处理函数
my_timer.expires = jiffies + 5*HZ;
my_timer.function = timer_func;
my_timer.data = (unsigned long)99;
3) 激活定时器，只执行一次处理函数
void add_timer(struct timer_list *timer)
4) 再次激活定时器
my_timer.expires = jiffies + 5*HZ;
add_timer(&my_timer);
or:
int mod_timer(struct timer_list *timer, unsigned long expires)
可以修改并未结束的定时器相当于：
del_timer(timer); timer->expires = expires; add_timer(timer);
return ：mod_timer() of an inactive timer returns 0, mod_timer() of an  active timer returns 1
5) 若想在定时器没有超时前取消定时器,注销模块时要使用
int del_timer(struct timer_list *timer)
return : del_timer() of an inactive timer returns 0, del_timer() of an  active timer returns 1

2. 延时
1) delay
void udelay(unsigned long usecs);	//该种延时属于忙等待
void mdelay(unsigned long msecs);
2) sleep
void msleep(unsigned int msecs)
void usleep_range(unsigned long min, unsigned long max)
