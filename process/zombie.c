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
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int status(pid_t pid, int limit);

int main(int argc, char *argv[]){
	umask(0);

	//Variable declaration
    pid_t pid, pid2 ;

	int j;
    //Creating a new process
     pid = fork();

	switch(pid){
		case -1:
			perror("Fork");
			exit(0);
			/* child qwill access this case 0*/
		case 0 :
			printf("%s \nA child created with pid  %d\n",argv[0],getpid());
			sleep(3); //keeps child process in sleep state
			
			break;

		/* parent will access this default case*/
		default:
			sleep(2);

			status(pid,3);//this will give status of child in sleep state,where 3 is status limit of lines
			sleep(2);
			status(pid,2);//this will give status of child in zombie state, 2 is atatus limit of lines
			
			pid2 = fork();//a second child is called from here
			/* child 2 will acces this if condition only*/
			if(pid2 == 0){
				int id = getppid();

				if(id == 1){
				printf("Process %d cleared by init\n",pid);
				}
			}
			/* parent can only access this*/
			if(pid > 0){

				waitpid(0,&pid2,WNOHANG);
			}
			
}
}

/* function to print /proc/$pid/status file*/
int status(pid_t pid, int j){
	char str[100];//for storing location path
	char buff[20];//for reading and writing from file
	int rfd;
	
	sprintf(str,"/proc/%d/status", pid);//makes path as string from obtained pid

	int fd = open(str,O_RDONLY);//open call to file
	if(fd == -1){
		perror("open error:");
              return 1;
	}

	int count = 0;
	while((rfd = read(fd,buff,20)) != 0){//read call to file

        if(rfd == -1){
        	perror("read");
            return 1;
        }
        for(int i = 0; i < rfd;i++){//for loop for checking and counting new line characters

        	if(buff[i] == '\n'){//this will count new line characters
            	count++;
            }
            if (count == j){//if requires lines are obtained, string will get terminated
                       
            	buff[i+1] = '\0';//buffer got updated with last character
			    break;
			}
		}
		printf("%s",buff);//prints the lines obtained from file
        if(count == j){//if required lines are printed reading gets terminated
           	close(fd);
            break;
		}
	}
}
