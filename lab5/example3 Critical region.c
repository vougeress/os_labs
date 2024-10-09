#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/**
  Explain where the critical region is in this code and why a race condition occurs?
they both used a global variable
 output differs all the time
 **/

int counter = 0;

void *increment(void *arg){
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
}

int main() {
    pthread_t thread1, thread2;
    int result;

    if (pthread_create(&thread1, NULL, increment, NULL)) {
        exit(0);
    }

    if (pthread_create(&thread2, NULL, increment, NULL)) {
        exit(0);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("%d\n", counter);

    return 0;
}
