/* FILE: sigint_sigaction.c
 * Description: 
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    printf("Signal number %d : ", signum);
	int i = 20;
	while(i > 0)
	{
		printf("I am in the handler %d\n",i);			
		sleep(1);
		i--;
	}
}

int main()
{
    struct sigaction newact;
	sigset_t set;

    

    
	memset(&newact, 0, sizeof(newact)); //Clear memory

	newact.sa_flags = SA_SIGINFO;
    newact.sa_sigaction = mysig_handler; //Assign your signal handler

	//Intialize the signal set
	sigemptyset(&set);

	//Add the signal 
	sigaddset(&set,SIGTERM);
	//sigfillset(&set);

	//newact.sa_mask= set;

	printf("PID of the process is %d\n",getpid());

    /* Register the signal handler for SIGINT signal */
    sigaction(SIGINT, &newact, NULL);
	sigprocmask(SIG_BLOCK, &set, NULL);

    while(1);

    return 0;
}
