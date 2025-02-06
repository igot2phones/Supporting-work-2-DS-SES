#include <stdio.h>
#include <pthread.h>

void *print_message(void *ptr) {
    printf("Hello from thread\n");
    return NULL;
}

int main() {
    pthread_t thread;
    // Create a new thread
    pthread_create(&thread, NULL, print_message, NULL);
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    printf("Thread has finished execution\n");
    return 0;
}