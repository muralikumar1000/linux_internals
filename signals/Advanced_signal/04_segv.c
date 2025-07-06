/* FILE: sigint_sigaction.c
 * Description: 
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    printf("Signal number %d : ", signum);
    printf("Address is  %p\n", siginfo->si_addr);
	//exit(0);
	signal(SIGSEGV,SIG_DFL);

}

int main()
{
    struct sigaction newact;
	int *ptr = NULL;

    memset(&newact, 0, sizeof(newact)); //Clear memory

    newact.sa_sigaction = mysig_handler; //Assign your signal handler
    newact.sa_flags = SA_SIGINFO;
	
    /* Register the signal handler for SIGINT signal */
    sigaction(SIGSEGV, &newact, NULL);
	*ptr = 10;
	 pause();

    return 0;
}
