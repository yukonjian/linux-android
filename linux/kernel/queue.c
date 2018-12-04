1. 工作队列
工作队列（workqueue）是另外一种将工作推后执行的形式.工作队列可以把工作推后，交由一个内核线程去执行，
也就是说，这个下半部分可以在进程上下文中执行。最重要的就是工作队列允许被重新调度甚至是睡眠。
1) 工作队列
  a) struct workqueue_struct *create_workqueue(const char *name)
  b) struct workqueue_struct *create_singlethread_workqueue(const char *name)

2) 工作的创建
  a) 静态定义
   DECLARE_WORK(name, void (*func)(struct work_struct *work));
   DECLARE_DELAY_WORK(name, void (*func)(struct work_struct *work));
  b) 动态创建
   struct work_struct work;
   INIT_WORK(struct work_struct * work, void (*func) (void *));

3) 调度工作
  a) int schedule_work(struct work_struct *work);
  b) int schedule_delayed_work(struct work_struct *work, unsigned long delay);  /* delay is jiffies */
  c) int queue_work(struct workqueue_struct *wq, struct work_struct *work);
  d) int queue_delayed_work(struct workqueue_struct *wq,
            struct work_struct *work, unsigned long delay);

4) 清理工作队列中的所有任务
  void flush_workqueue(struct workqueue_struct *wq)

5) 销毁队列，释放资源
  void destroy_workqueue(struct workqueue_struct *wq);

2. 等待队列
阻塞操作是指：在执行设备操作时，若不能获得资源，则挂起进程（进程进入睡眠状态）直到满足可操作的条件再进行操作。
1) 等待队列头部定义和初始化
  a) 静态定义
   DECLARE_WAIT_QUEUE_HEAD(name);
  b) 动态定义
   wait_queue_head_t my_queue;
   init_waitqueue_head(&my_queue);

2) 定义等待队列元素
  a) 静态定义
    DECLARE_WAITQUEUE(name, tsk); /* tsk 会赋值给 name.private, 一般的值是：current */

3) 添加和移除等待队列
  void add_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
  void remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);

4) 等待事件
  wait_event(queue, condition)
  注：queue ：等待队列头（并不是指针）；condition ：只有当条件满足时才会结束等待。
  wait_event_interruptible(queue, condition)
  wait_event_timeout(queue, timeout)
  wait_event_interruptible_timeout(queue, condition, timeout)

5) 唤醒队列
  void wake_up(wait_queue_head_t *q);
  void wake_up_interruptible(wait_queue_head_t *q);
