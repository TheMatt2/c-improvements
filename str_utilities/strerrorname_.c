#include "strerrorname_.h"
#include "str_common.h"

#include <errno.h>
#include <stdio.h>


#ifndef TEST_STRSIGNAL
// Allow specific functions to be linkable only if test macro is set.
#define TEST_LINKAGE static
#else
#define TEST_LINKAGE /* nothing */
#endif /* TEST_STRSIGNAL */

// Longest errno name is ENOTRECOVERABLE, EPROTONOSUPPORT, and ESOCKTNOSUPPORT.
#define ERRBUF_LEN 16
// For unknown errno name, just print the number (only concerned about 3 digits).
#define ERRBUF_UNKNOWN_LEN 4

#if HAS_STRERRORNAME_NP
// Use strerrorname_np() to get error name.
TEST_LINKAGE const char* strerrorname_gnu_np(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    // Call strerrorname_np() to get error name
    const char *buf = strerrorname_np(errnum);
    if (buf == NULL) {
        snprintf(errbuf, sizeof(errbuf), "%d", errnum);
        buf = errbuf;
    }
    return buf;
}
#endif /* HAS_STRERRORNAME_NP */

#if HAS_PRINTF_M
// Use printf("%m") to get errno string
// Pedantic warnings warns about usage of %m, but this code already checks
// %m is only used if available.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif /* __GNUC__ */
TEST_LINKAGE const char* strerrorname_printf_m(int errnum)
{
    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_LEN] = {0};
    int prev_errno = errno;
    errno = errnum;

    snprintf(errbuf, sizeof(errbuf), "%#m");
    errno = prev_errno;
    return errbuf;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
#endif /* HAS_PRINTF_M */

// Hardcode solution
TEST_LINKAGE const char* strerrorname_hardcode(int errnum)
{
    // There is no C standard way to get the acronym for the errno
    // errors. However, these are defined by ISO C as macros, so they
    // can be tested for. Some errno macros may have the same value.
#ifdef E2BIG
    if (errnum == E2BIG)           return "E2BIG";
#endif /* E2BIG */
#ifdef EACCES
    if (errnum == EACCES)          return "EACCES";
#endif /* EACCES */
#ifdef EADDRINUSE
    if (errnum == EADDRINUSE)      return "EADDRINUSE";
#endif /* EADDRINUSE */
#ifdef EADDRNOTAVAIL
    if (errnum == EADDRNOTAVAIL)   return "EADDRNOTAVAIL";
#endif /* EADDRNOTAVAIL */
#ifdef EADV
    if (errnum == EADV)            return "EADV";
#endif /* EADV */
#ifdef EAFNOSUPPORT
    if (errnum == EAFNOSUPPORT)    return "EAFNOSUPPORT";
#endif /* EAFNOSUPPORT */
#ifdef EAGAIN
    if (errnum == EAGAIN)          return "EAGAIN";
#endif /* EAGAIN */
#ifdef EALREADY
    if (errnum == EALREADY)        return "EALREADY";
#endif /* EALREADY */
#ifdef EBADE
    if (errnum == EBADE)           return "EBADE";
#endif /* EBADE */
#ifdef EBADF
    if (errnum == EBADF)           return "EBADF";
#endif /* EBADF */
#ifdef EBADFD
    if (errnum == EBADFD)          return "EBADFD";
#endif /* EBADFD */
#ifdef EBADMSG
    if (errnum == EBADMSG)         return "EBADMSG";
#endif /* EBADMSG */
#ifdef EBADR
    if (errnum == EBADR)           return "EBADR";
#endif /* EBADR */
#ifdef EBADRQC
    if (errnum == EBADRQC)         return "EBADRQC";
#endif /* EBADRQC */
#ifdef EBADSLT
    if (errnum == EBADSLT)         return "EBADSLT";
#endif /* EBADSLT */
#ifdef EBFONT
    if (errnum == EBFONT)          return "EBFONT";
#endif /* EBFONT */
#ifdef EBUSY
    if (errnum == EBUSY)           return "EBUSY";
#endif /* EBUSY */
#ifdef ECANCELED
    if (errnum == ECANCELED)       return "ECANCELED";
#endif /* ECANCELED */
#ifdef ECHILD
    if (errnum == ECHILD)          return "ECHILD";
#endif /* ECHILD */
#ifdef ECHRNG
    if (errnum == ECHRNG)          return "ECHRNG";
#endif /* ECHRNG */
#ifdef ECOMM
    if (errnum == ECOMM)           return "ECOMM";
#endif /* ECOMM */
#ifdef ECONNABORTED
    if (errnum == ECONNABORTED)    return "ECONNABORTED";
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
    if (errnum == ECONNREFUSED)    return "ECONNREFUSED";
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
    if (errnum == ECONNRESET)      return "ECONNRESET";
#endif /* ECONNRESET */
#ifdef EDEADLK
    if (errnum == EDEADLK)         return "EDEADLK";
#endif /* EDEADLK */
#ifdef EDEADLOCK
    if (errnum == EDEADLOCK)       return "EDEADLOCK";
#endif /* EDEADLOCK */
#ifdef EDESTADDRREQ
    if (errnum == EDESTADDRREQ)    return "EDESTADDRREQ";
#endif /* EDESTADDRREQ */
#ifdef EDOM
    if (errnum == EDOM)            return "EDOM";
#endif /* EDOM */
#ifdef EDOTDOT
    if (errnum == EDOTDOT)         return "EDOTDOT";
#endif /* EDOTDOT */
#ifdef EDQUOT
    if (errnum == EDQUOT)          return "EDQUOT";
#endif /* EDQUOT */
#ifdef EEXIST
    if (errnum == EEXIST)          return "EEXIST";
#endif /* EEXIST */
#ifdef EFAULT
    if (errnum == EFAULT)          return "EFAULT";
#endif /* EFAULT */
#ifdef EFBIG
    if (errnum == EFBIG)           return "EFBIG";
#endif /* EFBIG */
#ifdef EHOSTDOWN
    if (errnum == EHOSTDOWN)       return "EHOSTDOWN";
#endif /* EHOSTDOWN */
#ifdef EHOSTUNREACH
    if (errnum == EHOSTUNREACH)    return "EHOSTUNREACH";
#endif /* EHOSTUNREACH */
#ifdef EHWPOISON
    if (errnum == EHWPOISON)       return "EHWPOISON";
#endif /* EHWPOISON */
#ifdef EIDRM
    if (errnum == EIDRM)           return "EIDRM";
#endif /* EIDRM */
#ifdef EILSEQ
    if (errnum == EILSEQ)          return "EILSEQ";
#endif /* EILSEQ */
#ifdef EINPROGRESS
    if (errnum == EINPROGRESS)     return "EINPROGRESS";
#endif /* EINPROGRESS */
#ifdef EINTR
    if (errnum == EINTR)           return "EINTR";
#endif /* EINTR */
#ifdef EINVAL
    if (errnum == EINVAL)          return "EINVAL";
#endif /* EINVAL */
#ifdef EIO
    if (errnum == EIO)             return "EIO";
#endif /* EIO */
#ifdef EISCONN
    if (errnum == EISCONN)         return "EISCONN";
#endif /* EISCONN */
#ifdef EISDIR
    if (errnum == EISDIR)          return "EISDIR";
#endif /* EISDIR */
#ifdef EISNAM
    if (errnum == EISNAM)          return "EISNAM";
#endif /* EISNAM */
#ifdef EKEYEXPIRED
    if (errnum == EKEYEXPIRED)     return "EKEYEXPIRED";
#endif /* EKEYEXPIRED */
#ifdef EKEYREJECTED
    if (errnum == EKEYREJECTED)    return "EKEYREJECTED";
#endif /* EKEYREJECTED */
#ifdef EKEYREVOKED
    if (errnum == EKEYREVOKED)     return "EKEYREVOKED";
#endif /* EKEYREVOKED */
#ifdef EL2HLT
    if (errnum == EL2HLT)          return "EL2HLT";
#endif /* EL2HLT */
#ifdef EL2NSYNC
    if (errnum == EL2NSYNC)        return "EL2NSYNC";
#endif /* EL2NSYNC */
#ifdef EL3HLT
    if (errnum == EL3HLT)          return "EL3HLT";
#endif /* EL3HLT */
#ifdef EL3RST
    if (errnum == EL3RST)          return "EL3RST";
#endif /* EL3RST */
#ifdef ELIBACC
    if (errnum == ELIBACC)         return "ELIBACC";
#endif /* ELIBACC */
#ifdef ELIBBAD
    if (errnum == ELIBBAD)         return "ELIBBAD";
#endif /* ELIBBAD */
#ifdef ELIBEXEC
    if (errnum == ELIBEXEC)        return "ELIBEXEC";
#endif /* ELIBEXEC */
#ifdef ELIBMAX
    if (errnum == ELIBMAX)         return "ELIBMAX";
#endif /* ELIBMAX */
#ifdef ELIBSCN
    if (errnum == ELIBSCN)         return "ELIBSCN";
#endif /* ELIBSCN */
#ifdef ELNRNG
    if (errnum == ELNRNG)          return "ELNRNG";
#endif /* ELNRNG */
#ifdef ELOOP
    if (errnum == ELOOP)           return "ELOOP";
#endif /* ELOOP */
#ifdef EMEDIUMTYPE
    if (errnum == EMEDIUMTYPE)     return "EMEDIUMTYPE";
#endif /* EMEDIUMTYPE */
#ifdef EMFILE
    if (errnum == EMFILE)          return "EMFILE";
#endif /* EMFILE */
#ifdef EMLINK
    if (errnum == EMLINK)          return "EMLINK";
#endif /* EMLINK */
#ifdef EMSGSIZE
    if (errnum == EMSGSIZE)        return "EMSGSIZE";
#endif /* EMSGSIZE */
#ifdef EMULTIHOP
    if (errnum == EMULTIHOP)       return "EMULTIHOP";
#endif /* EMULTIHOP */
#ifdef ENAMETOOLONG
    if (errnum == ENAMETOOLONG)    return "ENAMETOOLONG";
#endif /* ENAMETOOLONG */
#ifdef ENAVAIL
    if (errnum == ENAVAIL)         return "ENAVAIL";
#endif /* ENAVAIL */
#ifdef ENETDOWN
    if (errnum == ENETDOWN)        return "ENETDOWN";
#endif /* ENETDOWN */
#ifdef ENETRESET
    if (errnum == ENETRESET)       return "ENETRESET";
#endif /* ENETRESET */
#ifdef ENETUNREACH
    if (errnum == ENETUNREACH)     return "ENETUNREACH";
#endif /* ENETUNREACH */
#ifdef ENFILE
    if (errnum == ENFILE)          return "ENFILE";
#endif /* ENFILE */
#ifdef ENOANO
    if (errnum == ENOANO)          return "ENOANO";
#endif /* ENOANO */
#ifdef ENOBUFS
    if (errnum == ENOBUFS)         return "ENOBUFS";
#endif /* ENOBUFS */
#ifdef ENOCSI
    if (errnum == ENOCSI)          return "ENOCSI";
#endif /* ENOCSI */
#ifdef ENODATA
    if (errnum == ENODATA)         return "ENODATA";
#endif /* ENODATA */
#ifdef ENODEV
    if (errnum == ENODEV)          return "ENODEV";
#endif /* ENODEV */
#ifdef ENOENT
    if (errnum == ENOENT)          return "ENOENT";
#endif /* ENOENT */
#ifdef ENOEXEC
    if (errnum == ENOEXEC)         return "ENOEXEC";
#endif /* ENOEXEC */
#ifdef ENOKEY
    if (errnum == ENOKEY)          return "ENOKEY";
#endif /* ENOKEY */
#ifdef ENOLCK
    if (errnum == ENOLCK)          return "ENOLCK";
#endif /* ENOLCK */
#ifdef ENOLINK
    if (errnum == ENOLINK)         return "ENOLINK";
#endif /* ENOLINK */
#ifdef ENOMEDIUM
    if (errnum == ENOMEDIUM)       return "ENOMEDIUM";
#endif /* ENOMEDIUM */
#ifdef ENOMEM
    if (errnum == ENOMEM)          return "ENOMEM";
#endif /* ENOMEM */
#ifdef ENOMSG
    if (errnum == ENOMSG)          return "ENOMSG";
#endif /* ENOMSG */
#ifdef ENONET
    if (errnum == ENONET)          return "ENONET";
#endif /* ENONET */
#ifdef ENOPKG
    if (errnum == ENOPKG)          return "ENOPKG";
#endif /* ENOPKG */
#ifdef ENOPROTOOPT
    if (errnum == ENOPROTOOPT)     return "ENOPROTOOPT";
#endif /* ENOPROTOOPT */
#ifdef ENOSPC
    if (errnum == ENOSPC)          return "ENOSPC";
#endif /* ENOSPC */
#ifdef ENOSR
    if (errnum == ENOSR)           return "ENOSR";
#endif /* ENOSR */
#ifdef ENOSTR
    if (errnum == ENOSTR)          return "ENOSTR";
#endif /* ENOSTR */
#ifdef ENOSYS
    if (errnum == ENOSYS)          return "ENOSYS";
#endif /* ENOSYS */
#ifdef ENOTBLK
    if (errnum == ENOTBLK)         return "ENOTBLK";
#endif /* ENOTBLK */
#ifdef ENOTCONN
    if (errnum == ENOTCONN)        return "ENOTCONN";
#endif /* ENOTCONN */
#ifdef ENOTDIR
    if (errnum == ENOTDIR)         return "ENOTDIR";
#endif /* ENOTDIR */
#ifdef ENOTEMPTY
    if (errnum == ENOTEMPTY)       return "ENOTEMPTY";
#endif /* ENOTEMPTY */
#ifdef ENOTNAM
    if (errnum == ENOTNAM)         return "ENOTNAM";
#endif /* ENOTNAM */
#ifdef ENOTRECOVERABLE
    if (errnum == ENOTRECOVERABLE) return "ENOTRECOVERABLE";
#endif /* ENOTRECOVERABLE */
#ifdef ENOTSOCK
    if (errnum == ENOTSOCK)        return "ENOTSOCK";
#endif /* ENOTSOCK */
#ifdef ENOTSUP
    if (errnum == ENOTSUP)         return "ENOTSUP";
#endif /* ENOTSUP */
#ifdef ENOTTY
    if (errnum == ENOTTY)          return "ENOTTY";
#endif /* ENOTTY */
#ifdef ENOTUNIQ
    if (errnum == ENOTUNIQ)        return "ENOTUNIQ";
#endif /* ENOTUNIQ */
#ifdef ENXIO
    if (errnum == ENXIO)           return "ENXIO";
#endif /* ENXIO */
#ifdef EOPNOTSUPP
    if (errnum == EOPNOTSUPP)      return "EOPNOTSUPP";
#endif /* EOPNOTSUPP */
#ifdef EOVERFLOW
    if (errnum == EOVERFLOW)       return "EOVERFLOW";
#endif /* EOVERFLOW */
#ifdef EOWNERDEAD
    if (errnum == EOWNERDEAD)      return "EOWNERDEAD";
#endif /* EOWNERDEAD */
#ifdef EPERM
    if (errnum == EPERM)           return "EPERM";
#endif /* EPERM */
#ifdef EPFNOSUPPORT
    if (errnum == EPFNOSUPPORT)    return "EPFNOSUPPORT";
#endif /* EPFNOSUPPORT */
#ifdef EPIPE
    if (errnum == EPIPE)           return "EPIPE";
#endif /* EPIPE */
#ifdef EPROTO
    if (errnum == EPROTO)          return "EPROTO";
#endif /* EPROTO */
#ifdef EPROTONOSUPPORT
    if (errnum == EPROTONOSUPPORT) return "EPROTONOSUPPORT";
#endif /* EPROTONOSUPPORT */
#ifdef EPROTOTYPE
    if (errnum == EPROTOTYPE)      return "EPROTOTYPE";
#endif /* EPROTOTYPE */
#ifdef ERANGE
    if (errnum == ERANGE)          return "ERANGE";
#endif /* ERANGE */
#ifdef EREMCHG
    if (errnum == EREMCHG)         return "EREMCHG";
#endif /* EREMCHG */
#ifdef EREMOTE
    if (errnum == EREMOTE)         return "EREMOTE";
#endif /* EREMOTE */
#ifdef EREMOTEIO
    if (errnum == EREMOTEIO)       return "EREMOTEIO";
#endif /* EREMOTEIO */
#ifdef ERESTART
    if (errnum == ERESTART)        return "ERESTART";
#endif /* ERESTART */
#ifdef ERFKILL
    if (errnum == ERFKILL)         return "ERFKILL";
#endif /* ERFKILL */
#ifdef EROFS
    if (errnum == EROFS)           return "EROFS";
#endif /* EROFS */
#ifdef ESHUTDOWN
    if (errnum == ESHUTDOWN)       return "ESHUTDOWN";
#endif /* ESHUTDOWN */
#ifdef ESOCKTNOSUPPORT
    if (errnum == ESOCKTNOSUPPORT) return "ESOCKTNOSUPPORT";
#endif /* ESOCKTNOSUPPORT */
#ifdef ESPIPE
    if (errnum == ESPIPE)          return "ESPIPE";
#endif /* ESPIPE */
#ifdef ESRCH
    if (errnum == ESRCH)           return "ESRCH";
#endif /* ESRCH */
#ifdef ESRMNT
    if (errnum == ESRMNT)          return "ESRMNT";
#endif /* ESRMNT */
#ifdef ESTALE
    if (errnum == ESTALE)          return "ESTALE";
#endif /* ESTALE */
#ifdef ESTRPIPE
    if (errnum == ESTRPIPE)        return "ESTRPIPE";
#endif /* ESTRPIPE */
#ifdef ETIME
    if (errnum == ETIME)           return "ETIME";
#endif /* ETIME */
#ifdef ETIMEDOUT
    if (errnum == ETIMEDOUT)       return "ETIMEDOUT";
#endif /* ETIMEDOUT */
#ifdef ETOOMANYREFS
    if (errnum == ETOOMANYREFS)    return "ETOOMANYREFS";
#endif /* ETOOMANYREFS */
#ifdef ETXTBSY
    if (errnum == ETXTBSY)         return "ETXTBSY";
#endif /* ETXTBSY */
#ifdef EUCLEAN
    if (errnum == EUCLEAN)         return "EUCLEAN";
#endif /* EUCLEAN */
#ifdef EUNATCH
    if (errnum == EUNATCH)         return "EUNATCH";
#endif /* EUNATCH */
#ifdef EUSERS
    if (errnum == EUSERS)          return "EUSERS";
#endif /* EUSERS */
#ifdef EWOULDBLOCK
    if (errnum == EWOULDBLOCK)     return "EWOULDBLOCK";
#endif /* EWOULDBLOCK */
#ifdef EXDEV
    if (errnum == EXDEV)           return "EXDEV";
#endif /* EXDEV */
#ifdef EXFULL
    if (errnum == EXFULL)          return "EXFULL";
#endif /* EXFULL */

    // Thread local buffer for errors.
    static thread_local char errbuf[ERRBUF_UNKNOWN_LEN] = {0};
    // Format a message of unknown value.
    snprintf(errbuf, sizeof(errbuf), "%d", errnum);
    return errbuf;
}

const char* strerrorname_(int errnum)
{
#if HAS_STRERRORNAME_NP
    return strerrorname_gnu_np(errnum);
#elif HAS_PRINTF_M
    return strerrorname_printf_m(errnum);
#else
    return strerrorname_hardcode(errnum);
#endif
}
