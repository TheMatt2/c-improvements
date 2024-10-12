#include "strsignal_.h"
#include "str_common.h"

#include <stdio.h> // snprintf
#include <string.h>
#include <signal.h>


#ifndef TEST_STRSIGNAL
// Allow specific functions to be linkable only if test macro is set.
#define TEST_LINKAGE static inline
#else
#define TEST_LINKAGE inline
#endif /* TEST_STRSIGNAL */

// Longest strsignal message on BSD "Filesize limit exceeded: 25"
#define SIGBUF_LEN 30
#define SIGBUF_UNKNOWN_LEN 19 /* "Unknown signal ###" */

#if HAS_SIGDESCR_NP
// sigdescr_np Solution.
// Preferred due to built in thread safe
TEST_LINKAGE const char* strsignal_sigdescr(int signum)
{
    static thread_local char sigbuf[SIGBUF_UNKNOWN_LEN] = {0};
    // Call sigdescr_np() to get signal string
    const char *buf = sigdescr_np(signum);
    if (buf == NULL) {
        snprintf(sigbuf, sizeof(sigbuf), "Unknown signal %d", signum);
        buf = sigbuf;
    }

    return buf;
}
#endif

#if HAS_STRSIGNAL
// POSIX threadsafe wrapper around strsignal().
#include <pthread.h>


TEST_LINKAGE const char* strsignal_posix(int signum)
{
    // Thread local buffer for signal string.
    static thread_local char sigbuf[SIGBUF_LEN] = {0};
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strsignal() to get signal string
    const char *buf = strsignal(signum);
    // Copy to a thread specific buffer. Always leave null terminator.
    buf = strncpy(sigbuf, buf, sizeof(sigbuf) - 1);
    pthread_mutex_unlock(&mutex);
    return buf;
}
#endif

#if HAS_SYS_SIGLIST
#if defined(TEST_STRSIGNAL) && (__GLIBC__ >= 2 && __GLIBC_MINOR__ >= 32)
// For test purposes, link against sys_siglist, even though it is
// removed from newer versions of glibc. Assembly trickery to make
// this work.
#define SYMVER(s) __asm__(".symver " s)
SYMVER("sys_siglist,sys_siglist@GLIBC_2.3.3");
extern const char * const sys_siglist[];
// glibc 2.3.3 defined NSIG of 65. Make that correct for testing purposes.
#undef NSIG
#define NSIG 65
#endif /* Legacy glibc sys_siglist for testing purposes. */
// GLIBC fallback solution. Used if strsignal() is not available
// at default source, but sys_siglist is.
TEST_LINKAGE const char* strsignal_sys_siglist(int signum)
{
    static thread_local char sigbuf[SIGBUF_UNKNOWN_LEN] = {0};
    // Call sigdescr_np() to get signal string
    const char *buf = NULL;
    if (0 <= signum && signum < NSIG) {
        buf = sys_siglist[signum];
    }

    if (buf == NULL) {
        snprintf(sigbuf, sizeof(sigbuf), "Unknown signal %d", signum);
        buf = sigbuf;
    }

    return buf;
}
#endif

TEST_LINKAGE const char* strsignal_hardcode(int signum)
{
    // ISO C says signal identifiers a MACROS, so they can be individually tested for
    // and enabled.
    switch (signum) {
#ifdef SIGHUP
      case SIGHUP   : return "Hangup";
#endif /* SIGHUP */
#ifdef SIGINT
      case SIGINT   : return "Interrupt";
#endif /* SIGINT */
#ifdef SIGQUIT
      case SIGQUIT  : return "Quit";
#endif /* SIGQUIT */
#ifdef SIGILL
      case SIGILL   : return "Illegal instruction";
#endif /* SIGILL */
#ifdef SIGTRAP
      case SIGTRAP  : return "Trace/breakpoint trap";
#endif /* SIGTRAP */
#ifdef SIGABRT
      case SIGABRT  : return "Aborted";
#endif /* SIGABRT */
#ifdef SIGBUS
      case SIGBUS   : return "Bus error";
#endif /* SIGBUS */
#ifdef SIGFPE
      case SIGFPE   : return "Floating point exception";
#endif /* SIGFPE */
#ifdef SIGKILL
      case SIGKILL  : return "Killed";
#endif /* SIGKILL */
#ifdef SIGUSR1
      case SIGUSR1  : return "User defined signal 1";
#endif /* SIGUSR1 */
#ifdef SIGSEGV
      case SIGSEGV  : return "Segmentation fault";
#endif /* SIGSEGV */
#ifdef SIGUSR2
      case SIGUSR2  : return "User defined signal 2";
#endif /* SIGUSR2 */
#ifdef SIGPIPE
      case SIGPIPE  : return "Broken pipe";
#endif /* SIGPIPE */
#ifdef SIGALRM
      case SIGALRM  : return "Alarm clock";
#endif /* SIGALRM */
#ifdef SIGTERM
      case SIGTERM  : return "Terminated";
#endif /* SIGTERM */
#ifdef SIGSTKFLT
      case SIGSTKFLT: return "Stack fault";
#endif /* SIGSTKFLT */
#ifdef SIGCHLD
      case SIGCHLD  : return "Child exited";
#endif /* SIGCHLD */
#ifdef SIGCONT
      case SIGCONT  : return "Continued";
#endif /* SIGCONT */
#ifdef SIGSTOP
      case SIGSTOP  : return "Stopped (signal)";
#endif /* SIGSTOP */
#ifdef SIGTSTP
      case SIGTSTP  : return "Stopped";
#endif /* SIGTSTP */
#ifdef SIGTTIN
      case SIGTTIN  : return "Stopped (tty input)";
#endif /* SIGTTIN */
#ifdef SIGTTOU
      case SIGTTOU  : return "Stopped (tty output)";
#endif /* SIGTTOU */
#ifdef SIGURG
      case SIGURG   : return "Urgent I/O condition";
#endif /* SIGURG */
#ifdef SIGXCPU
      case SIGXCPU  : return "CPU time limit exceeded";
#endif /* SIGXCPU */
#ifdef SIGXFSZ
      case SIGXFSZ  : return "File size limit exceeded";
#endif /* SIGXFSZ */
#ifdef SIGVTALRM
      case SIGVTALRM: return "Virtual timer expired";
#endif /* SIGVTALRM */
#ifdef SIGPROF
      case SIGPROF  : return "Profiling timer expired";
#endif /* SIGPROF */
#ifdef SIGWINCH
      case SIGWINCH : return "Window changed";
#endif /* SIGWINCH */
#ifdef SIGPOLL
      case SIGPOLL  : return "I/O possible";
#endif /* SIGPOLL */
#ifdef SIGPWR
      case SIGPWR   : return "Power failure";
#endif /* SIGPWR */
#ifdef SIGSYS
      case SIGSYS   : return "Bad system call";
#endif /* SIGSYS */
    }

    static thread_local char sigbuf[SIGBUF_UNKNOWN_LEN] = {0};
    // Format a message for unknown value.
    snprintf(sigbuf, sizeof(sigbuf), "Unknown signal %d", signum);
    return sigbuf;
}

#if !HAS_STRSIGNAL_MT_SAFE
// If strsignal is safe, no need to define anything hear.
const char* strsignal_(int signum)
{
#if HAS_SIGDESCR_NP
    return strsignal_sigdescr(signum);
#elif HAS_STRSIGNAL
    return strsignal_posix(signum);
#elif HAS_SYS_SIGLIST
    return strsignal_sys_siglist(signum);
#else
    return strsignal_hardcode(signum);
#endif
}
#endif /* HAS_STRSIGNAL_MT_SAFE */
