1.工作与工作队列
1.1 工作队列的概念
1.1.1 Linux中的Workqueue机制就是为了简化内核线程的创建。通过调用workqueue的接口就能创建内核线程。
并且可以根据当前系统CPU的个数创建线程的数量，使得线程处理的事务能够并行化。
1.1.2 工作队列（workqueue）是另外一种将工作推后执行的形式.工作队列可以把工作推后，交由一个内核线程去执行，
 也就是说，这个下半部分可以在进程上下文中执行。
1.1.3 最重要的就是工作队列允许被重新调度甚至是睡眠。
1.2 工作的创建
1.2.1 静态创建工作队列
DECLARE_WORK(name,void (*func) (void *), void *data);
#define DECLARE_WORK(n, f) struct work_struct n = __WORK_INITIALIZER(n, f)
1.2.2 动态创建工作队列
struct work_struct  commit_work;
INIT_WORK(struct work_struct * work, work_func);
typedef void (*work_func_t)(void *work);
1.3 工作队列的创建
struct workqueue_struct *Display_commit_work;
1.2.1 只创建一个内核线程。
struct workqueue_struct *create_singlethread_workqueue(const char *name)
1.2.2 为系统中的每个CPU都创建一个内核线程
create_workqueue
1.4 工作的调度
int queue_work(struct workqueue_struct *wq, struct work_struct *work)
延时工作调度
queue_delayed_work
1.5 在卸载模块时，需刷新并注销工作队列
void flush_workqueue(struct workqueue_struct *wq)
void destroy_workqueue(struct workqueue_struct *wq)

2. 等待队列
每一个等待队列项代表一个睡眠进程，该进程等待某一事件的发生。
2.1 定义并初始化等待队列头
typedef struct __wait_queue_head wait_queue_head_t;
wait_queue_head_t *wq；
#define init_waitqueue_head(wq)
2.2 进程进入休眠
#define wait_event_interruptible(wq, condition) //wq为等待队列头结构体，并不是指针
返回0：正常被唤醒；
返回非0：休眠被中断，驱动返回 -ERESTARTSYS
wait_event_interruptible_timeout(wq, condition, timeout) //timeout = s*HZ;
返回0：正常被唤醒和时间超时；
返回非0：休眠被中断，驱动返回 -ERESTARTSYS
2.3 唤醒进程
#define wake_up_interruptible(x)	__wake_up(x, TASK_INTERRUPTIBLE, 1, NULL)  //参数x为等待对了头的指针
