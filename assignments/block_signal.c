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
	int i = 40;
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

	//Intialize the signal set to empty
	sigemptyset(&set);

	//Add the signal to ignore
    //sigaddset(&set,SIGINT);
    //sigaddset(&set,SIGQUIT);
    //sigaddset(&set,SIGKILL);
    //sigaddset(&set,SIGSTOP);
    //sigaddset(&set,SIGTSTP);
    //sigaddset(&set,SIGCONT);
    //sigaddset(&set,SIGUSR1);
    //sigaddset(&set,SIGUSR2);
	//sigaddset(&set,SIGTERM);
    //sigaddset(&set,SIGABRT);

    // Fill the signal set with all signals
	sigfillset(&set);

    // Remove specific signals from the set so thery are not blocked
    sigdelset(&set, SIGINT); // Remove SIGINT from the set
    sigdelset(&set, SIGTERM); // Remove SIGTERM from the set

    //mask the signals in the set
    //newact.sa_mask = set; // This will block all signals in the set during the execution of the handler
	newact.sa_mask= set;

	printf("PID of the process is %d\n",getpid());

    /* Register the signal handler for SIGINT signal */
    sigaction(SIGINT, &newact, NULL);
	//sigprocmask(SIG_BLOCK, &set, NULL);

    while(1);

    return 0;
}
