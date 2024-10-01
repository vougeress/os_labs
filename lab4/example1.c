#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
1) What is the relationship between the processes?
parent-child relationship, where the parent creates a child process.
They operate independently, but the parent can manage the child,
and they can communicate or synchronize as needed.

 How to differentiate the parent from the child process?
Differentiating between a parent process and a child process in a C program is done by examining the return value of the fork().
If fork() returns a positive value (the PID of the child), you are in the parent process.
In the Child Process:
If fork() returns 0, you are in the child process.
Error Handling:
If fork() returns a negative value (-1), it indicates an error occurred while trying to create a new process.
**/
/**
int main() {
    int n = 4;
    pid_t pid = fork();
    if (pid < 0){
        printf("failed");
        return 1;
    } else if(pid == 0){
        printf("Hello from [PID - %d - %p]\n", getpid(), (void*)&n);
    } else {
        printf("Hello from parent process! (PID: %d)\n", getpid());
    }
}
**/

//Terminate both processes. Terminate one of them as a normal exit and the other as an error exit.
/**
int main() {
    int n = 4;
    pid_t pid = fork();
    if (pid < 0){
        printf("failed");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        printf("Hello from [PID - %d - %p]\n", getpid(), (void*)&n);
        sleep(2);
        printf("Child process is exiting normally.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Hello from parent process! (PID: %d)\n", getpid());
        sleep(1);
        printf("Parent process is exiting.\n");
        exit(EXIT_FAILURE);
    }
}
**/
// если родителю дать больше времени то ребенок успевает сдохнуть нормально, иначе он станет сиротой

// Попытка поймать сироту и посмотреть кто его родитель (оказалось его родителем станет процесс с PID 1 (обычно init процесс)).
/**
int main() {
    int n = 4;
    pid_t pid = fork();
    if (pid < 0){
        printf("failed");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        printf("Hello from [PID - %d - %p]\n", getpid(), (void*)&n);
        sleep(2);
        printf("Сирота с новым родителем (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        printf("Child process is exiting normally.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Hello from parent process! (PID: %d)\n", getpid());
        sleep(1);
        printf("Parent process is exiting.\n");
        exit(EXIT_FAILURE);
    }
}
**/

// Run the program and modify the code to let the parent process kill the child process using the function kill with the signal

/**
int main() {
    int n = 4;
    pid_t pid = fork();
    if (pid < 0){
        printf("failed");
        return 1;
    } else if(pid == 0){
        printf("Hello from [PID - %d - %p]\n", getpid(), (void*)&n);
        while (1) {
            printf("child sis sleeping peacefully");
            sleep(1);
        }
    } else {
        printf("Hello from parent process! (PID: %d)\n", getpid());
        sleep(2);
        if (kill(pid, SIGKILL) == 0) {
            printf("Parent killed the child process (PID: %d)\n", pid);
        }
    }
}
**/

//What is the maximum value for process ID that you can create in your operating system?
//sysctl kern.maxproc: kern.maxproc: 4000

// Which process has no parents like root (/) directory in case of files?
// "init" process

// What is the value of its ppid?
// 1
