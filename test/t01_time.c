
#include<stdio.h>
#include<time.h>

int main()
{
  time_t ret_val,my_time;
  //  time_t time(time_t *tloc)
 // ret_val = time(NULL);
  ret_val = time(&my_time);
  if(ret_val == -1)
  {
	printf("Time system call Failed\n");
	return 1;
  }
  printf("Time since Epoch :%ld\n",ret_val);
  printf("Time since Epoch :%ld\n",my_time);
}
