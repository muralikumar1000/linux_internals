/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:18:10 IST
 *   File           : t014.c
 *   Title          : IPC mechanism - Usage of FIFO (Named pipe) - Sender 
 *   Description    : IPC mechanisms provide various ways and means to share 
 *                    information between multiple processes. FIFO is one of the 
 *                    simplest and effective way to establish IPC. Here is an
 *                    example of FIFO (sender).
 *
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#define FIFO_NAME "/tmp/myfifo"
#define MAX_STRING_LEN 80

int main()
{
	int fd, pp;

	/* Create a pipe */
	//mknod(FIFO_NAME, S_IFIFO| 0666, 0);
	mkfifo(FIFO_NAME, 0666);
	if(errno == EEXIST)
	{
		printf("FIFO already exists\n");
	}
	else if(errno != 0)
	{
		perror("FIFO creation failed");
		exit(1);
	}
	else
	{
		printf("FIFO created successfully\n");
	}
	

	//Open the file in writemod
	fd = open(FIFO_NAME, O_WRONLY);
	if (fd < 0)
	{
		perror("Open");
		exit(1);
	}
	else
	{
		/* Send some hard coded value between two processes who are not related */
		pp = 100;
		write(fd,&pp,sizeof(pp));
		pp = 200;
		write(fd,&pp,sizeof(pp));
		printf("Value sent to FIFO\n");
		close(fd);
		exit(0);
	}
}
