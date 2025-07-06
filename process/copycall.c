/*
<<doc
Name: Murali venkata vijay kumar
Date:
Description:
Sample i/p:
Sample o/p:
doc
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



#define MAX 20

int file_copy(int , char **);
int change_mode(int, char **);

int src_fd;
int dst_fd;

int main(int argc, char *argv[]){


/* if less arguments given*/
	if(argc <= 2){
		printf("%s insufficient arguments\n",argv[0]);
		printf("Usage:- %s [option]\n",argv[0]);
		printf("%d",argc);
		return 0;

	}

	/* if 3 arguments present < ./a.out source destination > */
	else if(argc == 3 ){
		file_copy(argc, argv);
	}
	/* if 4 arguments present < ./a.out source destination -p > */
	else if(argc == 4){
		change_mode(argc, argv);

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////


int file_copy(int argc, char *argv[]){

		/*source file opening*/
		src_fd = open(argv[1],O_RDONLY);
		if(src_fd == -1){
			perror("source open failed");
		   return 1;
		}
		////////////////////////////

		char option ;

		/* ckecking if destination file is present */
		dst_fd = open(argv[2], O_EXCL | O_CREAT | O_WRONLY ,0666);

		if(errno == EEXIST){
			printf("%s file already exists, do you want to override y/n\n", argv[2]);
			scanf("%c",&option);
				
		}
			if(option == 'n' || option == 'N'){
				printf("overwrite cancelled\n");
				return 0;
			}

			else if(option == 'y' || option == 'Y'){
				printf("overwrite accepted");
				close(dst_fd);
				dst_fd = open(argv[2], O_WRONLY);

			}
			else{
				printf("overwrite cancelled\n");
				return 0;
			}
		
		if(dst_fd == -1){
			perror("destination open failed");
			return 2;
		}

		//////////////////////////

		///////////////////////////
		char buff[MAX];


		ssize_t rd_ret, wt_ret;

		/*************************************************************************************/
		do {
			/* reading MAX bytes from file */
			rd_ret = read(src_fd, buff, MAX);

			/* Checks for error */
			if (rd_ret == -1)
			{
				perror("read");
				return 3;
			}
			//buff[rd_ret] = '\0'; 

			/* writing to stdout */
			wt_ret = write(dst_fd, buff, rd_ret);
			/* Checks for error */
			if (wt_ret == -1)
			{
				perror("write");
				return 4;
			}

			/* Loops till end-of-files */
		}while(rd_ret != 0);

		/*if 4 arguments are there, this will return to its calling function to change file permissions*/
		if(argc == 4){
			return 5;
		}

		close(src_fd);
		close(dst_fd);
}
////////////////////////////////////////////////////////////////////////////////////////////////


int change_mode(int argc, char *argv[]){
		if((strcmp(argv[3], "-p")) == 0){

			/* if argument 4 matches */
			file_copy(argc,argv);

			struct stat status;
			
			/* source file mode status is retrived*/
			fstat(src_fd, &status);

			/* destination mode is changed to sources equivelent mode*/
			int fmod = fchmod(dst_fd, status.st_mode);
			if(fmod == -1){
				perror("fchmod");
				return 6;
			}
		close(src_fd);
		close(dst_fd);
		}
}
