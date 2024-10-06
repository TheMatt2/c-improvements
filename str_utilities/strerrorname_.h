
// strerror_.h
#ifndef STRERROR_H
#define STRERROR_H
// Include solely to get macros.
#include <string.h>

/* strerror() is MT-safe for glibc >= 2.32 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32
#ifndef HAS_STRERRORNAME_NP
#define HAS_STRERRORNAME_NP 1
#endif
#endif /* glibc >= 2.32 */

/* printf("%m") is defacto MT-safe for glibc >= 1.06 */
#if __GLIBC__ >= 1 && __GLIBC_MINOR__ >= 6
#ifndef HAS_PRINTF_M
#define HAS_PRINTF_M 1
#endif
#endif /* glibc >= 1.06 */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strerrorname_(int errnum);

#ifdef TEST_STRSIGNAL
#if HAS_STRERRORNAME_NP
const char* strerrorname_gnu_np(int errnum);
#endif /* HAS_STRERRORNAME_NP */
#if HAS_PRINTF_M
const char* strerrorname_printf_m(int errnum);
#endif /* HAS_PRINTF_M */
const char* strerrorname_hardcode(int errnum);
#endif /* TEST_STRSIGNAL */

#endif /* STRERROR_H */
