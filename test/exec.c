#include<stdio.h>
#include <unistd.h>

int main()
{
		printf("Hello\n");
		printf("Before exec PId of the process is %d\n",getpid());
		printf("Before exec Parent  PId of the process is %d\n",getppid());

		//execute ls 
		execl("/bin/ls","ls","-l",(char *)NULL);
	//	execlp("exec_demo","exec_demo",(char *)NULL);
		printf("The exec function failed\n");
}

