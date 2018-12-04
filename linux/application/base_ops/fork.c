1. 进程使用流程
创建-》判断-》使用-》return or exit.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t childpid1, childpid2, childpid3;
    int status;
    int num;

    /* 这里不可以一下就创建完子进程，要用
    *要 创建-》判断-》使用-》return or exit.更不能这样如test2.c
    *childpid1 = fork();
    *childpid2 = fork();
    *childpid3 = fork();
    */
    childpid1 = fork();                                             //创建
    if(0 == childpid1)                                              //判断
    {                                                                                   //进入
        printf("In child1 process\n");
        printf("\tchild pid = %d\n", getpid());
        exit(EXIT_SUCCESS);                                         //退出
    }
    childpid2 = fork();
    if(0 == childpid2)
    {
        printf("In child2 processd\n");
        printf("\tchild pid = %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    childpid3 = fork();
    if(0 == childpid3)
    {
        printf("In child3 process\n");
        printf("\tchild pid = %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    //这里不可以用wait(NULL)，多个子进程是不可以用wait来等待的，它只会等待一个 其它都成僵尸了
    waitpid(childpid1, NULL, 0);
    waitpid(childpid2, NULL, 0);
    waitpid(childpid3, NULL, 0);
    puts("in parent");

    exit(EXIT_SUCCESS);

}  
