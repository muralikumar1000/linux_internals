/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:00:04 IST
 *   File           : t005.c
 *   Title          : Creating a new process in Linux - System 
 *   Description    : A running instance of a program is called as Process in 
 *                    any OS. In Linux to create a new process there are multiple
 *                    system calls are provided. System() is one of them, which 
 *                    is demonstrated with an example below. 
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


int main()
{
	printf("Running gedit with system\n");
	/* TODO try other commands like ps, sleep, top rtc and observe the behaviour */
	system("gedit");
	printf("Done.\n");
	exit(0);
}
