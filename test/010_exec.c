#include <unistd.h>
#include<stdio.h>


int main()
{
		printf("Before exec pid of process is : %d\n",getpid());
		printf("Before exec Parent PID of Process is : %d\n",getppid());

		//ls command 
	//	execl("/bin/ls","ls", "-l",(char *)NULL);  //Absolute Path
//		execlp("ls","ls", "-l",(char *)NULL); 	  // Relative path

		char *const argv[] = {"ls","-l",(char *)NULL};
		//execv("/bin/ls",argv);
		execvp("ls",argv);

		printf("Hi exec() failed\n");

		return 0;

}

