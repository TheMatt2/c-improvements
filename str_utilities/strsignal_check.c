// gcc -Wall -std=c11 ./strsignal_check.c -o strsignal_check
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    int signum = *((int*)arg);
    const char *msg = strsignal(signum);

    pthread_mutex_lock(&mutex);
    printf("Thread %d: %s\n", signum, msg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int signums[2] = {71, 72};

    pthread_mutex_lock(&mutex);

    // Create two threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &signums[i]);
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
