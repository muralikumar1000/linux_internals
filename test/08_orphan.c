
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
		//Variable declaration
		pid_t pid;
		//Creating a new process
		pid = fork();
		

		switch(pid)
		{
				case -1: 
						perror("Fork");
						exit(0);
				case 0 : 
						printf("I am child process : pid = %d\n",  getpid());
						printf("The pid of the parent  = %d\n",getppid());
						sleep(20);
						printf("I am child process : pid = %d\n",  getpid());
						printf("The pid of the parent  = %d\n",getppid());
						break;
				default :   
						printf("The parent PID is  %d\n",getpid());
						printf("The pid of the parent  = %d\n",getppid());

		}
		return 0;
}


