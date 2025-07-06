
/*<<doc
name:Murali Venkata Vijay Kumar
date:
description:
sample i/p:
sample o/p:
doc*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* file_processor(void* arg) {
    printf("Thread started. Processing file...\n");

    // Enable cancellation and use deferred mode
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for (int i = 0; i < 10; ++i) {
        printf("Reading chunk %d\n", i);
        sleep(1);  // Simulates time taken to read/process a chunk (this is a cancellation point)
    }

    printf("File processing complete.\n");
    return NULL;
}
int main() {
    pthread_t processor_thread;

    // Create the processing thread
    pthread_create(&processor_thread, NULL, file_processor, NULL);

    sleep(3);  // Let it process a few chunks...

    printf("User clicked cancel! Attempting to cancel the thread...\n");
   // pthread_cancel(processor_thread);  // Sends cancellation request

	pthread_detach(processor_thread);
    // Wait for the thread to finish (and acknowledge cancel)
    void* retval;
  // pthread_join(processor_thread, &retval);
//	pthread_detach(processor_thread);
    printf("User clicked cancel! Attempting to cancel the thread...\n");
	pthread_cancel(processor_thread);

	printf("re attaching detached thread\t");

	pthread_join(processor_thread, &retval);


    if (retval == PTHREAD_CANCELED) {
        printf("Thread was successfully cancelled.\n");
    } else {
        printf("Thread completed normally.\n");
    }
	sleep(6);

    return 0;
}


