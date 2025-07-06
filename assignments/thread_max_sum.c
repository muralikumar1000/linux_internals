#include <stdio.h>
#include <pthread.h>
#include <limits.h>


#define NUM_THREADS 5

long int max;
unsigned long int sum;
pthread_mutex_t mutex;
typedef struct {
    unsigned long int start;
    unsigned long int end;
    int *array;
} ThreadData;

// Thread function to compute partial factorial
void* compute_max_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    pthread_mutex_lock(&mutex);

    for (unsigned long int i = data->start; i <= data->end; ++i) {
        sum += data->array[i];
        if (data->array[i] > max) {
            max = data->array[i];
        }

    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    unsigned long int n;
    max = LONG_MIN; // Initialize max to the smallest possible value
    
    printf("Enter size of array: ");
    scanf("%lu", &n);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int array[n];
    for(int i = 0; i < n; ++i) {
        array[i] = i + 1; // Initialize array with values 1 to n
    }


    unsigned long int chunk = n / NUM_THREADS;
    unsigned long int current = 0;

    pthread_mutex_init(&mutex, NULL);

    // Thread creation loop
    for (unsigned long int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = current;
        thread_data[i].end = (i == n - 1) ? n-1 : current + chunk - 1;
        thread_data[i].array = array;
        pthread_create(&threads[i], NULL, compute_max_sum, (void*)&thread_data[i]);
        current = thread_data[i].end + 1;
    }

    // Thread join loop
    for (unsigned long int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("max = %lu sum = %lu\n", max, sum);

    return 0;
}
