#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
           pid_t cpid1, cpid2, cpid3, w[3];
           int wstatus;

           pid_t pids[3];

           cpid1 = fork();
           if (cpid1 == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid1 == 0) {            /* Code executed by child */
               printf("Child0 PID is %ld, created\n", (long) getpid());
               
               sleep(3); /* Sleep for 1 seconds */

           } else {                /* Code executed by parent */
                cpid2 = fork();
                if (cpid2 == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                if (cpid2 == 0) {            /* Code executed by child */
                    printf("Child1 PID is %ld, created\n", (long) getpid());
                    
                    sleep(2); /* Sleep for 2 seconds */

                } else {                /* Code executed by parent */
                        cpid3 = fork();
                        if (cpid3 == -1) {
                            perror("fork");
                            exit(EXIT_FAILURE);
                        }
                        if (cpid3 == 0) {            /* Code executed by child */
                            printf("Child2 PID is %ld, created\n", (long) getpid());
                            
                            sleep(1); /* Sleep for 3 seconds */

                        } else {                /* Code executed by parent */
                            pids[0] = cpid1;
                            pids[2] = cpid3;
                            pids[1] = cpid2;
                do {
                        for(int i = 0; i < 3; i++) {
                            w[i] = waitpid(pids[i], &wstatus, WNOHANG);
                            if (w[i] == -1) {
                                perror("waitpid");
                                exit(EXIT_FAILURE);
                            }
                            if (WIFEXITED(wstatus)) {
                                printf("child%d exited, status=%d\n",i, WEXITSTATUS(wstatus));
                            }
                        }
                } while (w[0] == 0 || w[1] == 0 || w[2] == 0);
                exit(EXIT_SUCCESS);
            }
           }
        }
    }