#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/**
each time the result is different
 **/

/**
int counter = 0;

void *increment(void *arg){
    for (int i = 0; i < 1000; i++) {
        counter++;
    }
}


int main() {
    pthread_t threads[1000];
    for (int i = 0; i < 1000; i++){
        if (pthread_create(&threads[i], NULL, increment, NULL)) {
            exit(0);
        }
    }
    for (int i = 0; i < 1000; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("%d\n", counter);

    return 0;
}

**/

int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg){
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
}


int main() {
    pthread_t threads[1000];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < 1000; i++){
        if (pthread_create(&threads[i], NULL, increment, NULL)) {
            exit(0);
        }
    }
    for (int i = 0; i < 1000; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("%d\n", counter);

    return 0;
}

