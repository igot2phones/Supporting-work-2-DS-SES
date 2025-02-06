#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2]; // File descriptors for the pipe ends (fd[0] for read, fd[1] for write)
    pid_t pid;
    char buffer[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process
        close(fd[0]); // Close unused read end
        char message[] = "Hello from child";
        write(fd[1], message, strlen(message) + 1); // Write message to the pipe
        close(fd[1]);// Close write end
        return 0;
    } else { // Parent process
        close(fd[1]); // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer); // Read message from the pipe
        close(fd[0]);// Close read end
    }

    return 0;
}