#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main(){
    int shmid;
    char *shmaddr;
    char *message = "Hello, World!";
    int size = 1024;
    key_t key = 1234;

    // Create a shared memory segment
    sleep(1); // sleep for 2 seconds
    shmid = shmget(key, size, 0666);
    if (shmid < 0) {
        perror("reader shmget");
        exit(1);
    }
    // Attach the shared memory segment
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    char start = 0;
    char end = strlen(shmaddr)-1;
    printf("Reading from reader: %s\n", shmaddr);
    while(start < end){
        char temp = shmaddr[start];
        shmaddr[start] = shmaddr[end];
        shmaddr[end] = temp;
        start++;
        end--;
    }
    printf("Reversed string: %s\n", shmaddr);
    // Detach the shared memory segment

    if (shmdt(shmaddr) < 0) {
        perror("shmdt");
        exit(1);
    }


}