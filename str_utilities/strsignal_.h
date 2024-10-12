#ifndef STRSIGNAL_H
#define STRSIGNAL_H
#include <string.h>

#ifdef __APPLE__
#include <Availability.h>
#endif

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

/* strsignal() is defined for _GNU_SOURCE or _POSIX_C_SOURCE since glibc 1.09.
 * strsignal() is defined for MacOS since 10.6(?).
 */
#if defined(_GNU_SOURCE) || _POSIX_C_SOURCE >= 200809L
#ifndef HAS_STRSIGNAL
#define HAS_STRSIGNAL 1
#endif
#elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_6
#ifndef HAS_STRSIGNAL
#define HAS_STRSIGNAL 1
#endif
#endif

/* strsignal() is defacto MT Safe since glibc >= 2.32
 * man 2 strsignal says it isn't safe, but the source code shows it is safe.
 * Treating as the man page not being up to date.
 * strsignal() is MT safe starting with Mac OSX 10.7 according to man page. */
#if HAS_STRSIGNAL && __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#ifndef HAS_STRSIGNAL_MT_SAFE
#define HAS_STRSIGNAL_MT_SAFE 1
#endif
#elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_7
#ifndef HAS_STRSIGNAL_MT_SAFE
#define HAS_STRSIGNAL_MT_SAFE 1
#endif
#endif /* < glibc 2.32 */

/* sigdescr_np() is defined for _GNU_SOURCE */
#if defined(_GNU_SOURCE) && __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#define HAS_SIGDESCR_NP 1
#endif /* _GNU_SOURCE */

/* sys_siglist defined for glibc < 2.32 */
#if defined(__GLIBC__) && !(__GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32)
#ifndef HAS_SYS_SIGLIST
#define HAS_SYS_SIGLIST 1
#endif
#elif __APPLE__
/* sys_siglist defined for MacOS since at least Mac OS X 10.2 */
#ifndef HAS_SYS_SIGLIST
#define HAS_SYS_SIGLIST 1
#endif
#endif

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
