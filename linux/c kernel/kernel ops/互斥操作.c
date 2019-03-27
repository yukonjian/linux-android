1.信号量
struct semaphore sem;
sema_init(&sem, count);
void down(struct semaphore *sem)	//如果不能获取，切换状态至TASK_UNINTERRUPTIBLE*/
void up(struct semaphore *sem);

2.互斥量
struct mutex xxx_mutex;
void mutex_init(struct mutex *lock);
void mutex_lock(struct mutex *lock);
int mutex_trylock(struct mutex *lock);	//成功返回1；失败返回0
void mutex_unlock(struct mutex *lock);
