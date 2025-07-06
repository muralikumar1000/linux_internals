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
    int i = 1, count = 0;
    // Count the number of pipes in the arguments
    while(argv[i]){
        if(strcmp(argv[i], "|") == 0) {
            count++;
        }
        i++;
    }
    int argv_index[count+1];
    i = 1;
    int j = 1;
    argv_index[0] = 1; // The first command starts at index 1
    // Store the post-pipe indeces in the argv_index array
    while(argv[i]) {
        if(strcmp(argv[i], "|") == 0) {
            argv_index[j++] = i+1;
            argv[i] = NULL; // Null-terminate the command at the pipe
        }
        i++;
    }

    // pipefd for storing the file descriptors for the n-count pipes
    int pipe_fd[count][2];
    

    for(int i = 0; i < count; i++) {
        if(pipe(pipe_fd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    pid_t cpid;
    // First child: "ls"
    for(int i = 0; i < count; i++) {
        cpid = fork();
        if (cpid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (cpid == 0) {
            dup2(pipe_fd[i][1], STDOUT_FILENO);
            close(pipe_fd[i][0]); // Close unused read end
            close(pipe_fd[i][1]); // Close duplicate write end
            for(int j = 0; j < count; j++) {
                if(j != i) {
                    close(pipe_fd[j][0]); // Close unused read ends
                    close(pipe_fd[j][1]); // Close unused write ends
                }
            }

        execvp(argv[argv_index[i]], &argv[argv_index[i]]);
        char buffer[256];
        sprintf(buffer,"child%d execvp", i);
        perror(buffer);
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
        exit(EXIT_FAILURE);
        }

        for(int i = 0; i < count; i++) {
            close(pipe_fd[i][1]); // Close write end in parent
            close(pipe_fd[i][0]); // Close read end in parent
        }

        int status;
        pid_t wpid;
        while ((wpid = wait(&status)) > 0) {
            if (WIFEXITED(status)) {
                printf("Child with PID %d exited with status %d\n",wpid, WEXITSTATUS(status));
            }
        }
            
    }
    
    
    
   return 0;
}
