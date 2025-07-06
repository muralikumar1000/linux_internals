/* FILE: sigint_sigaction.c
 * Description: 
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static int sigcnt;

void mysig_handler(int signum)
{
		printf("Got signal %d\n", signum);
		sigcnt++;
}

int main()
{

		//Variable Declaration
		struct sigaction newact;

		memset(&newact, 0, sizeof(newact)); //Clear memory

		newact.sa_handler = mysig_handler; //Assign your signal handler

		/* Register the signal handler for SIGINT signal */
		sigaction(SIGINT, &newact, NULL);

	while(1)
		{
				printf("Sigint count is %d\n", sigcnt);
				pause();
		}
		
		return 0;
}
