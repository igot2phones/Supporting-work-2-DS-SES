#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 

#define NUM_THREADS 4 // Ορισμός του αριθμού των νημάτων

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Αρχικοποίηση του mutex
int shared_var = 0; // Κοινή μεταβλητή
int current_thread = 0; // Μεταβλητή για την παρακολούθηση του τρέχοντος νήματος

void* thread_func(void* arg) {
    int thread_num = *(int*)arg; // Απόκτηση του αριθμού του νήματος

    for(int i = 0; i < 2; i++) { // Κάθε νήμα εκτελείται δύο φορές για επίδειξη
        int done = 0; // Μεταβλητή για τον έλεγχο ολοκλήρωσης
        while(!done) {
            // Ξεκλείδωμα του mutex
            pthread_mutex_lock(&mutex);
            
            if(current_thread == thread_num) { // Έλεγχος αν είναι η σειρά του νήματος
                shared_var += 1; // Αύξηση της κοινής μεταβλητής
                printf("I am thread %d and I got: %d\n", thread_num + 1, shared_var); // Εκτύπωση του αποτελέσματος
                current_thread = (current_thread + 1) % NUM_THREADS; // Ενημέρωση του τρέχοντος νήματος
                done = 1; // Ολοκλήρωση της εργασίας
            }

            // Ξεκλείδωμα του mutex
            pthread_mutex_unlock(&mutex);
            
            if(!done) {
                usleep(10000); // Ύπνος για αποφυγή busy waiting
            }
        }
    }
    return 0; // Επιστροφή από τη συνάρτηση νήματος
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}