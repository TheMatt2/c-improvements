#include "strsignalname_.h"
#include "str_common.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>


#define SIGNAME_LEN 10

#if HAS_SIGABBREV_NP
LOCAL_LINKAGE const char* strsignalname_sigabbrev_np(int signum) {
    // Thread local buffer for signal.
    static thread_local char sigbuf[SIGNAME_LEN] = {0};
    // Get signal name
    const char *buf = sigabbrev_np(signum);
    if (buf != NULL) {
        snprintf(sigbuf, sizeof(sigbuf), "SIG%s", buf);
    } else {
        snprintf(sigbuf, sizeof(sigbuf), "Signal %d", signum);
    }
    return sigbuf;
}
#endif /* HAS_SIGABBREV_NP */

#if HAS_SYS_SIGNAME
static inline void uppercase(char *str, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\0') break;
        str[i] = toupper(str[i]);
    }
}

LOCAL_LINKAGE const char* strsignalname_sys_signame(int signum) {
    // Thread local buffer for signal.
    static thread_local char sigbuf[SIGNAME_LEN] = {0};
    const char *buf = NULL;
    // Check if signum is in array. Assumes 0 is not a valid signal.
    if (0 < signum && signum < NSIG) {
        buf = sys_signame[signum];
    }
    // Check if signum name is in list.
    if (buf != NULL) {
        snprintf(sigbuf, sizeof(sigbuf), "SIG%s", buf);
        // Convert to uppercase
        uppercase(&sigbuf[3], SIGNAME_LEN - 3);
    } else {
        snprintf(sigbuf, sizeof(sigbuf), "Signal %d", signum);
    }
    return sigbuf;
}
#endif /* HAS_SYS_SIGNAME */

// Hardcode solution
static const char *sysnamelist[] = {
#ifdef SIGABRT
    [ SIGABRT ] = "ABRT",
#endif /* SIGABRT */
#ifdef SIGALRM
    [ SIGALRM ] = "ALRM",
#endif /* SIGALRM */
#ifdef SIGBUS
    [ SIGBUS ] = "BUS",
#endif /* SIGBUS */
#ifdef SIGCHLD
    [ SIGCHLD ] = "CHLD",
#endif /* SIGCHLD */
#ifdef SIGCONT
    [ SIGCONT ] = "CONT",
#endif /* SIGCONT */
#ifdef SIGEMT
    [ SIGEMT ] = "EMT",
#endif /* SIGEMT */
#ifdef SIGFPE
    [ SIGFPE ] = "FPE",
#endif /* SIGFPE */
#ifdef SIGHUP
    [ SIGHUP ] = "HUP",
#endif /* SIGHUP */
#ifdef SIGILL
    [ SIGILL ] = "ILL",
#endif /* SIGILL */
#ifdef SIGINFO
    [ SIGINFO ] = "INFO",
#endif /* SIGINFO */
#ifdef SIGINT
    [ SIGINT ] = "INT",
#endif /* SIGINT */
#ifdef SIGIO
    [ SIGIO ] = "IO",
#endif /* SIGIO */
#ifdef SIGKILL
    [ SIGKILL ] = "KILL",
#endif /* SIGKILL */
#ifdef SIGPIPE
    [ SIGPIPE ] = "PIPE",
#endif /* SIGPIPE */
#ifdef SIGPOLL
    [ SIGPOLL ] = "POLL",
#endif /* SIGPOLL */
#ifdef SIGPROF
    [ SIGPROF ] = "PROF",
#endif /* SIGPROF */
#ifdef SIGPWR
    [ SIGPWR ] = "PWR",
#endif /* SIGPWR */
#ifdef SIGQUIT
    [ SIGQUIT ] = "QUIT",
#endif /* SIGQUIT */
#ifdef SIGSEGV
    [ SIGSEGV ] = "SEGV",
#endif /* SIGSEGV */
#ifdef SIGSTKFLT
    [ SIGSTKFLT ] = "STKFLT",
#endif /* SIGSTKFLT */
#ifdef SIGSTOP
    [ SIGSTOP ] = "STOP",
#endif /* SIGSTOP */
#ifdef SIGSYS
    [ SIGSYS ] = "SYS",
#endif /* SIGSYS */
#ifdef SIGTERM
    [ SIGTERM ] = "TERM",
#endif /* SIGTERM */
#ifdef SIGTRAP
    [ SIGTRAP ] = "TRAP",
#endif /* SIGTRAP */
#ifdef SIGTSTP
    [ SIGTSTP ] = "TSTP",
#endif /* SIGTSTP */
#ifdef SIGTTIN
    [ SIGTTIN ] = "TTIN",
#endif /* SIGTTIN */
#ifdef SIGTTOU
    [ SIGTTOU ] = "TTOU",
#endif /* SIGTTOU */
#ifdef SIGURG
    [ SIGURG ] = "URG",
#endif /* SIGURG */
#ifdef SIGUSR1
    [ SIGUSR1 ] = "USR1",
#endif /* SIGUSR1 */
#ifdef SIGUSR2
    [ SIGUSR2 ] = "USR2",
#endif /* SIGUSR2 */
#ifdef SIGVTALRM
    [ SIGVTALRM ] = "VTALRM",
#endif /* SIGVTALRM */
#ifdef SIGWINCH
    [ SIGWINCH ] = "WINCH",
#endif /* SIGWINCH */
#ifdef SIGXCPU
    [ SIGXCPU ] = "XCPU",
#endif /* SIGXCPU */
#ifdef SIGXFSZ
    [ SIGXFSZ ] = "XFSZ",
#endif /* SIGXFSZ */
};

#define SYSNAMELIST_LEN ARRAY_SIZE(sysnamelist)

LOCAL_LINKAGE const char* strsignalname_hardcode(int signum) {
    // Thread local buffer for signal.
    static thread_local char sigbuf[SIGNAME_LEN] = {0};
    const char *buf = NULL;
    // Check if signum name is in list.
    if (0 <= signum && signum < SYSNAMELIST_LEN) {
        buf = sysnamelist[signum];
    }
    // Format signal if name found.
    if (buf != NULL) {
        snprintf(sigbuf, sizeof(sigbuf), "SIG%s", buf);
    } else {
        snprintf(sigbuf, sizeof(sigbuf), "Signal %d", signum);
    }
    return sigbuf;
}

const char* strsignalname_(int signum) {
    // Void reference to suppress unused warnings.
#if HAS_SIGABBREV_NP
    (void) strsignalname_sigabbrev_np;
#endif
#if HAS_SYS_SIGNAME
    (void) strsignalname_sys_signame;
#endif
    (void) strsignalname_hardcode;

#if HAS_SIGABBREV_NP
    return strsignalname_sigabbrev_np(signum);
#elif HAS_SYS_SIGNAME
    return strsignalname_sys_signame(signum);
#else
    return strsignalname_hardcode(signum);
#endif
}
