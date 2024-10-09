#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//until i added pthread_join(threads[i].id, NULL) the order was messed up

#define MAX_MESSAGE_SIZE 256

struct Thread{
    pthread_t id;
    int i;
    char message[MAX_MESSAGE_SIZE];
};

void* threadFucn(void* arg) {
    struct Thread* threadData = (struct Thread*)arg;
    printf("%s\n", threadData->message);
    return NULL;
}

int main(int argc, char* argv[]) {

    int n = atoi(argv[1]);
    struct Thread* threads = malloc(n * sizeof(struct Thread));
    for (int i = 0; i < n; i++){
        threads[i].i = i;
        snprintf(threads[i].message, MAX_MESSAGE_SIZE, "Thread %d\n", i);
        pthread_create(&threads[i].id, NULL, threadFucn, &threads[i]);
        printf("Thread %d is made\n", i);
        pthread_join(threads[i].id, NULL);
    }
    free(threads);
    return 0;

}
