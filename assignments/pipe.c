#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Error: No arguments passed\nUsage: %s <command 1> | <command 2>\n", argv[0]);
        return 1;
    }
    int pipe_index = -1;

    // Find the index of the '|'
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index == -1) {
        fprintf(stderr,"Error: Insufficient arguments\nUsage: ./pipe <command 1> | <command 2>\n");
        return 1;
    }
    // Split the argv
    argv[pipe_index] = NULL;  // null-terminate the left part

    char **left_argv = argv;
    char **right_argv = &argv[pipe_index + 1];
    
    int pipefd[2];
    pid_t cpid1, cpid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child: "ls"
    cpid1 = fork();
    if (cpid1 == 0) {
        // Redirect stdout to pipe's write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]); // Close unused read end
        close(pipefd[1]); // Close duplicate write end

        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Second child: "wc"
    cpid2 = fork();
    if (cpid2 == 0) {
        // Redirect stdin to pipe's read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]); // Close unused write end
        close(pipefd[0]); // Close duplicate read end

        execvp(right_argv[0], right_argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Parent: close both ends and wait for children
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(cpid1, NULL, 0);
    waitpid(cpid2, NULL, 0);

    return 0;
}
