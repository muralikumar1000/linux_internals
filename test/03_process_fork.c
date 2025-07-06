/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:03:15 IST
 *   File           : t006.c
 *   Title          : Creating a new process in Linux - fork()
 *   Description    : A running instance of a program is called as Process in 
 *                    any OS. In Linux to create a new process there are multiple
 *                    system calls are provided. fork() is one of them, which 
 *                    is demonstrated with an example below. 
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main ()
{
	printf("Fork Demonstration\n");
	fork();
	printf("Hello World\n");
	printf("PID = %d\n", getpid());
	return 0;
}
