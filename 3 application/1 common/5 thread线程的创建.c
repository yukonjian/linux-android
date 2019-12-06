#include<pthread.h>
1. 线程创建
int pthread_create(pthread_t *tidp,const pthread_attr_t *attr,
(void*)(*start_rtn)(void*),void *arg);

tidp：线程号
attr：线程属性
start_rtn：线程执行的函数
arg：函数带入的参数
return: 线程创建成功，则返回0。若线程创建失败，则返回出错编号

2. 线程退出
http://www.man7.org/linux/man-pages/man3/pthread_join.3.html
int pthread_join(pthread_t thread, void **retval);
2.1 用于等待其他线程结束：当调用 pthread_join() 时，当前线程会处于阻塞状态，直到被调用的线程结束后，当前线程才会重新开始执行。
2.2 对线程的资源进行回收：如果一个线程是非分离的（默认情况下创建的线程都是非分离）并且没有对该线程使用 pthread_join() 的话，该线程结束后并不会释放其内存空间，这会导致该线程变成了“僵尸线程”。

3. 内核级线程的创建
内核级线程创建时先设置线程属性PTHREAD_SCOPE_SYSTEM，代码如下，:
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); //设置内核级的线程,以获取较高的响应速度
//创建线程
ret = pthread_create(&iAcceptThreadId, &attr, AcceptThread, NULL);

3.1 线程的3种实现方式--内核级线程, 用户级线程和混合型线程
https://www.cnblogs.com/feng9exe/p/7890934.html

4 linux 驱动中的线程创建
4.1 kernel_thread 
#include <linux/sched.h>
https://blog.csdn.net/ezimu/article/details/60467017
