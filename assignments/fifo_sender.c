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

int main(){
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int cpid = fork();
    if(cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0) {
        // Child process
        close(pipefd[1]); // Close unused write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);

        // lower case to upper case conversion
        char *ptr = buffer;
        while (*ptr != '\0') {
            *ptr = toupper(*ptr);
            ptr++;
        }
        printf("Received: %s\n", buffer);

        // write to shared memory
        int shmid;
        char *shmaddr;
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
        strcpy(shmaddr, buffer);
        sleep(8); // sleep for 5 seconds
    } 
    else {
        // Parent process
        close(pipefd[0]); // Close unused read end
        const char *message = "Hello from parent!";
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);

        waitpid(cpid, NULL, 0);
        //open the FIFO for reading
        int fd = open("/tmp/fifo", O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        char buffer[100];
        // Read the reversed string from the FIFO
        if (read(fd, buffer, sizeof(buffer)) == -1) {
            perror("read");
            exit(1);
        }
        close(fd);
        printf("Received from FIFO: %s\n", buffer);
        
    }

}