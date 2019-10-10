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
mod_timer(&my_timer, jiffies + 5*HZ);

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
注：app中没有msleep;需要使用usleep();在#include <unistd.h>中

3. 得到系统时间
struct timeval {
	__kernel_time_t		tv_sec;		/* seconds */
	__kernel_suseconds_t	tv_usec;	/* microseconds */
};
void do_gettimeofday(struct timeval *tv);

4. 应用中获得系统时间
#include<sys/time.h>
struct  timeval{
       long  tv_sec;  /*秒*/
       long  tv_usec; /*微妙*/
}；
int gettimeofday(struct  timeval*tv,struct  timezone *tz )
在gettimeofday()函数中tv或者tz都可以为空。如果为空则就不返回其对应的结构体。
函数执行成功后返回0，失败后返回-1，错误代码存于errno中。
