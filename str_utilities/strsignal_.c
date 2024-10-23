// strsignal added in POSIX.1-2008
#define _POSIX_C_SOURCE 200809L
#include "strsignal_.h"
#include "str_common.h"

// If strsignal is safe, no need to define anything hear.
#if !HAS_STRSIGNAL_MT_SAFE || defined(TEST_STR_UTILS)
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>


// Longest strsignal message on BSD "Filesize limit exceeded: 25"
#define SIGBUF_LEN 30

// POSIX threadsafe wrapper around strsignal().
LOCAL_LINKAGE const char* strsignal_posix(int signum)
{
    // Thread local buffer for signal string.
    static thread_local char sigbuf[SIGBUF_LEN] = {0};
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strsignal() to get signal string
    const char *buf = strsignal(signum);
    // Copy to a thread specific buffer. Always leave null terminator.
    buf = strncpy(sigbuf, buf, sizeof(sigbuf) - 1);
    pthread_mutex_unlock(&mutex);
    return buf;
}

#if !HAS_STRSIGNAL_MT_SAFE
const char* strsignal_(int signum)
{
    // Void reference to suppress unused warnings.
    return strsignal_posix(signum);
}
#endif /* HAS_STRSIGNAL_MT_SAFE */
#endif /* HAS_STRSIGNAL_MT_SAFE */
