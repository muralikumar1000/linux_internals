
#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    printf("Signal number %d : ", signum);
	printf("Child process with PID %d terminated\n", siginfo->si_pid);
    // Optionally, you can also print the exit status of the child
    if (siginfo->si_code == CLD_EXITED) {
        printf("Child exited with status %d\n", siginfo->si_status);
    } else if (siginfo->si_code == CLD_KILLED) {
        printf("Child was killed\n");
    } else if (siginfo->si_code == CLD_DUMPED) {
        printf("Child dumped core\n");
    }
    else {
        printf("Child terminated for an unknown reason\n");
    }
    // No need to call waitpid here, as SA_NOCLDWAIT prevents zombies
}

int main()
{
    struct sigaction newact;
	sigset_t set;

    

    
	memset(&newact, 0, sizeof(newact)); //Clear memory

	newact.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    newact.sa_sigaction = mysig_handler; //Assign your signal handler

	

	printf("PID of the process is %d\n",getpid());

    /* Register the signal handler for SIGINT signal */
    sigaction(SIGCHLD, &newact, NULL);

	//sigprocmask(SIG_BLOCK, &set, NULL);

    int pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process with PID %d created\n", getpid());
        sleep(5); // Simulate some work in the child
        _exit(0); // Exit child process
    }
    // Parent process
    printf("Parent process with PID %d waiting for child to finish\n", getpid());
    pause(); // Wait for signals
    printf("Parent process exiting\n");
    fflush(stdout);



    return 0;
}
