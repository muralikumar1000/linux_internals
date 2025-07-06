/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Thu 12 May 2016 15:59:19 IST
 *   Title          : POSIX threads (pThread) - Race conditions 
 *   Description    : Threads are prone to race conditions due to shared data 
 *                    problem. Here is an example of global variable being the
 *                    reason for race condition. 
 *
 *----------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int counter;

void* thread_function(void *arg)
{
    while(1)
	{
			counter = 0;
		    counter += 5;	
		    counter += 10;	
			printf("%d\n",counter);
            sleep(1);
	}
    return NULL;
}

int main(void)
{
   //Variable declaration
   pthread_t thread_1,thread_2;
   //Creating thread1 and thread2
   pthread_create(&thread_1,NULL,thread_function,NULL);
   pthread_create(&thread_2,NULL,thread_function,NULL);
   //Waiting for thread completion
   pthread_join(thread_1,NULL);
   pthread_join(thread_2,NULL);

   return 0;
}
