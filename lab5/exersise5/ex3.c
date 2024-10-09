#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int primes_count(int a, int b) {
    int ret = 0;
    for (int i = a; i < b; i++)
        if (is_prime(i))
            ret++;
    return ret;
}

typedef struct {
    int a, b;
} prime_request;

void *prime_counter(void *arg) {
    prime_request *req = (prime_request *)arg;
    int *count = malloc(sizeof(int));
    *count = primes_count(req->a, req->b);
    return (void *)count;
}

int main(int argc, char* argv[]) {

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    pthread_t threads[m];
    prime_request requests[m];
    int range_size = n / m;
    int total_primes = 0;

    for (int i = 0; i < m; i++) {
        requests[i].a = i * range_size;
        if (range_size < n){
            requests[i].b = (i + 1) * range_size;
        } else{
            requests[i].b = n;
        }
        pthread_create(&threads[i], NULL, prime_counter, (void *)&requests[i]);
    }
    for (int i = 0; i < m; i++) {
        int *count;
        pthread_join(threads[i], (void **)&count);
        total_primes += *count;
        free(count);
    }

    printf("Total number of primes  %d\n", total_primes);
    return 0;
}
