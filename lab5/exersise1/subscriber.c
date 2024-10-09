#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024
#define BASE_PATH "/tmp/ex1/s"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <subscriber id (1-3)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int id = atoi(argv[1]);
    if (id < 1 || id > 3) {
        fprintf(stderr, "Subscriber ID must be between 1 and 3.\n");
        exit(EXIT_FAILURE);
    }

    char pipe_path[BUFFER_SIZE];
    snprintf(pipe_path, sizeof(pipe_path), "%s%d", BASE_PATH, id);

    // Open the named pipe for reading
    int fd = open(pipe_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (1) {
        ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf("Subscriber %d received message: %s\n", id, buffer);
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(fd);
    return 0;
}
