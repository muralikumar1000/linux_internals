#include "main.h"
extern int exit_status; // Declare exit_status as an external variable

void extract_external_commands(char *input) {
    char *argv[MAX_ARGS];                 // Null-terminated array
{
    int argc = 0;

    char *token = strtok(input, " ");
    while (token != NULL && argc < MAX_ARGS - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;  // Null-terminate it
}

    // Now argv contains the command and its arguments
    int ret = fork();
    if (ret < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (ret == 0) {
        // Child process
        if (execvp(argv[0], argv) < 0) {
            perror("execvp failed");
            exit(EXIT_FAILURE); 
        }
    }
    else {
        // Parent process
        int status;
        waitpid(ret, &status, WUNTRACED); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n",ret,(exit_status = WEXITSTATUS(status)));
        } else if(WIFSIGNALED(status)){
           exit_status = WTERMSIG(status);
           printf("Child %d terminated by signal %d\n", ret, exit_status);
           exit_status += 128; // Convert signal to exit status
        }
        else if(WIFSTOPPED(status)){
            exit_status = WSTOPSIG(status);
            printf("Child %d stopped by signal %d\n", ret, exit_status);
            exit_status += 128; // Convert signal to exit status
        }
    }
}