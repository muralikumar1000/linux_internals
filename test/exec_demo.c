#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
		printf("After exec\n");
		printf("The pid of this process is %d\n",getpid());
		printf("The pid of the Parent  process is %d\n",getppid());
		return 0;
}
