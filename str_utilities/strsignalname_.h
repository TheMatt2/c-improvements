#ifndef STRSIGNALNAME_H
#define STRSIGNALNAME_H
// Include solely to get version macros.
#include <signal.h>

/* sigabbrev_np() exists for glibc >= 2.32 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32 && defined(_GNU_SOURCE)
#ifndef HAS_SIGABBREV_NP
#define HAS_SIGABBREV_NP 1
#endif
#endif /* glibc 2.32 */

#ifdef SIG2STR_MAX
#ifndef HAS_SIG2STR
#define HAS_SIG2STR 1
#endif
#endif /* SIG2STR_MAX */

#if defined(__APPLE__) || defined(__BSD__)
#define HAS_SYS_SIGNAME 1
#endif /* __BSD__ */

#if __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 2
#ifndef HAS_SYS_SIGABBREV
#define HAS_SYS_SIGABBREV 1
#endif
#endif /* glibc 2.2 */

#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strsignalname_(int signum);

#endif /* STRSIGNALNAME_H */
