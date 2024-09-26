#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message "GLIBC " XSTR(__GLIBC__) "." XSTR(__GLIBC_MINOR__)
#pragma message "__STDC_WANT_LIB_EXT1__ " XSTR(__STDC_WANT_LIB_EXT1__)


// strerror_.h
#ifndef STRERROR_H
#define STRERROR_H

/**
 * @brief Portable thread safe strerror()
 *
 * A version of strerror() guaranteed to be thread safe
 * and meant to be portable across multiple platforms.
 *
 * The returned string may be overwritten after future calls to strerror_()
 * from the same thread.
 *
 * Thread safe. Not async safe.
 *
 * Behavior is undefined if locale is set to something other than LC_ALL.
 *
 * @param errnum Errno number to make a user generated string for.
 * @returns Pointer to const string representing the error.
 */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strerror_(int errnum);

#endif /* STRERROR_H */

#define __STDC_WANT_LIB_EXT1__ 1
#include <errno.h>
#include <stdio.h>
#include <string.h>

// #pragma message "__STDC_LIB_EXT1__ " XSTR(__STDC_LIB_EXT1__)



/* strerror() is MT-safe for glibc >= 2.32 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#ifndef HAS_STRERROR_MT_SAFE
#define HAS_STRERROR_MT_SAFE 1
#endif
#endif /* glibc >= 2.32 */

/* printf("%m") is defacto MT-safe for glibc >= 1.06 */
#if __GLIBC__ >= 1 && __GLIBC_MINOR__ >= 6
#ifndef HAS_PRINTF_M
#define HAS_PRINTF_M 1
#endif
#endif /* glibc >= 1.06 */

/* strerror_s() is defined for C11 if __STDC_LIB_EXT1__ is set */
#ifdef __STDC_LIB_EXT1__
#ifndef HAS_STRERROR_S
#define HAS_STRERROR_S 1
#endif
#endif /* __STDC_LIB_EXT1__ */

/* Define thread_local for thread specific buffer */
#if __STDC_VERSION__ <= 199901L
#define thread_local __thread
#elif __STDC_VERSION__ < 202311L
// C23 changes thread_local to be a keyword
#define thread_local _Thread_local
#endif


#if HAS_STRERROR_MT_SAFE
// Just call strerror() when safe.
const char* strerror_(int errnum)
{
    return strerror(errnum);
}
#elif HAS_STRERROR_S
// Use strerror_s() to print error message.
const char* strerror_(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    strerror_s(errbuf, sizeof(errbuf), errnum);
    return errbuf;
}
#elif HAS_PRINTF_M
// Use printf("%m") to get errno string
// Pedantic warnings warns about usage of %m, but this code already checks
// %m is only used if available.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif /* __GNUC__ */
const char* strerror_(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    int prev_errno = errno;
    errno = errnum;

    snprintf(errbuf, sizeof(errbuf) - 1, "%m");
    errno = prev_errno;
    return errbuf;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
#else
// POSIX General Solution.
#include <pthread.h>


const char* strerror_(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    const char *buf;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strerror() to get error status
    buf = strerror(errnum);
    // Copy to a thread specific buffer. Always leave null terminator.
    buf = strncpy(errbuf, buf, sizeof(errbuf) - 1);
    pthread_mutex_unlock(&mutex);
    return buf;
}
#endif

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    printf("   (0): %s\n", strerror_(0));
    printf("EBADF : %s\n", strerror_(EBADF));
    printf("EILSEQ: %s\n", strerror_(EILSEQ));
    printf(" (999): %s\n", strerror_(999));

    return 0;
}
