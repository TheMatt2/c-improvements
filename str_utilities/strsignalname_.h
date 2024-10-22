#ifndef STRERRORNAME_H
#define STRERRORNAME_H
// Include solely to get version macros.
#include <signal.h>

/* sigabbrev_np() exists for glibc >= 2.32 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32 && defined(_GNU_SOURCE)
#ifndef HAS_SIGABBREV_NP
#define HAS_SIGABBREV_NP 1
#endif
#endif /* glibc 2.32 */

#if defined(__APPLE__) || defined(__BSD__)
#define HAS_SYS_SIGNAME 1
#endif /* __BSD__ */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strsignalname_(int signum);

#endif /* STRERRORNAME_H */
