/*
1. PIPES: Drawbacks
	- Pipes are used for communication between Parent & Child OR Between two processes which are related to each other.
	- Pipes are not PERMANENT, termination of the process leads to destruction of the PIPE.
2. To overcome the above drawbacks, FIFO or Named PIPES are used.
3. FIFO is nothing but regular file.
4. Named PIPE can be created using the command mknod.
	- mknod myfifo p
		- mknod: Command
		- myfifo: Named pipe
		- p: PIPE
	- This command only creates the FIFO, will not open it.	
5. cat < myfifo &
	- cat is trying to read from the file called myfifo, but the file is EMPTY.
	- cat waits, until another process writes something to it.
	- FIFO will be opened only when the other process writes to it.
6. ls -l > myfifo, As soon as ls writes the output to the FIFO, the cat who is waiting will read and print the output.
7. Do, point-6 and point-7 in separate terminals.
*/

/*
Description:
	- This is the reciever program, keeps waiting in the loop to read the message send by the sender.
	- This program creates the FIFO using mknod system call.
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define my_fifo1  "/tmp/p0"

int main()
{
	int fd;
	char buffer[6];
	int count;	

	//Open the file
	if ((fd = open(my_fifo1, O_RDWR)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	
	read(fd,buffer,6);
	printf("Message is %s\n",buffer);
}

/*
1. mknod(1, 2, 3),
	1:	Name of the FIFO
	2:	644 - Represents the permission
	3:	0	- Indicates special device, block / character device	
*/



