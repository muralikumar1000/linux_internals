/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:18:10 IST
 *   File           : t014.c
 *   Title          : IPC mechanism - Usage of FIFO (Named pipe) - Receiver
 *   Description    : IPC mechanisms provide various ways and means to share 
 *                    information between multiple processes. FIFO is one of the 
 *                    simplest and effective way to establish IPC. Here is an
 *                    example of FIFO (receiver).
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

#define FIFO_NAME "/tmp/myfifo"
#define MAX_STRING_LEN 80

int main()
{
	int fd, pp;
	//Open the file in read mode
	fd = open(FIFO_NAME, O_RDONLY);
	if (fd < 0)
	{
		perror("Open");
		exit(1);
	}
	else
	{
		/* As a unrelated process read from the FIFO and print */
		read(fd,&pp,sizeof(pp));
		printf("FIFO message received: %d\n",pp);
		read(fd,&pp,sizeof(pp));
		printf("FIFO message received: %d\n",pp);
		close(fd);
		exit(0);
	}
}
