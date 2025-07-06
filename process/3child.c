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
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t pid, pid2, pid3;

	pid = fork();
	switch(pid){
		case -1:
			perror("fork");
			exit(0);
			/*child 1 access case*/
		case 0:

			_Exit(0);
			break;
			/* parent access case*/
		default:
			printf("Child 1 with pid %d created\n",pid);//prints child1 details

			pid2 = fork();//child2 is called in parent

			if(pid2 > 0){
				printf("Child 2 with pid %d created\n",pid2);//prints child2 details in parent


			}
			if(pid2 == 0){//in child2 this is processed and exited
				exit(0);
			}

			pid3 = fork();//child3 is called in parent

			if(pid3 > 0){
				printf("Child 3 with pid %d created\n",pid3);//prints child3 details in parent
			}
			if(pid3 == 0){//in child3 this is processed and exited
				exit(0);
			}
			/*status of all the childs are processed in parent*/
			if(pid3 > 0){
				int status;
				waitpid(pid,&status,0);
				printf("Child %d is terminated with code %d\n",pid,status);//child 1 status

				waitpid(pid2,&status,0);
				printf("Child %d is terminated with code %d\n",pid2,status);//child 2 status

				waitpid(pid2,&status,0);
				printf("Child %d is terminated with code %d\n",pid3,status);//child 3 status

				
			}
	}
}

