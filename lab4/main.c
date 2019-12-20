#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() 
{ 
		time_t sec;
		time_t child_sec;
		__pid_t p; 
		unlink("fifo");
		if((mkfifo("fifo", 0777)) == -1)
		{
			printf("Can't create FIFO\n");
			exit(0);
		}	
		
		p = fork(); 
        
		
		if (p < 0) 
		{ 
			printf("fork Failed" ); 
			return 1; 
		} 
	  
		// Parent process 
		else if (p > 0) 
		{ 
			int fd = open("fifo", O_RDONLY);
			if(fd == -1)
			{
				printf("PARENT: Can't open FIFO\n");
				exit(0);
			}
			sec = time(NULL);
			write(fd, &sec, sizeof(time_t)); 
			printf("Writen in child %ld\n", sec);
			int res = 0;
			waitpid(p, &res, 0); 
			read(fd, &child_sec, sizeof(time_t));
			printf("Latency in parent %ld\n", child_sec - sec); 
			close(fd); 

		} 
	  
		// child process 
		else
		{ 
			int fd = open("fifo", O_WRONLY);
			if(fd == -1)
			{
				printf("CHILD: Can't open FIFO\n");
				exit(0);
			}
			read(fd,&child_sec , sizeof(time_t));
			printf("Latency in child: %ld\n",time(NULL) - child_sec);
			sleep(1);
			child_sec =  time(NULL);
			write(fd,&child_sec, sizeof(time_t)); 
			exit(0); 
		} 
} 