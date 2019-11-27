#include <pthread.h>

linux线程的创建与使用
https://blog.csdn.net/choudan8888/article/details/98329862
linux创建线程之pthread_create
https://www.cnblogs.com/qinshizhi/p/10972649.html

#include <pthread.h>
void * disp_scale_enlarge_move_thread(void *args)
{}
  
{
	pthread_t pthid;

  if(pthread_create(&pthid,NULL,disp_scale_enlarge_move_thread, disp) == -1)
	{
		fprintf(stderr,"Create disp_scale_enlarge_thread failed;\n");
	}
}
