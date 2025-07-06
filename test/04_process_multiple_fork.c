/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:15:45 IST
 *   File           : t007.c
 *   Title          : Creating multiple processes using fork()
 *   Description    : Using fork() multiple processes can be created by calling
 *                    the same system call in sequence. This is an example code
 *                    to demonstrate multiple child creation and build clear 
 *                    understanding of parent & child mechanism in Linux  
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
int main ()
{
	fork();
	fork();
	fork();
	printf("Hello World\n");
	return 0;
}
