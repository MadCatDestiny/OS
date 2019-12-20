#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() 
{ 
    while (1)
	{
		int fd1[2]; 
		int fd2[2];
	
		time_t sec;
		time_t child_sec;
		__pid_t p; 
	
		if (pipe(fd1)==-1) 
		{ 
			fprintf(stderr, "Pipe Failed" ); 
			return 1; 
		} 
		if (pipe(fd2)==-1) 
		{ 
			fprintf(stderr, "Pipe Failed" ); 
			return 1; 
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
			close(fd1[0]);
			sec = time(NULL);
			write(fd1[1], &sec, sizeof(time_t)); 
			printf("Writen in child %s\n", ctime(&sec));	
			close(fd1[1]); 
			int res = 0;
			waitpid(p, &res, 0); 
			close(fd2[1]);
			read(fd2[0], &child_sec, sizeof(time_t));
			printf("Time in in parent: %s\n",ctime(&child_sec));
			printf("Latency in parent %ld\n", child_sec - sec); 
			close(fd2[0]); 

		} 
	  
		// child process 
		else
		{ 
			close(fd1[1]);
			printf("Sleep 1s\n");
			sleep(1);
			read(fd1[0],&child_sec , sizeof(time_t));
			printf("Time in in child: %s\n",ctime(&child_sec));
			printf("Latency in child: %ld\n",time(NULL) - child_sec);
			close(fd1[0]); 
			close(fd2[0]); 
			printf("Sleep 1s\n");
			sleep(1);
			child_sec =  time(NULL);
			write(fd2[1],&child_sec, sizeof(time_t)); 
			close(fd2[1]); 
			exit(0); 
		} 
		sleep(10);
	}
} 
