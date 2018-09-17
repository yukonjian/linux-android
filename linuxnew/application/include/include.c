#include <fcntl.h>    /* (file control)对文件描述符的操作，open, fcntl */
#include <stdio.h>    /* 标准输入输出函数,  printf, scanf */
#include <unistd.h>   /* 针对linux系统调用的封装, read、write、close,fork、pipe，sleep, usleep */
#include <stdlib.h>   /* standard library标准库头文件,包含了C语言标准库函数的定义 */
/* stdlib.h里面定义了五种类型、一些宏和通用工具函数。 类型例如size_t、wchar_t、div_t、ldiv_t和lldiv_t；
宏例如EXIT_FAILURE、EXIT_SUCCESS、RAND_MAX和MB_CUR_MAX等等；
常用的函数如malloc()、calloc()、realloc()、free()、system()、atoi()、atol()、rand()、srand()、exit()等等。 */

#include <string.h>   /* 字符串处理，memset */

#include <sys/types.h> /* 基本系统数据类型, dev_t,size_t,pid_t  */

#include <sys/mman.h>
#include <linux/fb.h>
#include <linux/videodev2.h>
#include <linux/workqueue.h>
