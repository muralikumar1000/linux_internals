#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    printf("Segmentation fault....!\n");
    printf("Address  0x%p caused error\n", siginfo->si_addr);
    //exit(0);
    signal(SIGSEGV,SIG_DFL);

}

int main(){
    struct sigaction newact;
    int *ptrr = NULL;

    memset(&newact, 0, sizeof(newact)); //Clear memory

    newact.sa_sigaction = mysig_handler; //Assign your signal handler
    newact.sa_flags = SA_SIGINFO;

    /* Register the signal handler for SIGINT signal */
    sigaction(SIGSEGV, &newact, NULL);

    *ptrr = 10;//oops

    //char arr[5];
    //arr[10] = 'X';  // Oops.

    /*char *ptr = malloc(10);
    free(ptr);
    ptr[0] = 'Z';*/  // Might trigger a fault


     pause();

    return 0;
}