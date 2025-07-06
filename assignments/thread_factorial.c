#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 3

typedef struct {
    unsigned long int start;
    unsigned long int end;
    unsigned long int partial_result;
} ThreadData;

// Thread function to compute partial factorial
void* compute_partial_factorial(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_result = 1;

    for (unsigned long int i = data->start; i <= data->end; ++i) {
        data->partial_result *= i;
    }

    pthread_exit(NULL);
}

int main() {
    unsigned long int n;
    printf("Enter a number to calculate factorial: ");
    scanf("%lu", &n);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    unsigned long int chunk = n / NUM_THREADS;
    unsigned long int current = 1;

    // Thread creation loop
    for (unsigned long int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = current;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : current + chunk - 1;
        pthread_create(&threads[i], NULL, compute_partial_factorial, (void*)&thread_data[i]);
        current = thread_data[i].end + 1;
    }

    // Thread join loop
    for (unsigned long int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Final result: multiply partial results
    unsigned long int factorial = 1;
    for (unsigned long int i = 0; i < NUM_THREADS; ++i) {
        printf("Thread %lu computed partial factorial from %lu to %lu = %lu\n",
               i, thread_data[i].start, thread_data[i].end, thread_data[i].partial_result);
        factorial *= thread_data[i].partial_result;
    }

    printf("Factorial of %lu is: %lu\n", n, factorial);

    return 0;
}
