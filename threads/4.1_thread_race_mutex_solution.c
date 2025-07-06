/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Thu 12 May 2016 15:59:19 IST
 *   File           : t030.c
 *   Title          : POSIX threads (pThread) - Mutex usage for race conditions 
 *   Description    : Threads are prone to race conditions due to shared data 
 *                    problem. One of the way race conditions can be avoided 
 *                    by using mutex by protecting shared data, as shown below.
 *
 *----------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>



//Declare a lock variable
pthread_mutex_t lock;

int counter;

void* thread_function(void *arg)
{

		while(1)
		{
				//acquire the lock before entering CS
				pthread_mutex_lock(&lock);
				printf("locked by %ld->",pthread_self());
				counter = 0;
				counter += 5;	
				counter += 10;	
				printf("->%d\n",counter);
				//Unlock so that other threads can access CS
				printf("unlocked by %ld->",pthread_self());
				pthread_mutex_unlock(&lock);
		}

		return NULL;
}

int main(void)
{
		//Variable declaration
		pthread_t thread_1,thread_2;

		//Initialize the lock 
		if (pthread_mutex_init(&lock, NULL) != 0)
		{
				printf("\nPthread: mutex init failed\n");
				return 1;
		}	
		//Create the thread
		pthread_create(&thread_1,NULL,thread_function,NULL);
		pthread_create(&thread_2,NULL,thread_function,NULL);
		//Wait for thread completion
		pthread_join(thread_1,NULL);
		pthread_join(thread_2,NULL);
		
		//Destroy 
		pthread_mutex_destroy(&lock);
		return 0;
}
