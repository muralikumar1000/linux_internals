#include<stdio.h>
#include <unistd.h>

int main()
{
		printf("Hello\n");
		printf("Before exec PId of the process is %d\n",getpid());
		printf("Before exec Parent  PId of the process is %d\n",getppid());

		//execute ls 
		execlp("ls","ls","-l",(char *)NULL);
		printf("The exec function failed\n");
}

