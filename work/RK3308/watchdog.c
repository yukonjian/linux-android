卢瑞昕-luke 12:39:48
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include  <linux/watchdog.h>

static int g_watchdog_fd =0;

int enable_watchdog( int nTimeoutSeconds )
{
	if( g_watchdog_fd > 0 )
	{
		// watchdog only start once
		return 0;
	}

	g_watchdog_fd = open("/dev/watchdog", O_RDWR );
	if( g_watchdog_fd == -1)
	{
    		printf("open watchdog error \n\n\n");
    		return -1;
	}

	if( nTimeoutSeconds <=0 )
	{
		printf(" invalid watchdog timeout seconds, set default timeout as 15 seconds.\n");
		nTimeoutSeconds = 15;
	}

	ioctl( g_watchdog_fd, WDIOC_SETTIMEOUT, &nTimeoutSeconds ); //设置超时
	printf("The timeout was set to %d seconds\n", nTimeoutSeconds );

	ioctl( g_watchdog_fd, WDIOC_SETOPTIONS, WDIOS_ENABLECARD);
	return 0;
}


int clear_watchdog(void)
{
	if( g_watchdog_fd > 0 )
		ioctl(g_watchdog_fd, WDIOC_KEEPALIVE,NULL);

	return 0;
}

卢瑞昕-luke 12:40:31
以上接口已经在RK3308H上验证OK,可以封装在你的库里面，提供给上层使用
