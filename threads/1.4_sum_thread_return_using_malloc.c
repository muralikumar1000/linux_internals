/* FILE: sum_thread_return_using_malloc.c
 * Description: 
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct
{
    int num1, num2;
} sumdata_t;

void *sum_func(void *param)
{
    int *ptr; //
    ptr = malloc(sizeof(int));

    sumdata_t *info = param;
    *ptr = info->num1 + info->num2;

    return ptr; // Return address
}

int main()
{
    pthread_t tid1; //Thread ID
    sumdata_t data;
    int *sum = NULL;
    data.num1 = 5, data.num2 = 10;

    //Create thread 1. Thread 1 will execute sum_func. Arg is &data
    pthread_create(&tid1, NULL, sum_func, &data);

    //Wait for thread 1 to complete using pthread_join
    pthread_join(tid1, (void **) &sum);

    //Print result
    printf("Sum = %d\n", *sum);

    // Free ptr
    free(sum);
    sum = NULL;

    return 0;
}
