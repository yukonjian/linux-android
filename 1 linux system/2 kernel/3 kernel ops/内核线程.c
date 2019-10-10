1. 内核线程
https://blog.csdn.net/sharecode/article/details/40076951
#include <linux/sched.h>  //wake_up_process()
#include <linux/kthread.h>
1.1 线程创建
struct task_struct *kthread_create(int (*threadfn)(void *data),
void *data,const char *namefmt, ...);//注意，第二个参数data用于向线程函数传递参数
1.2 启动线程
线程创建后，不会马上运行，而是需要将kthread_create() 返回的task_struct指针传给
wake_up_process(struct task_struct *)，然后通过此函数运行线程。
1.3 线程停止
int kthread_stop(struct task_struct *k);
1.4 线程函数
int threadfunc(void *data){
  while(1){
    set_current_state(TASK_UNINTERRUPTIBLE);//b:将当前的状态表示设置为休眠
    if(kthread_should_stop()) break;  //a:解释见“注意”
    if(){//条件为真
      //进行业务处理
    }
    else{//条件为假
      //让出CPU运行其他线程，并在指定的时间内重新被调度
      schedule_timeout(HZ);   //C:休眠，与set_current_state配合使用，需要计算，这里表示休眠一秒
    }
  }
  return 0;
}
注意：
a. 值得一提的是kthread_should_stop函数，我们需要在开启的线程中嵌入该函数并检查此函数的返回值，
否则kthread_stop是不起作用的;在调用kthread_stop函数时，线程函数不能已经运行结束。
b. 休眠有两种相关的状态:TASK_INTERRUPTIBLE and TASK_UNINTERRUPTIBLE。
处于TASK_UNINTERRUPTIBLE状态的进程会忽略信号，而处于TASK_INTERRUPTIBLE状态的进程
如果收到信号会被唤醒并处理信号(然后再次进入等待睡眠状态)。两种状态的进程位于同一个等待队列上，等待某些事件，不能够运行。
c.schedule_time(s*HZ)的参数为节拍数，HZ宏每个系统定义不一样，表示每一秒时钟中断数，如在2.6中为1000，2.4中为100, s为秒单位，
例如如果要休眠20ms，则schedule_time(0.02*HZ)就可以了。
1.5 线程相关的命令
1.5.1 可以使用top命令来查看线程（包括内核线程）的CPU利用率。命令如下：
top –p 线程号
1.5.2 可以使用下面命令来查找线程号：
ps aux | grep 线程名
1.5.3可以用下面的命令显示所有内核线程：
ps afx
