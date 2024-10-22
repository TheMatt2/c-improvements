#define __STDC_WANT_LIB_EXT1__ 1
#include "strerror_.h"
#include "str_common.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


#ifndef TEST_STR_UTILS
// Allow specific functions to be linkable only if test macro is set.
#define TEST_LINKAGE static
#else
#define TEST_LINKAGE /* nothing */
#endif /* TEST_STR_UTILS */

// Longest EN error message on linux is EILSEQ is 49 characters + null.
#define ERRBUF_LEN 50

#if HAS_STRERROR_S
// Use strerror_s() to print error message.
TEST_LINKAGE const char* strerror_s_safe(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    strerror_s(errbuf, sizeof(errbuf), errnum);
    return errbuf;
}
#endif /* HAS_STRERROR_S */

#if HAS_PRINTF_M
// Use printf("%m") to get errno string
// Pedantic warnings warns about usage of %m, but this code already checks
// %m is only used if available.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif /* __GNUC__ */
TEST_LINKAGE const char* strerror_printf_m(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    int prev_errno = errno;
    errno = errnum;

    snprintf(errbuf, sizeof(errbuf), "%m");
    errno = prev_errno;
    return errbuf;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
#endif /* HAS_PRINTF_M */

// POSIX General Solution.
TEST_LINKAGE const char* strerror_posix(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
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

#if !HAS_STRERROR_MT_SAFE
// If strerror is safe, no need to define anything hear.
const char* strerror_(int errnum)
{
#if HAS_STRERROR_S
    return strerror_s_safe(errnum);
#elif HAS_PRINTF_M
    return strerror_printf_m(errnum);
#else
    return strerror_posix(errnum);
#endif
}
#endif /* HAS_STRERROR_MT_SAFE */
