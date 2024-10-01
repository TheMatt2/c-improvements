#include "strsignal_.h"
#include "str_common.h"

#include <time.h> // nanosleep
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

struct test_func {
    char *name;
    const char* (*func)(int);
};

// Reference to test in function calls
static const char* (*function_under_test)(int);

static bool success = true;

struct test_func test_funcs[] = {
#if HAS_STRSIGNAL
    {"strsignal", (void *) strsignal},
#endif /* HAS_STRSIGNAL */
#if HAS_SIGDESCR_NP
    {"strsignal_sigdescr", strsignal_sigdescr},
#endif /* HAS_SIGDESCR_NP */
#if HAS_STRSIGNAL
    {"strsignal_posix", strsignal_posix},
#endif /* HAS_STRSIGNAL */
#if HAS_SYS_SIGLIST
    {"strsignal_sys_siglist", strsignal_sys_siglist},
#endif /* HAS_SYS_SIGLIST */
    {"strsignal_hardcode", strsignal_hardcode}
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    int signum = *((int*)arg);
    const char *msg = function_under_test(signum);
    char *dup_msg = strdup(msg);

    pthread_mutex_lock(&mutex);
    printf("Thread %d: %s\n", signum, msg);

    // Check string is the same.
    if (strcmp(msg, dup_msg) != 0)
    {
        printf("FAILED: %s does not match %s\n", msg, dup_msg);
        success = false;
    }

    pthread_mutex_unlock(&mutex);

    free(dup_msg);
    return NULL;
}

void test_func() {
    // 2 invalid signal values
    int test_signals[2] = {71, 72};

    pthread_t threads[2];

    pthread_mutex_lock(&mutex);

    // Create two threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &test_signals[i]);
    }

    // Sleep
    nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);

    // Explicitly synchronize threads to show race condition.
    pthread_mutex_unlock(&mutex);

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    // Test all functions

    for (size_t i = 0; i < ARRAY_SIZE(test_funcs); i++)
    {
        printf("Test %s\n", test_funcs[i].name);

        for (size_t j = 0; j < 3; j++)
        {
            function_under_test = test_funcs[i].func;
            test_func();
        }
    }

    if (success)
    {
        printf("\nTests Passed\n");
    }
    else
    {
        printf("\nTests Failed\n");
    }

    return 0;
}
