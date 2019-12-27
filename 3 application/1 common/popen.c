1. popen 的使用方法及场景
https://blog.csdn.net/u012385733/article/details/79967753

1.Popen的应用场景
popen应用于执行shell命令，并读取此命令的返值，或者与执行的命令进行交互。

2.Popen的实现
Popen()函数通过创建一个管道，调用fork()产生一个子进程，然后调用execl("/bin/sh", "sh", "-c”,command,0);执行shell命令。可以通过这个管道进行标准输入输出操作，下面会附上源码。

3.Pclose操作
Pclose()函数会闭标准i/0流，等待子进程结束，然后返回shell终止状态。如果不执行，则pclose()返回终止状态就是shell的exit状态。

4. 使用例子
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;
	char buf[1024] = "";

	fp = popen("ls -al", "r");
	if(fp == NULL)
	{
		perror("popen error\n");
		return -1;
	}
	while(fgets(buf, sizeof(buf), fp) != 0)
	{
		printf("%s\n", buf);
		memset(buf, 0x0, sizeof(buf));
	}
	pclose(fp);
	return 0;
}
