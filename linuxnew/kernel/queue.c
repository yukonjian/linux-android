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
  d)  int queue_delayed_work(struct workqueue_struct *wq,
            struct work_struct *work, unsigned long delay);

4) 清理工作队列中的所有任务
  a) void flush_workqueue(struct workqueue_struct *wq)

5) 销毁队列，释放资源
  a) void destroy_workqueue(struct workqueue_struct *wq);
