/*
1. Code to demonstrate signal handler repeatedly.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

void signal_handler(int);
int count = 0;
int main()
{
	puts("Type: Ctrl + c\n");
	signal(SIGINT, signal_handler);
	while(1);
	pause();
}

void signal_handler(int num)
{
	printf("SIGINT signal recieved %d times\n",count++);
	if(count == 6 )
		signal(SIGINT, SIG_DFL);
}

/*
1. Default task, when ctrl+c is pressed, the process will be termiated.
2. We are overriding the default task by redefining it.
3. In the function again calling the signal.
*/
