/*
 * Despite strerror_r being a POSIX 2001 standard function, glibc offers
 * a non-compliant version of strerror_r if _GNU_SOURCE is set.
 *
 * _POSIX_C_SOURCE can not meaningfully be unset, as some platforms also have
 * _POSIX_SOURCE or _XOPEN_SOURCE that act as aliases, and this implementation
 * can not assume it can predict all test macros. _GNU_SOURCE, on the other
 * hand is specific to GNU Linux glibc, and there is no alternatives macros,
 * so it is safe to undefine it make sure we get a POSIX compliant strerror_r.
 *
 * Set _DEFAULT_SOURCE to make sure POSIX strerror_r is available.
 */
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#define _DEFAULT_SOURCE
#endif

#define __STDC_WANT_LIB_EXT1__ 1
#include "strerror_.h"
#include "str_common.h"

// If strerror is safe, no need to define anything hear.
#if !HAS_STRERROR_MT_SAFE || defined(TEST_STR_UTILS)
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


// Longest EN error message on linux is EILSEQ is 49 characters + null.
#define ERRBUF_LEN 50

#if HAS_STRERROR_S
// Use strerror_s() to print error message.
LOCAL_LINKAGE const char* strerror_s_safe(int errnum)
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
LOCAL_LINKAGE const char* strerror_printf_m(int errnum)
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

#if HAS_STRERROR_R
LOCAL_LINKAGE const char* strerror_r_xpg(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    int prev_errno = errno;
    strerror_r(errnum, errbuf, sizeof(errbuf));
    errno = prev_errno;
    return errbuf;
}
#endif /* HAS_STRERROR_R */

// POSIX General Solution.
LOCAL_LINKAGE const char* strerror_posix(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    const char *buf;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strerror() to get error status
    buf = strerror(errnum);
    if (buf != NULL) {
        // Copy to a thread specific buffer. Always leave null terminator.
        buf = strncpy(errbuf, buf, sizeof(errbuf) - 1);
    } else {
        // man strerror
        // "On some systems (but not on Linux), NULL may instead be returned."
        snprintf(errbuf, sizeof(errbuf), "Unknown error %d", errnum);
    }
    pthread_mutex_unlock(&mutex);
    return buf;
}

#if !HAS_STRERROR_MT_SAFE
const char* strerror_(int errnum)
{
    // Void reference to suppress unused warnings.
#if HAS_STRERROR_S
    (void) strerror_s_safe;
#endif
#if HAS_PRINTF_M
    (void) strerror_printf_m;
#endif
#if HAS_STRERROR_R
    (void) strerror_r_xpg;
#endif
    (void) strerror_posix;

#if HAS_STRERROR_S
    return strerror_s_safe(errnum);
#elif HAS_PRINTF_M
    return strerror_printf_m(errnum);
#elif HAS_STRERROR_R
    return strerror_r_xpg(errnum);
#else
    return strerror_posix(errnum);
#endif
}
#endif /* HAS_STRERROR_MT_SAFE */
#endif /* !HAS_STRERROR_MT_SAFE || defined(TEST_STR_UTILS) */
