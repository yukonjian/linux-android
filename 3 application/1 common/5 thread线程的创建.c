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
https://blog.csdn.net/ezimu/article/details/60467017
4.1 kernel_thread
#include <linux/sched.h>
pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);
参数说明：
fn:线程函数地址
arg:线程函数的形参，没有，可以是NULL
flags:标志，一般用CLONE_KERNEL（定义在linux/sched.h中，注意有的版本中，没用定义），其他标志及含义见uapi/linux/sched.h中。
返回值：返回线程ID值。
注意：kernel_thread()由于没有用EXPORT_SYMBOL导出来，所以用kernel_thread()这能用在和内核一起编译的驱动代码中

4.2 kthread_create
#include <linux/kthread.h>
kthread_create(threadfn, data, namefmt, arg...)
参数说明：
threadfn:线程函数地址
data:线程函数形参，如果没有可以定义为NULL
namefmt,arg…:线程函数名字，可以格式化输出名字。
返回值：返回线程指针（strcut task_struct *）
注意：kthread_create()创建后，线程没有立即运行，需要将返回的值，即线程指针（struct task_struct *）,作为参数传入到wake_up_process()唤起线程运行。
注意：在编写线程循环体时，一般都要加入kthread_should_stop(),如果不加，调用kthread_stop()是没有效果的，也会导致模块退出后，线程仍然还在运行。
sample:
strcut task_struct *practice_task_p = NULL;
int my_kernel_thread(void *arg)
{
        int n = 0;
        while(1)
        {
                printk("%s: %d\n",__func__,n++);
                ssleep(3);
        if(kthread_should_stop())
                {
                        break;
                }
        }

        return 0;
}
static int __init practiceCall(void)
{
        printk("%s:\n",__func__);
        practice_task_p = kthread_create(my_kernel_thread,NULL,"practice task");
        if(!IS_ERR(practice_task_p))
                wake_up_process(practice_task_p);
        return 0;
}

static void __exit practiceCallExit(void)
{
        printk("%s:\n",__func__);
        kthread_stop(practice_task_p);
}
