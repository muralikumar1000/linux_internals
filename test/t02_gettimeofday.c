#include<stdio.h>
#include <sys/time.h>

int main()
{
	int ret_val;
	struct timeval my_time;
   // int gettimeofday(struct timeval *tv, struct timezone *tz)
	ret_val = gettimeofday(&my_time , NULL);
	if(ret_val == -1)
	{
	  	perror("Error \n");
		return 1;
	}
	printf("Time in seconds since epoch %ld\n",my_time.tv_sec);
	printf("Time in micro seconds since epoch %ld\n",my_time.tv_usec);

	//To convert the time from sec to hours ,minutes
	//localtime()

	return 0 ;
}
