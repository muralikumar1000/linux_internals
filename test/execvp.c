#include<stdio.h>
#include <unistd.h>

int main()
{
		printf("Hello\n");
		printf("Before exec PId of the process is %d\n",getpid());
		printf("Before exec Parent  PId of the process is %d\n",getppid());


		char *const argv[] = {"ls","-l",(char *)NULL};
		//execute ls 
		execvp("ls",argv);

		printf("The exec function failed\n");
}

