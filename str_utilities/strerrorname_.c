#include "strerrorname_.h"
#include "str_common.h"

#include <errno.h>
#include <stdio.h>


#ifndef TEST_STRSIGNAL
// Allow specific functions to be linkable only if test macro is set.
#define TEST_LINKAGE static
#else
#define TEST_LINKAGE /* nothing */
#endif /* TEST_STRSIGNAL */

// Longest EN error message on linux is EILSEQ is 49 characters + null.
#define ERRBUF_LEN 16

#if HAS_STRERRORNAME_NP
// Use strerror_s() to print error message.
TEST_LINKAGE const char* strerrorname_gnu_np(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    // Call strerrorname_np() to get error name
    const char *buf = strerrorname_np(errnum);
    if (buf == NULL)
    {
        snprintf(errbuf, sizeof(errbuf), "%d", errnum);
        buf = errbuf;
    }
    return buf;
}
#endif /* HAS_STRERRORNAME_NP */

#if HAS_PRINTF_M
// Use printf("%m") to get errno string
// Pedantic warnings warns about usage of %m, but this code already checks
// %m is only used if available.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif /* __GNUC__ */
TEST_LINKAGE const char* strerrorname_printf_m(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    int prev_errno = errno;
    errno = errnum;

    snprintf(errbuf, sizeof(errbuf), "%#m");
    errno = prev_errno;
    return errbuf;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
#endif /* HAS_PRINTF_M */

// Hardcode solution
TEST_LINKAGE const char* strerrorname_hardcode(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    const char *buf = "TODO";
    return buf;
}

const char* strerrorname_(int errnum)
{
#if HAS_STRERRORNAME_NP
    return strerrorname_gnu_np(errnum);
#elif HAS_PRINTF_M
    return strerrorname_printf_m(errnum);
#else
    return strerrorname_hardcode(errnum);
#endif
}
