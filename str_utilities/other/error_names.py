ERRNO_NAMES = [
    "E2BIG",           "EACCES",          "EADDRINUSE",      "EADDRNOTAVAIL",
    "EAFNOSUPPORT",    "EAGAIN",          "EALREADY",        "EAUTH",
    "EBADARCH",        "EBADE",           "EBADEXEC",        "EBADF",
    "EBADFD",          "EBADMACHO",       "EBADMSG",         "EBADR",
    "EBADRPC",         "EBADRQC",         "EBADSLT",         "EBUSY",
    "ECANCELED",       "ECHILD",          "ECHRNG",          "ECOMM",
    "ECONNABORTED",    "ECONNREFUSED",    "ECONNRESET",      "EDEADLK",
    "EDEADLOCK",       "EDESTADDRREQ",    "EDEVERR",         "EDOM",
    "EDOOFUS",         "EDQUOT",          "EEXIST",          "EFAULT",
    "EFBIG",           "EFTYPE",          "EHOSTDOWN",       "EHOSTUNREACH",
    "EHWPOISON",       "EIDRM",           "EILSEQ",          "EINPROGRESS",
    "EINTR",           "EINVAL",          "EIO",             "EISCONN",
    "EISDIR",          "EISNAM",          "EKEYEXPIRED",     "EKEYREJECTED",
    "EKEYREVOKED",     "EL2HLT",          "EL2NSYNC",        "EL3HLT",
    "EL3RST",          "ELIBACC",         "ELIBBAD",         "ELIBEXEC",
    "ELIBMAX",         "ELIBSCN",         "ELNRNG",          "ELOOP",
    "EMEDIUMTYPE",     "EMFILE",          "EMLINK",          "EMSGSIZE",
    "EMULTIHOP",       "ENAMETOOLONG",    "ENEEDAUTH",       "ENETDOWN",
    "ENETRESET",       "ENETUNREACH",     "ENFILE",          "ENOANO",
    "ENOATTR",         "ENOBUFS",         "ENODATA",         "ENODEV",
    "ENOENT",          "ENOEXEC",         "ENOKEY",          "ENOLCK",
    "ENOLINK",         "ENOMEDIUM",       "ENOMEM",          "ENOMSG",
    "ENONET",          "ENOPKG",          "ENOPROTOOPT",     "ENOSPC",
    "ENOSR",           "ENOSTR",          "ENOSYS",          "ENOTBLK",
    "ENOTCAPABLE",     "ENOTCONN",        "ENOTDIR",         "ENOTEMPTY",
    "ENOTRECOVERABLE", "ENOTSOCK",        "ENOTSUP",         "ENOTTY",
    "ENOTUNIQ",        "ENXIO",           "EOPNOTSUPP",      "EOVERFLOW",
    "EOWNERDEAD",      "EPERM",           "EPFNOSUPPORT",    "EPIPE",
    "EPROCLIM",        "EPROCUNAVAIL",    "EPROGMISMATCH",   "EPROGUNAVAIL",
    "EPROTO",          "EPROTONOSUPPORT", "EPROTOTYPE",      "EPWROFF",
    "ERANGE",          "EREMCHG",         "EREMOTE",         "EREMOTEIO",
    "ERESTART",        "ERFKILL",         "EROFS",           "ERPCMISMATCH",
    "ESHLIBVERS",      "ESHUTDOWN",       "ESOCKTNOSUPPORT", "ESPIPE",
    "ESRCH",           "ESTALE",          "ESTRPIPE",        "ETIME",
    "ETIMEDOUT",       "ETOOMANYREFS",    "ETXTBSY",         "EUCLEAN",
    "EUNATCH",         "EUSERS",          "EWOULDBLOCK",     "EXDEV",
    "EXFULL"]

list_prefix = """
const char* errnamelist[] = {
""".strip()
list_element = """
#ifdef {errname}
    [ {errname} ] = "{errname}",
#endif /* {errname} */
""".strip()
list_postfix = """
};
""".strip()


print(list_prefix)
for errname in ERRNO_NAMES:
    print(list_element.format(errname = errname))
print(list_postfix)
