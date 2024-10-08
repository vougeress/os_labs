#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *start_routine(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread ID: %lu\n", (unsigned long)thread_id);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int result;
    result = pthread_create(&threads[0], NULL, start_routine, NULL);
    result = pthread_create(&threads[1], NULL, start_routine, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads are done.\n");
    return 0;
}
