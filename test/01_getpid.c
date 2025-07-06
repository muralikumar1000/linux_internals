#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
		printf("Hello\n");
		printf("Pid of the process is %d\n",getpid());
		printf("Parent Pid of the process is %d\n",getppid());
		
		return 0;
}
