#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int fd1, fd2;
    fd1 = dup(1);
    if (fd1 == -1) {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    int fp1 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fp1 == -1) {
        if(errno == ENOENT) {
            fprintf(stderr, "File not found\n");
        } else if (errno == EACCES) {
            fprintf(stderr, "Permission denied\n");
        }
        else if(errno == EEXIST) {
            fprintf(stderr, "File already exists\n");
        } else if (errno == ENOSPC) {
            fprintf(stderr, "No space left on device\n");
        } else if (errno == EISDIR) {
            fprintf(stderr, "Is a directory\n");
        } else {
            fprintf(stderr, "Error opening file\n");
        }
        perror("open");
        exit(EXIT_FAILURE);
    }
   
    fd2 = dup2(fp1, 1);// redirect stdout to fp1, old stdout is fd1, new stdout is 1
    if (fd2 == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fp1);
    printf("Hello World\n");
    printf("This is a test\n");
    printf("This is a test\n");
    printf("This is a test\n");

}