#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/**
took program from the last example and just moved the pthread_join(thread1, NULL) now it waits till the first one ends
Using pthread_join we ensure that only one process execute at a time
 **/

int counter = 0;

void *increment(void *arg){
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
}

int main() {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, increment, NULL)) {
        exit(0);
    }
    pthread_join(thread1, NULL);

    if (pthread_create(&thread2, NULL, increment, NULL)) {
        exit(0);
    }
    pthread_join(thread2, NULL);

    printf("%d\n", counter);

    return 0;
}
