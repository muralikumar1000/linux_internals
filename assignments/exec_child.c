#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Error : Please Pass the Command through CL\nUsage: %s <command> [args...]\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        printf("This is the CHILD process, with id %d\n", getpid());
        execvp(argv[1], &argv[1]);

        perror("execvp");
        exit(1);
    }
    else{
        while(1){
            int status;
            pid_t wpid = waitpid(pid, &status, WNOHANG);
            if(wpid == -1){
                perror("waitpid");
                return 1;
            }
            if(wpid == 0){
                //printf("This is the PARENT process, with id %d\n", getpid());
                sleep(1);
            }
            else{
                if(WIFEXITED(status)){
                    printf("Child process exited with status %d\n", WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child process killed by signal %d\n", WTERMSIG(status));
                }
                else if(WIFSTOPPED(status)){
                    printf("Child process stopped by signal %d\n", WSTOPSIG(status));
                }
                else if(WIFCONTINUED(status)){
                    printf("Child process continued\n");
                }
                else if(WIFSTOPPED(status)){
                    printf("Child process stopped\n");
                }
                break;
            }
        }

    }
}