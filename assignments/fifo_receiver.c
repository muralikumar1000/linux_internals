#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main(){
    int shmid;
    char *shmaddr;
    char buffer[100];
    key_t key = 1234;
    size_t size = 1024;
    shmid = shmget(key, size,0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    char start = 0;
    char end = strlen(shmaddr)-1;
    
    while(start < end){
        char temp = shmaddr[start];
        shmaddr[start] = shmaddr[end];
        shmaddr[end] = temp;
        start++;
        end--;
    }
    printf("Reversed string: %s\n", shmaddr);

    mkfifo("/tmp/fifo", 0666);
    if(errno != 0) {
        perror("mkfifo");
        exit(1);
    }
    int fd = open("/tmp/fifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    // Write the reversed string to the FIFO
    if (write(fd, shmaddr, strlen(shmaddr)) == -1) {
        perror("write");
        exit(1);
    }
    close(fd);
    // Detach the shared memory segment
    if (shmdt(shmaddr) < 0) {
        perror("shmdt");
        exit(1);
    }

}