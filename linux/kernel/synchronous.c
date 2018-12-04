1. 互斥锁

1) 定义并初始化
  a) 静态定义并初始化
    DEFINE_MUTEX(mutex);  /* 直接定义结构体，且赋值 */
  b) 动态初始化
    struct mutex mutex;
    mutex_init(&mutex);
2) 获得锁
  mutex_lock(&mutex);
3) 释放锁
  mutex_unlock(&mutex);

2. 信号量

1) 定义并初始化
  a) 静态定义并初始化
    DEFINE_SEMAPHORE(sem)  /* 直接定义结构体，且赋值 */
  b) 动态初始化
    struct semaphore sem;
    sema_init(&sem, count);
2) 获得锁
  void down(&sem)
3) 释放锁
  void up(&sem);

3. 自旋锁
自旋锁上锁后让等待线程进行忙等待而不是睡眠阻塞，而信号量是让等待线程睡眠阻塞。
1) 定义并初始化
  spinlock_t lock;
  spin_lock_init(&lock);
2) 获得锁
  spin_lock(&lock);
3) 3) 释放锁
  spin_unlock(&lock);

/* 中断外部使用spin_lock_irq，中断内部使用spin_lock */
spin_lock_irq() = spin_lock() + local_irq_disable()
spin_unlock_irq() = spin_lock() + local_irq_disable()
spin_lock_irqsave() = spin_lock() + local_irq_save()
spin_unlock_irqsave() = spin_unlock() + local_irq_restore()
spin_lock_bh() = spin_lock() + local_bh_disable()
spin_unlock_bh() = spin_unlock() + local_bh_enable()
