#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            close(pipefd[0]); // Close read end
            char message[50];
            snprintf(message, sizeof(message), "This is from child %d (PID: %d)\n", i + 1, getpid());
            write(pipefd[1], message, strlen(message));
            close(pipefd[1]);
            return 0;
        }
    }

    close(pipefd[1]); // Close write end in parent
    char buffer[100];
    while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
        printf("%s", buffer);
    }
    close(pipefd[0]);

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Parent process (PID: %d)\n", getpid());

    return 0;
}