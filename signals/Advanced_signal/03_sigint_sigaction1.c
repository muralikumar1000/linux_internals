/* FILE: sigint_sigaction.c
 * Description: 
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static int sigcnt;

void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    printf("Signal number %d : ", signum);
    printf("Signal sent by %d\n", (int)siginfo->si_pid);
    sigcnt++;
}

int main()
{
    struct sigaction newact;

    memset(&newact, 0, sizeof(newact)); //Clear memory

    newact.sa_sigaction = mysig_handler; //Assign your signal handler
    newact.sa_flags = SA_SIGINFO;
	
    /* Register the signal handler for SIGINT signal */
    sigaction(SIGINT, &newact, NULL);

    while(1)
    {
		printf("Sigint count is %d\n", sigcnt);
		sleep(1);
    }

    return 0;
}
