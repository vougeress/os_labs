#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PIPE_DIR "/tmp/ex1"
#define MAX_MSG_SIZE 1024

void create_named_pipe(int index) {
    char pipe_path[256];
    sprintf(pipe_path, "%s/s%d", PIPE_DIR, index);

    if (mkfifo(pipe_path, 0666) == -1) {
        exit(1);
    }
}

void write_to_pipe(int index) {
    char pipe_path[256];
    sprintf(pipe_path, "%s/s%d", PIPE_DIR, index);

    int pipe_fd = open(pipe_path, O_WRONLY);
    char message[MAX_MSG_SIZE];

    while (1) {
        if (fgets(message, MAX_MSG_SIZE, stdin) == NULL) {
            break;
        }
        if (write(pipe_fd, message, strlen(message) + 1) == -1) {
            perror("write");
            close(pipe_fd);
            exit(1);
        }
    }

    close(pipe_fd);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    if (mkdir(PIPE_DIR, 0777) == -1 && access(PIPE_DIR, F_OK) == -1) {
        exit(1);
    }
    for (int i = 1; i <= n; i++) {
        create_named_pipe(i);
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (pid == 0) {
            write_to_pipe(i);
            exit(0);
        }
    }
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
    return 0;
}
