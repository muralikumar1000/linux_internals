#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
  	int fd;
  	fd =  open(argv[1],O_RDONLY);
	if(fd == -1)
	{
	  perror("Open system call failed\n");
	  return 1;
	}
	printf("The value of file descriptor is %d\n",fd);

	return 0 ;

}
