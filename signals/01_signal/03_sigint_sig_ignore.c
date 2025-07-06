/*
1. Code to demonstrate signal handler.
2. SIG_IGN: To ignore the signal
*/

#include <stdio.h>
#include <signal.h>

//typedef void (*sighandler_t)(int);

void signal_handler(int);

int main()
{
	puts("Type: Ctrl + c");
	signal(SIGINT, signal_handler); // Register signal handler for SIGINT
	while(1);
}

void signal_handler(int num)
{
	puts("You have pressed: Ctrl+c");
	signal(SIGINT, SIG_IGN);
}

/*
1. Default task, when ctrl+c is pressed, the process will be termiated.
*/
