#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pid_t child_pid = -1;

void handle_sigalrm(int sig) {
    printf("Child PID %d: Alarm triggered\n", child_pid);
    exit(0);
}

void handle_sigquit(int sig) {
    printf("Received SIGQUIT\n");
    exit(0);
}

void handle_sigint(int sig) {
    static int count = 0;
    count++;

    if (count == 1) {
        printf("Interrupted\n");
    } else {
        signal(SIGINT, SIG_DFL);
        printf("Exiting on second SIGINT.\n");
        kill(child_pid, SIGQUIT);
    }
}

void create_child(){
    child_pid = fork();
    if (child_pid == 0){
        signal(SIGALRM, handle_sigalrm);
        alarm(3);
        while (1){
            printf("Hello word\n");
        }

    }
    else if (child_pid > 0) {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);
    } else {
        exit(1);
    }


}

int main() {
    create_child();
    while (1) {
        pause();
    }


}
