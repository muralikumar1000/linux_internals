/* FILE: simple_thread.c 
 * Description: 
 */

#include <stdio.h>
#include <pthread.h>

void *print_x(void *data)
{
    while(1)
	fputc('X', stderr);
}

void *print_o(void *data)
{
    while(1)
	fputc('O', stderr);
}

int main()
{
    pthread_t tid1, tid2; //Thread IDs

    //Create thread 1. Thread 1 will execute print_x func
    pthread_create(&tid1, NULL, print_x, NULL);

    //Create thread 2. Thread 2 will execute print_o func
    pthread_create(&tid2, NULL, print_o, NULL);

    //Wait for thread 1 to complete using pthread_join
    pthread_join(tid1, NULL);
    //Wait for thread 2 to complete using pthread_join
    pthread_join(tid2, NULL);

    return 0;
}
