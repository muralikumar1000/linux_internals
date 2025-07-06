#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void mysignal_handler(int signum)
{
    printf("Signal number %d received\n", signum);
    int status;
    pid_t pid;

    // Reap the child (handle multiple if needed)
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child %d killed by signal %d\n", pid, WTERMSIG(status));
        }
    }
}

int main(){

    signal(SIGCHLD, mysignal_handler);
    printf("PID of the process is %d\n", getpid());
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
    pause(); // Wait for a signal
    printf("Parent process with PID %d received signal from child\n", getpid());
}