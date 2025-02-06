#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_message(void *ptr) {
    printf("Hello from thread %ld\n", (long)ptr);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc; // Return code
    long i;

    for(i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, print_message, (void *)i);
        if (rc != 0) {
            printf("Error creating thread %ld\n", i);
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution\n");
    return 0;
}