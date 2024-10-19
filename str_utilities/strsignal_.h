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

/* strsignal() is defacto MT Safe since glibc >= 2.32
 * man 2 strsignal says it isn't safe, but the source code shows it is safe.
 * Treating as the man page not being up to date.
 * strsignal() is MT safe starting with Mac OSX 10.7 according to man page. */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#ifndef HAS_STRSIGNAL_MT_SAFE
#define HAS_STRSIGNAL_MT_SAFE 1
#endif
#elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_7
#ifndef HAS_STRSIGNAL_MT_SAFE
#define HAS_STRSIGNAL_MT_SAFE 1
#endif
#endif /* < glibc 2.32 */

// If HAS_STRSIGNAL_MT_SAFE, just link to the strsignal function directly.
#if HAS_STRSIGNAL_MT_SAFE
#define strsignal_ strsignal
#else
NO_DISCARD const char* strsignal_(int signum);
#endif /* HAS_STRSIGNAL_MT_SAFE */
#endif /* STRSIGNAL_H */
