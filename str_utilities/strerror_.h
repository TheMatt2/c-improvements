
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

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

#if HAS_STRERROR_MT_SAFE
// Just call strerror() when safe.
#define strerror_ strerror
#else
NO_DISCARD const char* strerror_(int errnum);
#endif /* HAS_STRERROR_MT_SAFE */
#endif /* STRERROR_H */
