#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 press Ctrl+C, it sends the SIGINT signal
 we can ignore it by setting  signal(SIGINT, SIG_IGN);
 press Ctrl+\, it sends the SIGQUIT
 we can ignore it by setting  signal(SIGQUIT, SIG_IGN);

 kate@MacBook-Pro-Kate os % ./ex4 > output.txt &

[1] 15101
kate@MacBook-Pro-Kate os % kill -s SIGTERM 15101
kate@MacBook-Pro-Kate os %
[1]  + terminated  ./ex4 > output.txt
kate@MacBook-Pro-Kate os %
 
 SIGKILL cannot be caught, handled, or ignored.

 пока я думала как посылать сигнал, у меня нагенерилось 4,68 гигов hello word :)
 *
 */

void handle_sigint(int sig) {
    _exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);
    while (1){
        printf("Hello word\n");
    }
}
