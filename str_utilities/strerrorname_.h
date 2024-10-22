
// strerror_.h
#ifndef STRERROR_H
#define STRERROR_H
// Include solely to get version macros.
#include <string.h>

/* strerrorname_np() exists for glibc >= 2.32 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32 && defined(_GNU_SOURCE)
#ifndef HAS_STRERRORNAME_NP
#define HAS_STRERRORNAME_NP 1
#endif
#endif /* glibc >= 2.32 */

/* printf("%#m") exists for glibc >= 2.35 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 35
#ifndef HAS_PRINTF_M
#define HAS_PRINTF_M 1
#endif
#endif /* glibc >= 2.35 */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strerrorname_(int errnum);

#endif /* STRERROR_H */
