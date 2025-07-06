#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Error: No arguments passed\nUsage: %s <command 1> | <command 2> | <command 3>\n", argv[0]);
        return 1;
    }
    int pipe_index = -1, pipe_index2 = -1;

    // Find the index of the '|'
    int i = 0;
    for (i; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_index = i++;
            break;
        }
    }
    for (i; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_index2 = i;
            break;
        }
    }

    if (pipe_index == -1 || pipe_index2 == -1) {
        fprintf(stderr,"Error: Insufficient arguments\nUsage: ./pipe <command 1> | <command 2> | <command 3>\n");
        return 1;
    }
    // Split the argv
    argv[pipe_index] = NULL;  // null-terminate the first part
    char **right_argv = &argv[pipe_index + 1]; // argv[pipe_index + 1] points to the first command of middle part

    char **last_argv;
    if(pipe_index2 != -1) {
        argv[pipe_index2] = NULL;  // null-terminate the middle part
        last_argv = &argv[pipe_index2 + 1]; // argv[pipe_index2 + 1] points to the first command of last part
    }
    
    int pipefd1[2], pipefd2[2];
    pid_t cpid1, cpid2, cpid3;

    if (pipe(pipefd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child: "ls"
    cpid1 = fork();
    if (cpid1 == 0) {
        // Redirect stdout to pipe's write end
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[0]); // Close unused read end
        close(pipefd1[1]); // Close duplicate write end

        close(pipefd2[0]); // Close unused read end
        close(pipefd2[1]); // Close unused write end

        execvp(argv[1], &argv[1]);
        perror("child1 execvp");
        exit(EXIT_FAILURE);
    }else if (cpid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    cpid2 = fork();

    // Second child: "wc"   
    if (cpid2 == 0) {
        // Redirect stdin to pipe's read end
        dup2(pipefd1[0], STDIN_FILENO);
        close(pipefd1[1]); // Close unused write end
        close(pipefd1[0]); // Close duplicate read end

        dup2(pipefd2[1], STDOUT_FILENO); // Redirect stdout to second pipe's write end
        close(pipefd2[0]); // Close unused read end
        close(pipefd2[1]); // Close duplicate write end

        execvp(right_argv[0], right_argv);
        perror("child2 execvp");
        if(errno == ENOENT) {
            fprintf(stderr, "Error: Command not found\n");
        } else if(errno == EACCES) {
            fprintf(stderr, "Error: Permission denied\n");
        }
        else if(errno == ENOTDIR) {
            fprintf(stderr, "Error: Not a directory\n");
        }
        else if(errno == ELOOP) {
            fprintf(stderr, "Error: Too many symbolic links\n");
        }
        else if(errno == ENAMETOOLONG) {
            fprintf(stderr, "Error: File name too long\n");
        }
        else if(errno == ENOTEMPTY) {
            fprintf(stderr, "Error: Directory not empty\n");
        }
        else if(errno == EEXIST) {
            fprintf(stderr, "Error: File exists\n");
        }
        else if(errno == EISDIR) {
            fprintf(stderr, "Error: Is a directory\n");
        }
        else if(errno == ENOSPC) {
            fprintf(stderr, "Error: No space left on device\n");
        }
        else if(errno == EROFS) {
            fprintf(stderr, "Error: Read-only file system\n");
        }
        else if(errno == ENOTBLK) {
            fprintf(stderr, "Error: Block device required\n");
        }
        else if(errno == EFAULT) {
            fprintf(stderr, "Error: Bad address\n");
        }
        else if(errno == EINVAL) {
            fprintf(stderr, "Error: Invalid argument\n");
        }
        else if(errno == ENFILE) {
            fprintf(stderr, "Error: Too many open files in system\n");
        }
        //perror("child2 execvp");
        exit(EXIT_FAILURE);

        
    }
    else if (cpid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    cpid3 = fork();
    // Third child: "sort"

    if(cpid3 == 0) {
        // Redirect stdin to pipe's read end
        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[1]); // Close unused write end
        close(pipefd2[0]); // Close duplicate read end

        close(pipefd1[0]); // Close unused read end
        close(pipefd1[1]); // Close unused write end

        execvp(last_argv[0], last_argv);
        perror("child3 execvp");
        exit(EXIT_FAILURE);
    }else if (cpid3 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Close all pipe ends in the parent
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);
    // Wait for all children to finish
    waitpid(cpid1, NULL, 0);
    waitpid(cpid2, NULL, 0);
    waitpid(cpid3, NULL, 0);
    
   return 0;
}
