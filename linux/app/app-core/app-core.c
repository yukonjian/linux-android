1. 时间操作
头文件 <time.h>
struct timespec {
time_t tv_sec; // seconds
long tv_nsec; // and nanoseconds
};
一般由函数int clock_gettime(clockid_t, struct timespec *)获取特定时钟的时间，常用如下4种时钟：
CLOCK_REALTIME 统当前时间，从1970年1.1日算起
CLOCK_MONOTONIC 系统的启动时间，不能被设置
CLOCK_PROCESS_CPUTIME_ID 本进程运行时间
CLOCK_THREAD_CPUTIME_ID 本线程运行时间
