1. 什么是workqueue
1.1 Linux中的Workqueue机制就是为了简化内核线程的创建。通过调用workqueue的接口就能创建内核线程。
并且可以根据当前系统CPU的个数创建线程的数量，使得线程处理的事务能够并行化。
1.2 工作队列（workqueue）是另外一种将工作推后执行的形式.工作队列可以把工作推后，交由一个内核线程去执行，
 也就是说，这个下半部分可以在进程上下文中执行。
1.3 最重要的就是工作队列允许被重新调度甚至是睡眠。
2. 数据结构
2.1 我们把推后执行的任务叫做工作（work），描述它的数据结构为work_struct:
struct work_struct {
    atomic_long_t data;       /*工作处理函数func的参数*/
#define WORK_STRUCT_PENDING 0        /* T if work item pending execution */
#define WORK_STRUCT_STATIC 1        /* static initializer (debugobjects) */
#define WORK_STRUCT_FLAG_MASK (3UL)
#define WORK_STRUCT_WQ_DATA_MASK (~WORK_STRUCT_FLAG_MASK)
    struct list_head entry;        /*连接工作的指针*/
    work_func_t func;              /*工作处理函数*/
#ifdef CONFIG_LOCKDEP
    struct lockdep_map lockdep_map;
#endif
};
2.2 这些工作以队列结构组织成工作队列（workqueue），其数据结构为workqueue_struct:
truct cpu_workqueue_struct {
 spinlock_t lock;/*因为工作者线程需要频繁的处理连接到其上的工作，所以需要枷锁保护*/
 struct list_head worklist;
 wait_queue_head_t more_work;
 struct work_struct *current_work; /*当前的work*/
 struct workqueue_struct *wq;   /*所属的workqueue*/
 struct task_struct *thread; /*任务的上下文*/
} ____cacheline_aligned;
在该结构主要维护了一个任务队列，以及内核线程需要睡眠的等待队列，另外还维护了一个任务上下文，即task_struct。
3 工作队列的使用
3.1 创建工作queue
