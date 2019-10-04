#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void onend_handler(int,void*);
void atend_handler(void);

int main(void)
{
    int count = 0;
    puts("Start main");
    printf("MAIN - The proccess id in main : %d\n", getpid());
    printf("MAIN - The parent proccess id in main : %d\n", getppid());
       __pid_t pid;
    printf("new pid : %d\n",pid = fork());
    int res = on_exit(onend_handler,0);
    int res1 = atexit(atend_handler);
    if(res != 0 && res1 != 0) 
        puts("Atexit error\n");

    
    waitpid(pid, 0, 0);
    
    return 0;
}

void onend_handler(int,void*)
{
    int a = 1/0;
    static int count = 0;
    puts("Start onexit");
    printf("%d - The proccess id in on_exit : %d\n", ++count, getpid());
    printf("%d - The parent proccess id in on_exit : %d\n", count, getppid());
}

void atend_handler(void)
{
    static int count = 0;
    puts("Start atexit");
    printf("%d - The proccess id in atexit : %d\n", ++count, getpid());
    printf("%d - The parent proccess id in atexit : %d\n", count, getppid());
}