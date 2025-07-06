/*
1. Code to demonstrate signal handler.
*/

#include <stdio.h>
#include <signal.h>


void signal_handler(int);

int main()
{
	
	printf("Type: Ctrl + c\n");
	//Register the signal 
	signal(SIGINT, signal_handler);

	while(1);
}

void signal_handler(int num)
{
	printf("num:%d\n", num);
	printf("You have pressed: Ctrl+c\n");
	signal(SIGINT, SIG_DFL);
}

/*
1. Default task, when ctrl+c is pressed, the process will be termiated.
2. We are overriding the default task by redefining it.
3. Default action will be SIG_DFL.
*/
