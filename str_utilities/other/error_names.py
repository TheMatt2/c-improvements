ERRNO_NAMES = [
    "E2BIG",           "EACCES",          "EADDRINUSE",      "EADDRNOTAVAIL",
    "EADV",            "EAFNOSUPPORT",    "EAGAIN",          "EALREADY",
    "EAUTH",           "EBACKGROUND",     "EBADARCH",        "EBADE",
    "EBADEXEC",        "EBADF",           "EBADFD",          "EBADMACHO",
    "EBADMSG",         "EBADR",           "EBADRPC",         "EBADRQC",
    "EBADSLT",         "EBFONT",          "EBUSY",           "ECANCELED",
    "ECHILD",          "ECHRNG",          "ECOMM",           "ECONNABORTED",
    "ECONNREFUSED",    "ECONNRESET",      "ED",              "EDEADLK",
    "EDEADLOCK",       "EDESTADDRREQ",    "EDEVERR",         "EDIED",
    "EDOM",            "EDOOFUS",         "EDOTDOT",         "EDQUOT",
    "EEXIST",          "EFAULT",          "EFBIG",           "EFTYPE",
    "EGRATUITOUS",     "EGREGIOUS",       "EHOSTDOWN",       "EHOSTUNREACH",
    "EHWPOISON",       "EIDRM",           "EIEIO",           "EILSEQ",
    "EINPROGRESS",     "EINTR",           "EINVAL",          "EIO",
    "EISCONN",         "EISDIR",          "EISNAM",          "EKEYEXPIRED",
    "EKEYREJECTED",    "EKEYREVOKED",     "EL2HLT",          "EL2NSYNC",
    "EL3HLT",          "EL3RST",          "ELIBACC",         "ELIBBAD",
    "ELIBEXEC",        "ELIBMAX",         "ELIBSCN",         "ELNRNG",
    "ELOOP",           "EMEDIUMTYPE",     "EMFILE",          "EMLINK",
    "EMSGSIZE",        "EMULTIHOP",       "ENAMETOOLONG",    "ENAVAIL",
    "ENEEDAUTH",       "ENETDOWN",        "ENETRESET",       "ENETUNREACH",
    "ENFILE",          "ENOANO",          "ENOATTR",         "ENOBUFS",
    "ENOCSI",          "ENODATA",         "ENODEV",          "ENOENT",
    "ENOEXEC",         "ENOKEY",          "ENOLCK",          "ENOLINK",
    "ENOMEDIUM",       "ENOMEM",          "ENOMSG",          "ENONET",
    "ENOPKG",          "ENOPROTOOPT",     "ENOSPC",          "ENOSR",
    "ENOSTR",          "ENOSYS",          "ENOTBLK",         "ENOTCAPABLE",
    "ENOTCONN",        "ENOTDIR",         "ENOTEMPTY",       "ENOTNAM",
    "ENOTRECOVERABLE", "ENOTSOCK",        "ENOTSUP",         "ENOTTY",
    "ENOTUNIQ",        "ENXIO",           "EOPNOTSUPP",      "EOVERFLOW",
    "EOWNERDEAD",      "EPERM",           "EPFNOSUPPORT",    "EPIPE",
    "EPROCLIM",        "EPROCUNAVAIL",    "EPROGMISMATCH",   "EPROGUNAVAIL",
    "EPROTO",          "EPROTONOSUPPORT", "EPROTOTYPE",      "EPWROFF",
    "ERANGE",          "EREMCHG",         "EREMOTE",         "EREMOTEIO",
    "ERESTART",        "ERFKILL",         "EROFS",           "ERPCMISMATCH",
    "ESHLIBVERS",      "ESHUTDOWN",       "ESOCKTNOSUPPORT", "ESPIPE",
    "ESRCH",           "ESRMNT",          "ESTALE",          "ESTRPIPE",
    "ETIME",           "ETIMEDOUT",       "ETOOMANYREFS",    "ETXTBSY",
    "EUCLEAN",         "EUNATCH",         "EUSERS",          "EWOULDBLOCK",
    "EXDEV",           "EXFULL"
]

list_prefix = """
const char* errnamelist[] = {
""".strip()
list_element = """
#ifdef {errname}
    [ {errname} ] {errname_quoted:>20},
#endif /* {errname} */
""".strip()
list_postfix = """
};
""".strip()


print(list_prefix)
for errname in ERRNO_NAMES:
    print(list_element.format(
        errname = errname, errname_quoted = f'= "{errname}"'))
print(list_postfix)
