#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pipe1[2];
    int pipe2[2];
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        char buffer[256];
        read(pipe1[0], buffer, sizeof(buffer));
        close(pipe1[0]);
        printf("Child received: %s\n", buffer);
        int length = strlen(buffer);
        write(pipe2[1], &length, sizeof(length));
        close(pipe2[1]);
    } else {
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], argv[1], strlen(argv[1]) + 1);
        close(pipe1[1]);
        int length;
        read(pipe2[0], &length, sizeof(length));
        close(pipe2[0]);
        printf("Parent received length: %d\n", length);
    }

    return 0;
}
