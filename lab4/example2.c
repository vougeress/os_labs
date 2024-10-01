#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();
    if (pid < 0){
        printf("failed");
        return 1;
    } else if(pid == 0){
        printf("Hello from [PID - %d]\n", getpid());
        sleep(40);
    } else {
        printf("Hello from parent process! (PID: %d)\n", getpid());
        printf("Created Child Process: PID = %d\n", pid);
        printf("Parent Process woke up after 2 seconds.\n");
        kill(pid, SIGKILL);
        printf("Killed Child Process: PID = %d\n", pid);
        sleep(5);
    }
}


/**
Как можно управлять зомби-процессами:
Обработка завершения: Родительский процесс должен использовать wait() или waitpid() для обработки завершения дочерних процессов и удаления их записей из таблицы.
Использование сигналов: Родительский процесс может установить обработчик сигнала SIGCHLD, чтобы автоматически обрабатывать завершение дочерних процессов.
**/

