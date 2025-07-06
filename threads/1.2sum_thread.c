/* FILE: simple_thread.c 
 * Description: 
 */

#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int num1, num2;
    int result;
} sumdata_t;

void *sum_func(void *param)
{
    sumdata_t *info = param;
    info->result = info->num1 + info->num2;

    return NULL;
}

int main()
{
    pthread_t tid1; //Thread ID
    sumdata_t data;
    data.num1 = 5, data.num2 = 10;

    //Create thread 1. Thread 1 will execute sum_func. Arg is &data
    pthread_create(&tid1, NULL, sum_func, &data);

    //Wait for thread 1 to complete using pthread_join
    pthread_join(tid1, NULL);

    //Print result
    printf("Sum = %d\n", data.result);

    return 0;
}
