https://blog.csdn.net/lilichang11106/article/details/84069357
1.信号量
#include <linux/semaphore.h>
struct semaphore sem;
sema_init(&sem, count);
void down(struct semaphore *sem)	//如果不能获取，切换状态至TASK_UNINTERRUPTIBLE*/
int down_interruptible(struct semaphore *sem)
返回0：成功获得信号量
返回-EINTR：没有获得信号量
void up(struct semaphore *sem);
/* Unlike mutex_trylock, this function can be used from interrupt context,
 * and the semaphore can be released by any task or interrupt.
 */
int down_trylock ( struct  semaphore * sem )
返回0：成功获得信号量
返回1：没有获得信号量

1.1 信号量completion
include/linux/completion.h
struct completion x;
void init_completion(struct completion *x)
void wait_for_completion(struct completion *);该函数执行一个非中断的等待，并且是阻塞型的；
unsigned long wait_for_completion_timeout(struct completion *x,unsigned long timeout);//该函数是延迟等待，返回值大于0，表示还没等到延迟的时间，信号量已经被释放，即该线程已经被唤醒；可用于同步阻塞。
void complete(struct completion *);
注意：每次使用信号量之前都必须重新初始化，因为一旦释放后，该结构就不存在了。

2.互斥量
struct mutex xxx_mutex;
void mutex_init(struct mutex *lock);
void mutex_lock(struct mutex *lock);
/* This function must not be used in interrupt context */
int mutex_trylock(struct mutex *lock);	//成功返回1；失败返回0
void mutex_unlock(struct mutex *lock);

3. 自旋锁
3.1 定义自旋锁变量
spinlock_t testlock；
3.2 初始化锁
spin_lock_init(&testlock)； //可以使用DEFINE_SPINLOCK(testlock)替代上两步操作
3.3 获取锁
spin_lock/spin_lock_irq/spin_lock_irqsave
3.3.1
spin_lock_irq  = spin_lock + local_irq_disable()
spin_lock比spin_lock_irq速度快，但是它并不是任何情况下都是安全的。
在中断程序中获得锁，不能使用spin_lock
sample:
进程A中调用了spin_lock（&lock）然后进入临界区，此时来了一个中断(interrupt），
该中断也运行在和进程A相同的CPU上，并且在该中断处理程序中恰巧也会spin_lock(&lock)
试图获取同一个锁。由于是在同一个CPU上被中断，进程A会被设置为TASK_INTERRUPT状态，
中断处理程序无法获得锁，会不停的忙等，由于进程A被设置为中断状态，schedule（）进程调度就
无法再调度进程A运行，这样就导致了死锁！
3.3.2
spin_lock_irqsave = spin_lock_irq + 保存当前中断寄存器flag状态
spin_lock_irqsave锁返回时，中断状态不会被改变，调用spin_lock_irqsave前是开中断返回就开中断。
spin_lock_irq锁返回时，永远都是开中断，即使spin_lock_irq前是关中断
3.4 释放锁
spin_unlock/spin_unlock_irq/spin_unlock_restore
