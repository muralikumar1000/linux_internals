/* FILE: fork.c 
 * Description: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    // Create a child process using fork()
    pid = fork();
	//execl("/bin/ls","ls","-l", NULL);

    switch(pid)
    {
	case -1: // fork returned -1 (failed)
	    perror("fork");
	    exit(1);
	case 0: //child, fork returns 0
	    printf("I am child\n");
	    printf("Child PID = %d\n", getpid()); // Executed by child
	    break;
	default: // parent, pid -> child pid
	    printf("I am parent\n");
	    printf("Parent PID = %d\n", getpid()); // Executed by parent
	    printf(" PID of child process = %d\n",pid ); // Executed by parent
    }

    printf("Done for the day\n");

    return 0;
}
