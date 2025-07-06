#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
		pid_t pid;

		// Create a child process using fork()
		pid = fork();

		if(pid > 0) // parent, pid -> child pid
		{
				printf("I am parent\n");
				printf("Parent PID = %d\n", getpid()); // Executed by parent
				sleep(20);
				printf("Parent died\n");
		}
		//child, fork returns 0
		else if(pid == 0)
		{
				printf("I am child\n");
				printf("Child PID = %d\n", getpid()); // Executed by child
				sleep(10);
				printf("Child died\n");
		}
		else // fork returned -1 (failed)
		{
				perror("fork");
				exit(1);
		}

		return 0;
}

//Type ps aux | grep 'z'  in another terminal after the child dies---> to see the zombie process
