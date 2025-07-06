#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

int main(){
    int shmid;
    char *shmaddr;
    char buffer[] = "hello";
    key_t key = 1234;
    size_t size = 1024;

    shmid = shmget(key, size, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    //printf("enter the message to write to shared memory: ");
    //fgets(buffer, sizeof(buffer), stdin);

    //buffer[strcspn(buffer, "\n")] = '\0'; // replace newline character
    // to uppercase
    char *ptr = buffer;
    while (*ptr != '\0') {
        *ptr = toupper(*ptr);
        ptr++;
    }
    // write to shared memory
    strcpy(shmaddr, buffer); 
    sleep(8); // sleep for 5 seconds
    // read from shared memory
    printf("Reading from shared memory: %s\n", shmaddr);   

    if (shmdt(shmaddr) < 0) {
        perror("shmdt");
        exit(1);
    }
    /*if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("shmctl");
        exit(1);
    }*/
    //printf("Shared memory removed\n");
    return 0;

}