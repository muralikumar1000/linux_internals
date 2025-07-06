
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
#include <stdlib.h>

void* worker_thread(void* arg) {
    printf("Detached thread started.\n");
    fflush(stdout);

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);           // Allow cancellation
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);          // Only cancel at points like sleep or testcancel

    for (int i = 0; i < 20; ++i) {
        printf("Working... step %d\n", i);
        fflush(stdout);
        sleep(1);  // This is a natural cancellation point

        pthread_testcancel();  // Manually check if cancel was requested

        // Simulate some work
    }

    printf("Thread completed without cancellation.\n");
    fflush(stdout);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;

    // Initialize thread attributes and set it as detached
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create the thread
    pthread_create(&thread, &attr, worker_thread, NULL);
    pthread_attr_destroy(&attr);  // We don't need the attr object anymore

    // Let the thread run for a few seconds
    sleep(5);

    printf("Main: Sending cancel request to detached thread...\n");
    fflush(stdout);
   // pthread_cancel(thread);  // Fire the cancellation

    // Give thread time to cleanup and exit
    sleep(5);

    printf("Main: Exiting. No join() needed for detached thread.\n");
    return 0;
}




