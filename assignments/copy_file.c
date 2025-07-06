#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


extern int optind;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    int fd1, fd2;
    int opt, flag = 0;

    while((opt = getopt(argc, argv, "p")) != -1) {
        switch(opt) {
            case 'p':
                flag = 1;
                break;
        }
    }
    if(flag){
        fd1 = open(argv[optind], O_RDONLY);
        if (fd1 < 0) {
            perror("Error opening source file in while loop\n");
            return 1;
        }
        //printf("opening file with option\n");
        if (stat(argv[optind++], &file_stat) == -1) {
            perror("Error getting file status");
            return 1;
        }
        fd2 = open(argv[optind],O_WRONLY|O_CREAT |O_EXCL, file_stat.st_mode);
    }
    
    if(argc == 3) {
        fd1 = open(argv[1], O_RDONLY);
        if (fd1 < 0) {
            perror("Error opening source file");
            return 1;
        }
        //printf("opening file without option\n");
        fd2 = open(argv[2], O_WRONLY | O_CREAT |O_EXCL, 0666);
    }
   
    if (fd2 < 0) {
        if(errno == EEXIST) {
            fprintf(stderr, "Error: Destination file already exists\n");
            char choice;
            printf("Do you want to overwrite it? ('y' for yes, 'n' for no): ");
            close(fd2);
            scanf("%c", &choice);
            if( (choice == 'y') && (argc == 3) ){
                fd2 = open(argv[2], O_WRONLY | O_TRUNC);
                if (fd2 < 0) {
                    perror("Error opening destination file");
                    close(fd1);
                    return 1;
                }
                //printf("festination file opened without option\n");
            } else if (choice == 'y' && argc == 4) {
                fd2 = open(argv[optind],O_WRONLY | O_TRUNC, file_stat.st_mode);
                if (fd2 < 0) {
                    perror("Error opening destination file");
                    close(fd1);
                    return 1;
                }
                //printf("festination file opened with option\n");
            } else {
                fprintf(stderr, "Error: Destination file already exists and user chose not to overwrite\n");
                //printf("%d",argc);
                close(fd1);
                return 0;
            }
        }   
    }
    char buffer[1024];
    ssize_t size;
    while((size = read(fd1, buffer, sizeof(buffer))) > 0) {
        if (write(fd2, buffer, size) == -1) {
            perror("Error writing to destination file");
            close(fd1);
            close(fd2);
            return 1;
        }
    }
    if (close(fd1) == -1) {
        perror("Error closing source file");
        return 1;
    }
    if (close(fd2) == -1) {
        perror("Error closing destination file");
        return 1;
    }
    printf("File copied successfully\n");
    return 0;


    

}