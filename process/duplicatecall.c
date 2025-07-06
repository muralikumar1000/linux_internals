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
#include<errno.h>

#define MAX 10
int main(int argc, char *argv[]){


	printf("1.print to file\n");
	printf("2.print on screen\n");
	int option;
	scanf("%d",&option);

///////////////////////////////////////////////////////////////////////////////

	if(option == 1 ){
		/* standard output FD is duplicated for future use*/
		int stdout_copy = dup(1);
		if(stdout_copy == -1){
			perror("dup");
			return 1;
		}


		/* file opened in write only mode flag , with previously exist Oexcl flag, if not create with Ocreat flag */
		int dst_fd;
		if(argv[1] == NULL){
			dst_fd = open("file1.txt",O_EXCL | O_CREAT | O_WRONLY, 0666);
		}
		else{
			dst_fd = open(argv[1],O_EXCL | O_CREAT | O_WRONLY, 0666);
		}

		if(errno == EEXIST){
			close(dst_fd); //if file already exists, it is closed due to error generated
			if(argv[1] == NULL){
				dst_fd = open("file1.txt",O_WRONLY);//file re opened in write only mode
			}
			else{
				dst_fd = open(argv[1],O_WRONLY);//file re opened in write only mode
			}
		}
		if(dst_fd == -1){
			perror("open");
			return 2;
		}

		/* destination file FD is placed at STDOUT(1) position, and STDOUT(1) is closed*/
		int stdop_file = dup2(dst_fd,1);
		if(stdop_file == -1){
			perror("dup2");
			return 3;
		}
		printf("I am pushing these strings to file from printf function by changing FD of stdout with file FD\n");

		dup2(stdout_copy,1);//stdout position is resetted from previous copy.
	}
	if(option == 2){
		printf("this is getting printed on screen by stdout without any FD changes\n");
	}
}



