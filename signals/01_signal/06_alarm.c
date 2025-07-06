/*
1. Code to demonstrate signal handler.
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void signal_handler(int);

int main()
{


	//Register the signal 
	signal(SIGALRM, signal_handler);
	alarm(4);	
    //alarm(1);
	for(int i = 1 ;i < 10 ; i++)
	{
			printf("%d Inside the main function \n",i);
			sleep(1);
	}
}

void signal_handler(int num)
{
	printf("Alarm has occured\n");
}

/*
1. Default task, when ctrl+c is pressed, the process will be termiated.
2. We are overriding the default task by redefining it.
3. Default action will be SIG_DFL.
*/
