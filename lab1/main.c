#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void end_handler(void);

int main(void)
{
    puts("Start main");

    int res = atexit(end_handler);
    if(res != 0)
        puts("Atexit error\n");

    __pid_t pid;
    printf("new pid : %d\n",pid = fork());

    waitpid(pid, 0, 0);
    return 0;
}

void end_handler(void)
{
    static int count = 0;
    printf(" %d - The proccess id in exit : %d\n", ++count, getpid());
}