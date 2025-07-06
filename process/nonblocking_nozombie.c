/*
<<doc
Name: Murali venkata vijay kumar
Date:
Description:
Sample i/p:
Sample o/p:
doc
*/
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	pid_t pid;
	int status, ret;

	pid = fork();

	switch (pid){
		case -1:
			perror("fork");
			exit(0);
		case 0:
			printf("A child created with pid %d\n",getpid());
			
			break;
		default:

			while((ret = waitpid(pid,&status,WNOHANG)) == 0){
				printf("parent is running\n");
			}
			printf("Child %d terminated normally with exit status %d parent terminating\n",pid,status);
	}
}

