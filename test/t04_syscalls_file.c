/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 16 Feb 2016 16:49:51 IST
 *   File           : t004.c
 *   Title          : System calls usage in Linux - File operations
 *   Description    : System calls in Linux provide unified access to resources
 *                    that Kernel is managing. This is second level program 
 *                    for performing file operations using system calls. Using 
 *                    this example, developers can also understand Virtual File
 *                    System (VFS) in Linux.  
 *
 *----------------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 10

int main(int argc, char **argv)
{
	/* For storing file discriptor */
	int source_fd;
	int rd_ret, wt_ret;
	/* Buffer to store read values */
	char buff[10];

	/* Open file in read-only mode */
	source_fd = open(argv[1], O_RDONLY);
	/* Checks for error */
	if (source_fd == -1)
	{
		perror("open");
		return (1);
	}
	do {
		/* reading MAX bytes from file */
		rd_ret = read(source_fd, buff, MAX);
		/* Checks for error */
		if (rd_ret == -1)
		{
			perror("read");
			return 2;
		}

		/* writing to stdout */
		wt_ret = write(1, buff, rd_ret);
		/* Checks for error */
		if (wt_ret == -1)
		{
			perror("write");
			return 3;
		}
		/* Loops till end-of-files */
	}while(rd_ret != 0);

	close(source_fd);
}
