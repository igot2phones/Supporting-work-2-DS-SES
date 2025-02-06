#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) { // Δημιουργία 3 παιδικών διεργασιών με χρήση επαναληπτικής δομής
        pid_t pid = fork(); // Δημιουργία νέας διεργασίας (Child process)

        if (pid < 0) { // Η δημιουργία διεργασίας απέτυχε
            perror("fork");
            return 1;
        } else if (pid == 0) { // διεργασία παιδί
            printf("Child process %d (PID: %d)\n", i + 1, getpid());
            return 0; // Το παιδί τερματίζει εδώ για να μην δημιουργήσει επιπλέον διεργασίες
        }
    }

    // Γονική διεργασία
    for (int i = 0; i < 3; i++) {
        wait(NULL); // Αναμονή για την ολοκλήρωση των παιδικών διεργασιών
    }
    printf("Parent process (PID: %d)\n", getpid());

    return 0;
}