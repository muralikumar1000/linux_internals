/*
<<doc
Name: Murali venkata vijay kumar
Date:
Description:
Sample i/p:./a.out date
Sample o/p:This is the CHILD process, with id 11612
			Wed Apr  4 13:27:19 IST 2012
			Child exited with status 0
doc
*/
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	/* if no CLA arguments are passed throws error*/
	if(argc == 1){
		printf("%s \nUsage: %s args...\n",argv[0],argv[0]);
		return 1;
	}
	int status;
	pid_t pid;

	pid = fork();

	switch(pid){
		case -1:
			perror("fork");
			exit(0);
			/* this case executes in child process*/
		case 0:
			/* prints child status*/
			printf("This is the CHILD process, with id %d\n",getpid());

			char *args[] = {argv[1],NULL};//arguments for execcute process function

			execvp(argv[1], args);//ececutes arguments passed from CLA
			break;
			/* this case executes in parent process*/
		default:
			
			wait(&status);//waits for child to exit 

			/*prints childs exit status*/
			printf("Child exited with status %d\n",status);
			}


}

