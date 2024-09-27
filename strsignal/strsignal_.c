#include <stdio.h>
#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message "GLIBC " XSTR(__GLIBC__) "." XSTR(__GLIBC_MINOR__)


// strsignal_.h
#ifndef STRSIGNAL_H
#define STRSIGNAL_H

/**
 * Convert a signal to a string for printing.
 * Must be thread safe.
 */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strsignal_(int signum);

#endif /* STRSIGNAL_H */

#include <string.h>


/* Define thread_local for thread specific buffer */
#if __STDC_VERSION__ <= 199901L
#define thread_local __thread
#elif __STDC_VERSION__ < 202311L
// C23 changes thread_local to be a keyword
#define thread_local _Thread_local
#endif


/* strsignal() is defined for _GNU_SOURCE or _POSIX_C_SOURCE (glibc versions?) */
#if _GNU_SOURCE || _POSIX_C_SOURCE >= 200809L
#ifndef HAS_STRSIGNAL
#define HAS_STRSIGNAL 1
#endif
#endif

/* sigdescr_np() is defined for _GNU_SOURCE */
#if _GNU_SOURCE
#define HAS_SIGDESCR_NP 1
#define HAS_SIGABBREV_NP 1
#endif /* _GNU_SOURCE */

#if HAS_SIGDESCR_NP
// sigdescr_np Solution.
// Preferred due to built in thread safe
const char* strsignal_(int signum)
{
    static thread_local char sigbuf[25] = {0};
    const char *buf;
    // Call sigdescr_np() to get signal string
    buf = sigdescr_np(signum);
    if (buf == NULL)
    {
        snprintf(sigbuf, sizeof(sigbuf) - 1, "Unknown signal %d", signum);
        buf = sigbuf;
    }

    return buf;
}
#elif HAS_STRSIGNAL
// POSIX General Solution.
#include <pthread.h>


const char* strsignal_(int signum)
{
    // Thread local buffer for signal string.
    // Longest EN error message on linux 24 characters.
    static thread_local char sigbuf[25] = {0};
    const char *buf;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strsignal() to get signal string
    buf = strsignal(signum);
    // Copy to a thread specific buffer. Always leave null terminator.
    buf = strncpy(sigbuf, buf, sizeof(sigbuf) - 1);
    pthread_mutex_unlock(&mutex);
    return buf;
}
#else
// Otherwise, strsignal is not defined, don't compile.
#error "strerror not defined"
#endif
