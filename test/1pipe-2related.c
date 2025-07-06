
/*<<doc
name:Murali Venkata Vijay Kumar
date:
description:
sample i/p:
sample o/p:
doc*/
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char *argv[]){
	if(argc == 1){
		printf(" Error: No arguments passed Usage: ./pipe   <command1 > '|'   <command2>");
		exit(1);
	}
	else if(argc < 4){
		printf("Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>");
		exit(1);
	}
	////////////////////////////////////////////////////////
	int pos = 0;
	while(argv[pos] != NULL){
		
		if(strcmp(argv[pos], "|") == 0){//checking for pipe and replacing it with null
			argv[pos] = NULL;
			pos = pos+1;
			break;
		}
		pos++;
	}
	if(argv[pos] == NULL){//if no pipe found arguments are wrong
		printf("Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>");
	}
///////////////////////////////////////////////////////////////

	int pipefd[2];//fd[0] read, fd[1] write, array for pipe file discreptors
	if(pipe(pipefd) == -1){//pipe is called
		perror("pipe");
		exit(1);
	}
	int c1 = fork();//child process is created

	if(c1 == -1){
		perror("fork1");
		exit(1);
	}
	else if(c1 == 0){
		//child1
		
		close(pipefd[0]);//closing read end of pipe
		dup2(pipefd[1], 1);//stdout replaced with pipe write

		execvp(argv[1], argv+1);//first part of arguments are called
	}
	else{
		//parent

		int c2 = fork();//child2 process is created
		if(c2 == -1){
			perror("fork2");
			exit(1);
		}
		else if(c2 == 0){
			//child2
			close(pipefd[1]);//write end of pipe is closed
			dup2(pipefd[0], 0);//stdin replaced with read pipe

			execvp(argv[pos], argv + pos);//second part of arguments are called
		}
		else{
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
		}


}
}


