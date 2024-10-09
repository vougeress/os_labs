#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024

int main() {
    int pipe_fd[2]; 
    pid_t pid;
    char message[MAX];
    if (pipe(pipe_fd) == -1) {
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        close(pipe_fd[0]);
        printf("Publisher: ");
        fgets(message, MAX, stdin);
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
    }
    else {
        close(pipe_fd[1]);
        read(pipe_fd[0], message, MAX);
        printf("Subscriber got %s", message);
        close(pipe_fd[0]);
    }
        return 0;
}
