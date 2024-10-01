#ifndef STRSIGNAL_H
#define STRSIGNAL_H
#include <string.h>

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

/* strsignal() is defined for _GNU_SOURCE or _POSIX_C_SOURCE (glibc versions?) */
#if defined(_GNU_SOURCE) || _POSIX_C_SOURCE >= 200809L
#ifndef HAS_STRSIGNAL
#define HAS_STRSIGNAL 1
#endif
#endif

/* strsignal() is defacto MT Safe since glibc >= 2.32
 * man 2 strsignal says it isn't safe, but the source code shows it is safe.
 * Treating as the man page not being up to date. */
#if HAS_STRSIGNAL && __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#ifndef HAS_STRSIGNAL_MT_SAFE
#define HAS_STRSIGNAL_MT_SAFE 1
#endif
#endif /* < glibc 2.32 */

/* sigdescr_np() is defined for _GNU_SOURCE */
#ifdef _GNU_SOURCE
#define HAS_SIGDESCR_NP 1
#endif /* _GNU_SOURCE */

/* sys_siglist defined for glibc < 2.32 */
#if !(__GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32)
#ifndef HAS_SYS_SIGLIST
#define HAS_SYS_SIGLIST 1
#endif
#endif /* < glibc 2.32 */

// If HAS_STRSIGNAL_MT_SAFE, just link to the strsignal function directly.
#if HAS_STRSIGNAL_MT_SAFE
#define strsignal_(signum) strsignal(signum)
#else
NO_DISCARD const char* strsignal_(int signum);
#endif /* HAS_STRSIGNAL_MT_SAFE */

#ifdef TEST_STRSIGNAL
#if HAS_SIGDESCR_NP
const char* strsignal_sigdescr(int signum);
#endif /* HAS_SIGDESCR_NP */
#if HAS_STRSIGNAL
const char* strsignal_posix(int signum);
#endif /* HAS_STRSIGNAL */
#if HAS_SYS_SIGLIST
const char* strsignal_sys_siglist(int signum);
#endif /* HAS_SYS_SIGLIST */
const char* strsignal_hardcode(int signum);
#endif /* TEST_STRSIGNAL */

#endif /* STRSIGNAL_H */
