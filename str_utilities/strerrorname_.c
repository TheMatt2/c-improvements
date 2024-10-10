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

/*
 * Prefer EDEADLK to EDEADLOCK
 * Prefer EOPNOTSUPP to ENOTSUP
 * Prefer EAGAIN to EWOULDBLOCK
 */
static const char* errnamelist[] = {
#ifdef E2BIG
    [ E2BIG ]            = "E2BIG",
#endif /* E2BIG */
#ifdef EACCES
    [ EACCES ]           = "EACCES",
#endif /* EACCES */
#ifdef EADDRINUSE
    [ EADDRINUSE ]       = "EADDRINUSE",
#endif /* EADDRINUSE */
#ifdef EADDRNOTAVAIL
    [ EADDRNOTAVAIL ]    = "EADDRNOTAVAIL",
#endif /* EADDRNOTAVAIL */
#ifdef EADV
    [ EADV ]             = "EADV",
#endif /* EADV */
#ifdef EAFNOSUPPORT
    [ EAFNOSUPPORT ]     = "EAFNOSUPPORT",
#endif /* EAFNOSUPPORT */
#ifdef EAGAIN
    [ EAGAIN ]           = "EAGAIN",
#endif /* EAGAIN */
#ifdef EALREADY
    [ EALREADY ]         = "EALREADY",
#endif /* EALREADY */
#ifdef EAUTH
    [ EAUTH ]            = "EAUTH",
#endif /* EAUTH */
#ifdef EBACKGROUND
    [ EBACKGROUND ]      = "EBACKGROUND",
#endif /* EBACKGROUND */
#ifdef EBADARCH
    [ EBADARCH ]         = "EBADARCH",
#endif /* EBADARCH */
#ifdef EBADE
    [ EBADE ]            = "EBADE",
#endif /* EBADE */
#ifdef EBADEXEC
    [ EBADEXEC ]         = "EBADEXEC",
#endif /* EBADEXEC */
#ifdef EBADF
    [ EBADF ]            = "EBADF",
#endif /* EBADF */
#ifdef EBADFD
    [ EBADFD ]           = "EBADFD",
#endif /* EBADFD */
#ifdef EBADMACHO
    [ EBADMACHO ]        = "EBADMACHO",
#endif /* EBADMACHO */
#ifdef EBADMSG
    [ EBADMSG ]          = "EBADMSG",
#endif /* EBADMSG */
#ifdef EBADR
    [ EBADR ]            = "EBADR",
#endif /* EBADR */
#ifdef EBADRPC
    [ EBADRPC ]          = "EBADRPC",
#endif /* EBADRPC */
#ifdef EBADRQC
    [ EBADRQC ]          = "EBADRQC",
#endif /* EBADRQC */
#ifdef EBADSLT
    [ EBADSLT ]          = "EBADSLT",
#endif /* EBADSLT */
#ifdef EBFONT
    [ EBFONT ]           = "EBFONT",
#endif /* EBFONT */
#ifdef EBUSY
    [ EBUSY ]            = "EBUSY",
#endif /* EBUSY */
#ifdef ECANCELED
    [ ECANCELED ]        = "ECANCELED",
#endif /* ECANCELED */
#ifdef ECHILD
    [ ECHILD ]           = "ECHILD",
#endif /* ECHILD */
#ifdef ECHRNG
    [ ECHRNG ]           = "ECHRNG",
#endif /* ECHRNG */
#ifdef ECOMM
    [ ECOMM ]            = "ECOMM",
#endif /* ECOMM */
#ifdef ECONNABORTED
    [ ECONNABORTED ]     = "ECONNABORTED",
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
    [ ECONNREFUSED ]     = "ECONNREFUSED",
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
    [ ECONNRESET ]       = "ECONNRESET",
#endif /* ECONNRESET */
#ifdef ED
    [ ED ]               = "ED",
#endif /* ED */
#ifdef EDEADLK
    [ EDEADLK ]          = "EDEADLK",
#endif /* EDEADLK */
#if defined(EDEADLOCK) && EDEADLOCK != EDEADLK
    [ EDEADLOCK ]        = "EDEADLOCK",
#endif /* EDEADLOCK */
#ifdef EDESTADDRREQ
    [ EDESTADDRREQ ]     = "EDESTADDRREQ",
#endif /* EDESTADDRREQ */
#ifdef EDEVERR
    [ EDEVERR ]          = "EDEVERR",
#endif /* EDEVERR */
#ifdef EDIED
    [ EDIED ]            = "EDIED",
#endif /* EDIED */
#ifdef EDOM
    [ EDOM ]             = "EDOM",
#endif /* EDOM */
#ifdef EDOOFUS
    [ EDOOFUS ]          = "EDOOFUS",
#endif /* EDOOFUS */
#ifdef EDOTDOT
    [ EDOTDOT ]          = "EDOTDOT",
#endif /* EDOTDOT */
#ifdef EDQUOT
    [ EDQUOT ]           = "EDQUOT",
#endif /* EDQUOT */
#ifdef EEXIST
    [ EEXIST ]           = "EEXIST",
#endif /* EEXIST */
#ifdef EFAULT
    [ EFAULT ]           = "EFAULT",
#endif /* EFAULT */
#ifdef EFBIG
    [ EFBIG ]            = "EFBIG",
#endif /* EFBIG */
#ifdef EFTYPE
    [ EFTYPE ]           = "EFTYPE",
#endif /* EFTYPE */
#ifdef EGRATUITOUS
    [ EGRATUITOUS ]      = "EGRATUITOUS",
#endif /* EGRATUITOUS */
#ifdef EGREGIOUS
    [ EGREGIOUS ]        = "EGREGIOUS",
#endif /* EGREGIOUS */
#ifdef EHOSTDOWN
    [ EHOSTDOWN ]        = "EHOSTDOWN",
#endif /* EHOSTDOWN */
#ifdef EHOSTUNREACH
    [ EHOSTUNREACH ]     = "EHOSTUNREACH",
#endif /* EHOSTUNREACH */
#ifdef EHWPOISON
    [ EHWPOISON ]        = "EHWPOISON",
#endif /* EHWPOISON */
#ifdef EIDRM
    [ EIDRM ]            = "EIDRM",
#endif /* EIDRM */
#ifdef EIEIO
    [ EIEIO ]            = "EIEIO",
#endif /* EIEIO */
#ifdef EILSEQ
    [ EILSEQ ]           = "EILSEQ",
#endif /* EILSEQ */
#ifdef EINPROGRESS
    [ EINPROGRESS ]      = "EINPROGRESS",
#endif /* EINPROGRESS */
#ifdef EINTR
    [ EINTR ]            = "EINTR",
#endif /* EINTR */
#ifdef EINVAL
    [ EINVAL ]           = "EINVAL",
#endif /* EINVAL */
#ifdef EIO
    [ EIO ]              = "EIO",
#endif /* EIO */
#ifdef EISCONN
    [ EISCONN ]          = "EISCONN",
#endif /* EISCONN */
#ifdef EISDIR
    [ EISDIR ]           = "EISDIR",
#endif /* EISDIR */
#ifdef EISNAM
    [ EISNAM ]           = "EISNAM",
#endif /* EISNAM */
#ifdef EKEYEXPIRED
    [ EKEYEXPIRED ]      = "EKEYEXPIRED",
#endif /* EKEYEXPIRED */
#ifdef EKEYREJECTED
    [ EKEYREJECTED ]     = "EKEYREJECTED",
#endif /* EKEYREJECTED */
#ifdef EKEYREVOKED
    [ EKEYREVOKED ]      = "EKEYREVOKED",
#endif /* EKEYREVOKED */
#ifdef EL2HLT
    [ EL2HLT ]           = "EL2HLT",
#endif /* EL2HLT */
#ifdef EL2NSYNC
    [ EL2NSYNC ]         = "EL2NSYNC",
#endif /* EL2NSYNC */
#ifdef EL3HLT
    [ EL3HLT ]           = "EL3HLT",
#endif /* EL3HLT */
#ifdef EL3RST
    [ EL3RST ]           = "EL3RST",
#endif /* EL3RST */
#ifdef ELIBACC
    [ ELIBACC ]          = "ELIBACC",
#endif /* ELIBACC */
#ifdef ELIBBAD
    [ ELIBBAD ]          = "ELIBBAD",
#endif /* ELIBBAD */
#ifdef ELIBEXEC
    [ ELIBEXEC ]         = "ELIBEXEC",
#endif /* ELIBEXEC */
#ifdef ELIBMAX
    [ ELIBMAX ]          = "ELIBMAX",
#endif /* ELIBMAX */
#ifdef ELIBSCN
    [ ELIBSCN ]          = "ELIBSCN",
#endif /* ELIBSCN */
#ifdef ELNRNG
    [ ELNRNG ]           = "ELNRNG",
#endif /* ELNRNG */
#ifdef ELOOP
    [ ELOOP ]            = "ELOOP",
#endif /* ELOOP */
#ifdef EMEDIUMTYPE
    [ EMEDIUMTYPE ]      = "EMEDIUMTYPE",
#endif /* EMEDIUMTYPE */
#ifdef EMFILE
    [ EMFILE ]           = "EMFILE",
#endif /* EMFILE */
#ifdef EMLINK
    [ EMLINK ]           = "EMLINK",
#endif /* EMLINK */
#ifdef EMSGSIZE
    [ EMSGSIZE ]         = "EMSGSIZE",
#endif /* EMSGSIZE */
#ifdef EMULTIHOP
    [ EMULTIHOP ]        = "EMULTIHOP",
#endif /* EMULTIHOP */
#ifdef ENAMETOOLONG
    [ ENAMETOOLONG ]     = "ENAMETOOLONG",
#endif /* ENAMETOOLONG */
#ifdef ENAVAIL
    [ ENAVAIL ]          = "ENAVAIL",
#endif /* ENAVAIL */
#ifdef ENEEDAUTH
    [ ENEEDAUTH ]        = "ENEEDAUTH",
#endif /* ENEEDAUTH */
#ifdef ENETDOWN
    [ ENETDOWN ]         = "ENETDOWN",
#endif /* ENETDOWN */
#ifdef ENETRESET
    [ ENETRESET ]        = "ENETRESET",
#endif /* ENETRESET */
#ifdef ENETUNREACH
    [ ENETUNREACH ]      = "ENETUNREACH",
#endif /* ENETUNREACH */
#ifdef ENFILE
    [ ENFILE ]           = "ENFILE",
#endif /* ENFILE */
#ifdef ENOANO
    [ ENOANO ]           = "ENOANO",
#endif /* ENOANO */
#ifdef ENOATTR
    [ ENOATTR ]          = "ENOATTR",
#endif /* ENOATTR */
#ifdef ENOBUFS
    [ ENOBUFS ]          = "ENOBUFS",
#endif /* ENOBUFS */
#ifdef ENOCSI
    [ ENOCSI ]           = "ENOCSI",
#endif /* ENOCSI */
#ifdef ENODATA
    [ ENODATA ]          = "ENODATA",
#endif /* ENODATA */
#ifdef ENODEV
    [ ENODEV ]           = "ENODEV",
#endif /* ENODEV */
#ifdef ENOENT
    [ ENOENT ]           = "ENOENT",
#endif /* ENOENT */
#ifdef ENOEXEC
    [ ENOEXEC ]          = "ENOEXEC",
#endif /* ENOEXEC */
#ifdef ENOKEY
    [ ENOKEY ]           = "ENOKEY",
#endif /* ENOKEY */
#ifdef ENOLCK
    [ ENOLCK ]           = "ENOLCK",
#endif /* ENOLCK */
#ifdef ENOLINK
    [ ENOLINK ]          = "ENOLINK",
#endif /* ENOLINK */
#ifdef ENOMEDIUM
    [ ENOMEDIUM ]        = "ENOMEDIUM",
#endif /* ENOMEDIUM */
#ifdef ENOMEM
    [ ENOMEM ]           = "ENOMEM",
#endif /* ENOMEM */
#ifdef ENOMSG
    [ ENOMSG ]           = "ENOMSG",
#endif /* ENOMSG */
#ifdef ENONET
    [ ENONET ]           = "ENONET",
#endif /* ENONET */
#ifdef ENOPKG
    [ ENOPKG ]           = "ENOPKG",
#endif /* ENOPKG */
#ifdef ENOPROTOOPT
    [ ENOPROTOOPT ]      = "ENOPROTOOPT",
#endif /* ENOPROTOOPT */
#ifdef ENOSPC
    [ ENOSPC ]           = "ENOSPC",
#endif /* ENOSPC */
#ifdef ENOSR
    [ ENOSR ]            = "ENOSR",
#endif /* ENOSR */
#ifdef ENOSTR
    [ ENOSTR ]           = "ENOSTR",
#endif /* ENOSTR */
#ifdef ENOSYS
    [ ENOSYS ]           = "ENOSYS",
#endif /* ENOSYS */
#ifdef ENOTBLK
    [ ENOTBLK ]          = "ENOTBLK",
#endif /* ENOTBLK */
#ifdef ENOTCAPABLE
    [ ENOTCAPABLE ]      = "ENOTCAPABLE",
#endif /* ENOTCAPABLE */
#ifdef ENOTCONN
    [ ENOTCONN ]         = "ENOTCONN",
#endif /* ENOTCONN */
#ifdef ENOTDIR
    [ ENOTDIR ]          = "ENOTDIR",
#endif /* ENOTDIR */
#ifdef ENOTEMPTY
    [ ENOTEMPTY ]        = "ENOTEMPTY",
#endif /* ENOTEMPTY */
#ifdef ENOTNAM
    [ ENOTNAM ]          = "ENOTNAM",
#endif /* ENOTNAM */
#ifdef ENOTRECOVERABLE
    [ ENOTRECOVERABLE ]  = "ENOTRECOVERABLE",
#endif /* ENOTRECOVERABLE */
#ifdef ENOTSOCK
    [ ENOTSOCK ]         = "ENOTSOCK",
#endif /* ENOTSOCK */
#if defined(ENOTSUP) && ENOTSUP != EOPNOTSUPP
    [ ENOTSUP ]          = "ENOTSUP",
#endif /* ENOTSUP */
#ifdef ENOTTY
    [ ENOTTY ]           = "ENOTTY",
#endif /* ENOTTY */
#ifdef ENOTUNIQ
    [ ENOTUNIQ ]         = "ENOTUNIQ",
#endif /* ENOTUNIQ */
#ifdef ENXIO
    [ ENXIO ]            = "ENXIO",
#endif /* ENXIO */
#ifdef EOPNOTSUPP
    [ EOPNOTSUPP ]       = "EOPNOTSUPP",
#endif /* EOPNOTSUPP */
#ifdef EOVERFLOW
    [ EOVERFLOW ]        = "EOVERFLOW",
#endif /* EOVERFLOW */
#ifdef EOWNERDEAD
    [ EOWNERDEAD ]       = "EOWNERDEAD",
#endif /* EOWNERDEAD */
#ifdef EPERM
    [ EPERM ]            = "EPERM",
#endif /* EPERM */
#ifdef EPFNOSUPPORT
    [ EPFNOSUPPORT ]     = "EPFNOSUPPORT",
#endif /* EPFNOSUPPORT */
#ifdef EPIPE
    [ EPIPE ]            = "EPIPE",
#endif /* EPIPE */
#ifdef EPROCLIM
    [ EPROCLIM ]         = "EPROCLIM",
#endif /* EPROCLIM */
#ifdef EPROCUNAVAIL
    [ EPROCUNAVAIL ]     = "EPROCUNAVAIL",
#endif /* EPROCUNAVAIL */
#ifdef EPROGMISMATCH
    [ EPROGMISMATCH ]    = "EPROGMISMATCH",
#endif /* EPROGMISMATCH */
#ifdef EPROGUNAVAIL
    [ EPROGUNAVAIL ]     = "EPROGUNAVAIL",
#endif /* EPROGUNAVAIL */
#ifdef EPROTO
    [ EPROTO ]           = "EPROTO",
#endif /* EPROTO */
#ifdef EPROTONOSUPPORT
    [ EPROTONOSUPPORT ]  = "EPROTONOSUPPORT",
#endif /* EPROTONOSUPPORT */
#ifdef EPROTOTYPE
    [ EPROTOTYPE ]       = "EPROTOTYPE",
#endif /* EPROTOTYPE */
#ifdef EPWROFF
    [ EPWROFF ]          = "EPWROFF",
#endif /* EPWROFF */
#ifdef ERANGE
    [ ERANGE ]           = "ERANGE",
#endif /* ERANGE */
#ifdef EREMCHG
    [ EREMCHG ]          = "EREMCHG",
#endif /* EREMCHG */
#ifdef EREMOTE
    [ EREMOTE ]          = "EREMOTE",
#endif /* EREMOTE */
#ifdef EREMOTEIO
    [ EREMOTEIO ]        = "EREMOTEIO",
#endif /* EREMOTEIO */
#ifdef ERESTART
    [ ERESTART ]         = "ERESTART",
#endif /* ERESTART */
#ifdef ERFKILL
    [ ERFKILL ]          = "ERFKILL",
#endif /* ERFKILL */
#ifdef EROFS
    [ EROFS ]            = "EROFS",
#endif /* EROFS */
#ifdef ERPCMISMATCH
    [ ERPCMISMATCH ]     = "ERPCMISMATCH",
#endif /* ERPCMISMATCH */
#ifdef ESHLIBVERS
    [ ESHLIBVERS ]       = "ESHLIBVERS",
#endif /* ESHLIBVERS */
#ifdef ESHUTDOWN
    [ ESHUTDOWN ]        = "ESHUTDOWN",
#endif /* ESHUTDOWN */
#ifdef ESOCKTNOSUPPORT
    [ ESOCKTNOSUPPORT ]  = "ESOCKTNOSUPPORT",
#endif /* ESOCKTNOSUPPORT */
#ifdef ESPIPE
    [ ESPIPE ]           = "ESPIPE",
#endif /* ESPIPE */
#ifdef ESRCH
    [ ESRCH ]            = "ESRCH",
#endif /* ESRCH */
#ifdef ESRMNT
    [ ESRMNT ]           = "ESRMNT",
#endif /* ESRMNT */
#ifdef ESTALE
    [ ESTALE ]           = "ESTALE",
#endif /* ESTALE */
#ifdef ESTRPIPE
    [ ESTRPIPE ]         = "ESTRPIPE",
#endif /* ESTRPIPE */
#ifdef ETIME
    [ ETIME ]            = "ETIME",
#endif /* ETIME */
#ifdef ETIMEDOUT
    [ ETIMEDOUT ]        = "ETIMEDOUT",
#endif /* ETIMEDOUT */
#ifdef ETOOMANYREFS
    [ ETOOMANYREFS ]     = "ETOOMANYREFS",
#endif /* ETOOMANYREFS */
#ifdef ETXTBSY
    [ ETXTBSY ]          = "ETXTBSY",
#endif /* ETXTBSY */
#ifdef EUCLEAN
    [ EUCLEAN ]          = "EUCLEAN",
#endif /* EUCLEAN */
#ifdef EUNATCH
    [ EUNATCH ]          = "EUNATCH",
#endif /* EUNATCH */
#ifdef EUSERS
    [ EUSERS ]           = "EUSERS",
#endif /* EUSERS */
#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
    [ EWOULDBLOCK ]      = "EWOULDBLOCK",
#endif /* EWOULDBLOCK */
#ifdef EXDEV
    [ EXDEV ]            = "EXDEV",
#endif /* EXDEV */
#ifdef EXFULL
    [ EXFULL ]           = "EXFULL",
#endif /* EXFULL */
};

#define ERRNAMELIST_LEN ARRAY_SIZE(errnamelist)

// Hardcode solution
TEST_LINKAGE const char* strerrorname_hardcode(int errnum)
{
    // There is no C standard way to get the acronym for the errno
    // errors. However, these are defined by ISO C as macros, so they
    // can be tested for. Some errno macros may have the same value.
    if (0 < errnum && errnum < ERRNAMELIST_LEN)
    {
        const char *buf = errnamelist[errnum];
        if (buf != NULL) return buf;
    }

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
