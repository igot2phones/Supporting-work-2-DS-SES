#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Δημιουργία νέας διεργασίας (Child process)

    if (pid < 0) { // Η δημιουργία διεργασίας απέτυχε
        perror("fork");
        exit(1);
    } else if (pid == 0) { // διεργασία παιδί (Child process) 
        printf("Child process (PID: %d)\n", getpid());
    } else { // Γονική διεργασία (Parent process)
        printf("Parent process (PID: %d)\n", getpid());
        wait(NULL); // Αναμονή για την ολοκλήρωση της παιδικής διεργασίας
    }

    return 0;
}