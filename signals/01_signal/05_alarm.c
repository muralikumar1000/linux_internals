/*
1. Code to demonstrate signal handler.
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void signal_handler(int);

int main()
{

	alarm(5);	
	//Register the signal 
	signal(SIGALRM, signal_handler);

	while(1);
}

void signal_handler(int num)
{
	printf("Alarm has occured\n");
	alarm(3);
	//signal(SIGALRM, SIG_DFL);
}

/*
1. Default task, when ctrl+c is pressed, the process will be termiated.
2. We are overriding the default task by redefining it.
3. Default action will be SIG_DFL.
*/
