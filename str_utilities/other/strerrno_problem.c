// http://www.club.cc.cmu.edu/~cmccabe/blog_strerror.html
// gcc -Wall -std=c11 -g ./strerrno_problem.c
// #define _GNU_SOURCE
#define _POSIX_C_SOURCE 200812L

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <threads.h>
#include <stdbool.h>
#include <locale.h>

// #define MAX(a, b) (a) > (b) ? (a) : (b)
#define MAX(a,b) ({ \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; \
})

#define XSTR(x) STR(x)
#define STR(x) #x

// sys_nerr, sys_errlist
// Deprecated from glibc 2.19 to glib 2.31
// Removed after glib 2.31
#if ! defined(HAS_SYS_ERRLIST) && \
     defined(__GLIBC__) && defined(__GLIBC_MINOR__) && \
     __GLIBC__ <= 2 && __GLIBC_MINOR__ <= 31
#define HAS_SYS_ERRLIST
#endif

#if ! defined(HAS_STRERROR_NP) && defined(_GNU_SOURCE)
#define HAS_STRERROR_NP
#endif

void strerror_r_improved(int err, char *str, size_t str_len)
{
#ifdef HAS_SYS_ERRLIST
    if (0 <= err && err < sys_nerr)
        snprintf(str, str_len, "%s", sys_errlist[err]);
    else
        snprintf(str, str_len, "Unknown error: %d", err);
#else
    if (str_len != 0) str[0] = '\0';
#endif /* HAS_SYS_ERRLIST */
}

// glibc and XSI disagree on the signature of strerror_r()!
const char* strerror_r_np(int errnum)
{
    static _Thread_local char err_buf[60];

    // (from man page) The XSI-compliant version is provided if:
#if (_POSIX_C_SOURCE >= 200112L) && ! defined(_GNU_SOURCE)
#pragma message "_POSIX_C_SOURCE " XSTR(_POSIX_C_SOURCE)
    // int strerror_r(int errnum, char buf[.buflen], size_t buflen)
    strerror_r(errnum, err_buf, sizeof(err_buf));
    return err_buf;
#else
#ifdef _GNU_SOURCE
    // char *strerror_r(int errnum, char buf[.buflen], size_t buflen);
    return strerror_r(errnum, err_buf, sizeof(err_buf));
#endif /* _GNU_SOURCE */
#endif
    (void) err_buf;
    return "(no support)";
}

#ifdef HAS_SYS_ERRLIST
const static int SYSNERR = sysnerr;
#else
const static int SYSNERR = 150;
#endif

const char* strerror_s(int err)
{
    if (err == E2BIG)           return "E2BIG";
    if (err == EACCES)          return "EACCES";
    if (err == EADDRINUSE)      return "EADDRINUSE";
    if (err == EADDRNOTAVAIL)   return "EADDRNOTAVAIL";
    if (err == EAFNOSUPPORT)    return "EAFNOSUPPORT";
    if (err == EAGAIN)          return "EAGAIN";
    if (err == EALREADY)        return "EALREADY";
    if (err == EBADE)           return "EBADE";
    if (err == EBADF)           return "EBADF";
    if (err == EBADFD)          return "EBADFD";
    if (err == EBADMSG)         return "EBADMSG";
    if (err == EBADR)           return "EBADR";
    if (err == EBADRQC)         return "EBADRQC";
    if (err == EBADSLT)         return "EBADSLT";
    if (err == EBUSY)           return "EBUSY";
    if (err == ECANCELED)       return "ECANCELED";
    if (err == ECHILD)          return "ECHILD";
    if (err == ECHRNG)          return "ECHRNG";
    if (err == ECOMM)           return "ECOMM";
    if (err == ECONNABORTED)    return "ECONNABORTED";
    if (err == ECONNREFUSED)    return "ECONNREFUSED";
    if (err == ECONNRESET)      return "ECONNRESET";
    if (err == EDEADLK)         return "EDEADLK";
    if (err == EDEADLOCK)       return "EDEADLOCK";
    if (err == EDESTADDRREQ)    return "EDESTADDRREQ";
    if (err == EDOM)            return "EDOM";
    if (err == EDQUOT)          return "EDQUOT";
    if (err == EEXIST)          return "EEXIST";
    if (err == EFAULT)          return "EFAULT";
    if (err == EFBIG)           return "EFBIG";
    if (err == EHOSTDOWN)       return "EHOSTDOWN";
    if (err == EHOSTUNREACH)    return "EHOSTUNREACH";
    if (err == EHWPOISON)       return "EHWPOISON";
    if (err == EIDRM)           return "EIDRM";
    if (err == EILSEQ)          return "EILSEQ";
    if (err == EINPROGRESS)     return "EINPROGRESS";
    if (err == EINTR)           return "EINTR";
    if (err == EINVAL)          return "EINVAL";
    if (err == EIO)             return "EIO";
    if (err == EISCONN)         return "EISCONN";
    if (err == EISDIR)          return "EISDIR";
    if (err == EISNAM)          return "EISNAM";
    if (err == EKEYEXPIRED)     return "EKEYEXPIRED";
    if (err == EKEYREJECTED)    return "EKEYREJECTED";
    if (err == EKEYREVOKED)     return "EKEYREVOKED";
    if (err == EL2HLT)          return "EL2HLT";
    if (err == EL2NSYNC)        return "EL2NSYNC";
    if (err == EL3HLT)          return "EL3HLT";
    if (err == EL3RST)          return "EL3RST";
    if (err == ELIBACC)         return "ELIBACC";
    if (err == ELIBBAD)         return "ELIBBAD";
    if (err == ELIBMAX)         return "ELIBMAX";
    if (err == ELIBSCN)         return "ELIBSCN";
    if (err == ELIBEXEC)        return "ELIBEXEC";
    if (err == ELNRNG)          return "ELNRNG";
    if (err == ELOOP)           return "ELOOP";
    if (err == EMEDIUMTYPE)     return "EMEDIUMTYPE";
    if (err == EMFILE)          return "EMFILE";
    if (err == EMLINK)          return "EMLINK";
    if (err == EMSGSIZE)        return "EMSGSIZE";
    if (err == EMULTIHOP)       return "EMULTIHOP";
    if (err == ENAMETOOLONG)    return "ENAMETOOLONG";
    if (err == ENETDOWN)        return "ENETDOWN";
    if (err == ENETRESET)       return "ENETRESET";
    if (err == ENETUNREACH)     return "ENETUNREACH";
    if (err == ENFILE)          return "ENFILE";
    if (err == ENOANO)          return "ENOANO";
    if (err == ENOBUFS)         return "ENOBUFS";
    if (err == ENODATA)         return "ENODATA";
    if (err == ENODEV)          return "ENODEV";
    if (err == ENOENT)          return "ENOENT";
    if (err == ENOEXEC)         return "ENOEXEC";
    if (err == ENOKEY)          return "ENOKEY";
    if (err == ENOLCK)          return "ENOLCK";
    if (err == ENOLINK)         return "ENOLINK";
    if (err == ENOMEDIUM)       return "ENOMEDIUM";
    if (err == ENOMEM)          return "ENOMEM";
    if (err == ENOMSG)          return "ENOMSG";
    if (err == ENONET)          return "ENONET";
    if (err == ENOPKG)          return "ENOPKG";
    if (err == ENOPROTOOPT)     return "ENOPROTOOPT";
    if (err == ENOSPC)          return "ENOSPC";
    if (err == ENOSR)           return "ENOSR";
    if (err == ENOSTR)          return "ENOSTR";
    if (err == ENOSYS)          return "ENOSYS";
    if (err == ENOTBLK)         return "ENOTBLK";
    if (err == ENOTCONN)        return "ENOTCONN";
    if (err == ENOTDIR)         return "ENOTDIR";
    if (err == ENOTEMPTY)       return "ENOTEMPTY";
    if (err == ENOTRECOVERABLE) return "ENOTRECOVERABLE";
    if (err == ENOTSOCK)        return "ENOTSOCK";
    if (err == ENOTSUP)         return "ENOTSUP";
    if (err == ENOTTY)          return "ENOTTY";
    if (err == ENOTUNIQ)        return "ENOTUNIQ";
    if (err == ENXIO)           return "ENXIO";
    if (err == EOPNOTSUPP)      return "EOPNOTSUPP";
    if (err == EOVERFLOW)       return "EOVERFLOW";
    if (err == EOWNERDEAD)      return "EOWNERDEAD";
    if (err == EPERM)           return "EPERM";
    if (err == EPFNOSUPPORT)    return "EPFNOSUPPORT";
    if (err == EPIPE)           return "EPIPE";
    if (err == EPROTO)          return "EPROTO";
    if (err == EPROTONOSUPPORT) return "EPROTONOSUPPORT";
    if (err == EPROTOTYPE)      return "EPROTOTYPE";
    if (err == ERANGE)          return "ERANGE";
    if (err == EREMCHG)         return "EREMCHG";
    if (err == EREMOTE)         return "EREMOTE";
    if (err == EREMOTEIO)       return "EREMOTEIO";
    if (err == ERESTART)        return "ERESTART";
    if (err == ERFKILL)         return "ERFKILL";
    if (err == EROFS)           return "EROFS";
    if (err == ESHUTDOWN)       return "ESHUTDOWN";
    if (err == ESPIPE)          return "ESPIPE";
    if (err == ESOCKTNOSUPPORT) return "ESOCKTNOSUPPORT";
    if (err == ESRCH)           return "ESRCH";
    if (err == ESTALE)          return "ESTALE";
    if (err == ESTRPIPE)        return "ESTRPIPE";
    if (err == ETIME)           return "ETIME";
    if (err == ETIMEDOUT)       return "ETIMEDOUT";
    if (err == ETOOMANYREFS)    return "ETOOMANYREFS";
    if (err == ETXTBSY)         return "ETXTBSY";
    if (err == EUCLEAN)         return "EUCLEAN";
    if (err == EUNATCH)         return "EUNATCH";
    if (err == EUSERS)          return "EUSERS";
    if (err == EWOULDBLOCK)     return "EWOULDBLOCK";
    if (err == EXDEV)           return "EXDEV";
    if (err == EXFULL)          return "EXFULL";

    // else
    static _Thread_local char errno_msg[22];
    snprintf(errno_msg, sizeof(errno_msg), "Unknown error: %d", err);
    return errno_msg;
}

#define HAS_STRERROR_L
// #define HAS_USELOCALE

// From https://github.com/tavianator/bfs/blob/c1ac8a73589f9d27704e6bd8f99d0c42fac2100f/src/bfstd.c#L322C1-L364C2
const char* strerror_(int errnum) {
    int saved = errno;
    const char *ret = NULL;
    static thread_local char buf[256];

    // On FreeBSD with MemorySanitizer, duplocale() triggers
    // https://github.com/llvm/llvm-project/issues/65532
#if defined(HAS_STRERROR_L) && !(__FreeBSD__ && __SANITIZE_MEMORY__)
#if defined(HAS_USELOCALE)
    locale_t loc = uselocale((locale_t)0);
#else
    locale_t loc = LC_GLOBAL_LOCALE;
#endif

    bool free_loc = false;
    if (loc == LC_GLOBAL_LOCALE) {
        loc = duplocale(loc);
        free_loc = true;
    }

    if (loc != (locale_t)0) {
        ret = strerror_l(errnum, loc);
        if (free_loc) {
            freelocale(loc);
        }
    }
#elif HAS_STRERROR_R_POSIX
    if (strerror_r(errnum, buf, sizeof(buf)) == 0) {
        ret = buf;
    }
#elif HAS_STRERROR_R_GNU
    ret = strerror_r(errnum, buf, sizeof(buf));
#endif

    if (!ret) {
        // Fallback for strerror_[lr]() or duplocale() failures
        snprintf(buf, sizeof(buf), "Unknown error %d", errnum);
        ret = buf;
    }

    errno = saved;
    return ret;
}

int main()
{
    const char *sts_buf;
    const char *stn_buf;
    const char *ste_buf;
    const char *str_buf;
    char srl_buf[100];
    const char *std_buf;
    const char *sti_buf;
    char spf_buf[100];

    // Track max length of error message
    size_t sts_maxlen = 0;
    size_t stn_maxlen = 0;
    size_t ste_maxlen = 0;
    size_t str_maxlen = 0;
    size_t stl_maxlen = 0;
    size_t std_maxlen = 0;

#ifdef HAS_SYS_ERRLIST
    printf("### %-20s %-50s %-50s %s\n", "strerror_s", "strerror", "strerror_r", "sys_errlist");
#else
#ifndef HAS_STRERROR_NP
    printf("### %-20s %-50s %-50s %s\n", "strerror_s", "strerror", "strerror_r", "printf(\"%m\")");
#else
    printf("### %-20s %-20s %-50s %-50s %-50s %s\n", "strerror_s", "strerrorname_np", "strerror", "strerror_r", "strerrordesc_np", "strerror_l");
#endif /* HAS_STRERROR_NP */
#endif /* HAS_SYS_ERRLIST */

    for (int i = 0; i < SYSNERR + 5; i++) {
        // strerror_s
        sts_buf = strerror_s(i);
        sts_maxlen = MAX(sts_maxlen, strlen(sts_buf));

#ifdef HAS_STRERROR_NP
        // strerrorname_np
        stn_buf = strerrorname_np(i);
        if (!stn_buf) stn_buf = "(null)";
        stn_maxlen = MAX(stn_maxlen, strlen(stn_buf));
#else
        (void) stn_buf;
#endif /* HAS_STRERROR_NP */

        // strerror
        ste_buf = strerror(i);
        ste_maxlen = MAX(ste_maxlen, strlen(ste_buf));

        // strerror_r
        str_buf = strerror_r_np(i);
        str_maxlen = MAX(str_maxlen, strlen(str_buf));

        // strerror_r_improved
        strerror_r_improved(i, srl_buf, sizeof(srl_buf));
        stl_maxlen = MAX(stl_maxlen, strlen(srl_buf));

#ifdef HAS_STRERROR_NP
        // strerrordesc_np
        std_buf = strerrordesc_np(i);
        if (!std_buf) std_buf = "(null)";
        std_maxlen = MAX(std_maxlen, strlen(std_buf));
#else
        (void) std_buf;
#endif /* HAS_STRERROR_NP */

        // strerror_l
        sti_buf = strerror_(i);
        (void) sti_buf;

        // printf("%m")
        errno = i;
        snprintf(spf_buf, sizeof(spf_buf), "%m");

        // only print if they differ
#ifdef HAS_SYS_ERRLIST
        printf("%3d %-20s %-50s %-50s %s\n", i, sts_buf, ste_buf, str_buf, srl_buf);
#else
#ifndef HAS_STRERROR_NP
        printf("%3d %-20s %-50s %-50s %s\n", i, sts_buf, ste_buf, str_buf, spf_buf);
#else
        printf("%3d %-20s %-20s %-50s %-50s %-50s %s\n", i, sts_buf, stn_buf, ste_buf, str_buf, std_buf, sti_buf);
#endif /* HAS_STRERROR_NP */
#endif /* HAS_SYS_ERRLIST */
    }

    printf("\nError Messages Max Lengths\n");
#ifdef HAS_SYS_ERRLIST
    printf("### %-20zu %-50zu %-50zu %zu\n", sts_maxlen, ste_maxlen, str_maxlen, stl_maxlen);
#else
    printf("### %-20zu %-20zu %-50zu %-50zu %zu\n", sts_maxlen, stn_maxlen, ste_maxlen, str_maxlen, std_maxlen);
#endif /* HAS_SYS_ERRLIST */

    return 0;
}
