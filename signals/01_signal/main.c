
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
		printf("Pid of this process is  %d\n",getpid());
		while(1);
}
