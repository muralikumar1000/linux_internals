#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
           pid_t cpid, w;
           int wstatus;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %ld\n", (long) getpid());
               sleep(5); /* Sleep for 5 seconds */

           } else {                    /* Code executed by parent */
               do {
                    printf("Parent PID is %ld\n", (long) getpid());
                   printf("Waiting for child PID %ld\n", (long) cpid);
                   w = waitpid(cpid, &wstatus, WNOHANG);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d, w = %d\n", WEXITSTATUS(wstatus), w);
                   }
                   usleep(500); // Sleep for 0.5 seconds
               } while (w == 0);
               printf("%d",w);
               exit(EXIT_SUCCESS);
           }
       }