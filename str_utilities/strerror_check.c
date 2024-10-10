// gcc -Wall -std=c11 ./strerror_check.c -o strerror_check
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    int errnum = *((int*)arg);
    // printf("Thread %d: %s\n", errnum, strerror(errnum));
    const char *msg = strsignal(errnum);

    pthread_mutex_lock(&mutex);
    printf("Thread %d: %s\n", errnum, msg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[2];
    // int errnums[2] = {SIGILL, SIGSEGV};
    int errnums[2] = {71, 72};

    pthread_mutex_lock(&mutex);

    // Create two threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &errnums[i]);
    }

    // Sleep
    nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);

    // Explicitly synchronize threads to show race condition.
    pthread_mutex_unlock(&mutex);

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
