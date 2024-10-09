#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;
int k = 0;
int c = 0;
int n = 0;


bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}


int get_number_to_check() {
    int ret;
    pthread_mutex_lock(&global_lock);
    if (k < n) {
        ret = k;
        k++;
    } else {
        ret = -1;
    }
    pthread_mutex_unlock(&global_lock);
    return ret;
}


void increment_primes() {
    pthread_mutex_lock(&global_lock);
    c++;
    pthread_mutex_unlock(&global_lock);
}


void *check_primes(void *arg) {
    while (1) {
        int number = get_number_to_check();
        if (number == -1) break; // No more numbers to check

        if (is_prime(number)) {
            increment_primes(); // Increment count if the number is prime
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);
    int m = atoi(argv[2]);

    if (n <= 0 || m <= 0) {
        fprintf(stderr, "Both n and m must be positive integers.\n");
        return EXIT_FAILURE;
    }

    pthread_t threads[m];
    for (int i = 0; i < m; i++) {
        pthread_create(&threads[i], NULL, check_primes, NULL);
    }
    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("number of primes %d\n", c);
    pthread_mutex_destroy(&global_lock);
    return EXIT_SUCCESS;
}
