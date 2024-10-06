## Common String Library

1. Works on everything
2. Don't care about locale support
3. "Successful call to strerror() or strerror_l() shall leave errno unchanged..." (man strerror)
4. C11. At least glibc 2.15
5. Ideally don't need to hardcode all possible value.
6. Ideally don't need explicit buffer.

### strstring

| C Library Function       | glibc Support                          | Requirements                                                      |
| ------------------------ | -------------------------------------- | ----------------------------------------------------------------- |
| `strerror()`             | >= glibc 1.0? MT-safe >= 2.32          | POSIX still says it isn't thread safe.                            |
| `char* strerror_r()` GNU | >= glibc 2.0                           | Requires `_GNU_SOURCE`                                            |
| `int strerror_r()` XSI   | >= glibc 2.13                          | Requires `(_POSIX_C_SOURCE >= 200112L) && ! defined(_GNU_SOURCE)` |
| `char* strerror_l()`     | >= glibc 2.6                           | POSIX.1-2008                                                      |
| `strerrordesc_np()`      | >= glibc 2.32                          | Non-POSIX. GNU specific.                                          |
| `sys_errlist[]`          | < glibc 2.32. Deprecated >= glibc 2.19 | Non-POSIX. GNU specific.                                          |
| `printf("%m")`           | glibc 1.06                             | None?                                                             |
| `strerror_s()`           | None!                                  | C11 with `__STDC_WANT_LIB_EXT1__` and if extension is supported.  |

If Non-GNU, POSIX.1 2001 only... put a lock around strerror?

Preferability of Solutions
1. If glibc >= 2.32. Directly use strerror()
2. If `__STDC_LIB_EXT1__` is defined, use `strerror_s()`
3. If glibc < 2.32. `printf("%m")`
4. `pthread_mutex_lock()` around strerror()

### References

 - http://www.club.cc.cmu.edu/~cmccabe/blog_strerror.html
 - https://man7.org/linux/man-pages/man3/strerror.3.html
 - https://man7.org/linux/man-pages/man3/strerror.3p.html
 - https://man.freebsd.org/cgi/man.cgi?query=strerror&apropos=0&sektion=0&manpath=FreeBSD+6.2-RELEASE&arch=default&format=html
 - https://github.com/rafael-santiago/aegis/tree/e648ef933db02dce89a73ed7fceb03cfb0dcb59b
 - https://forums.freebsd.org/threads/gcc-general-macro-for-bsd.47769/
 - http://www.rkoucha.fr/tech_corner/percent_m.html
 - https://stackoverflow.com/questions/20577557/whats-the-meaning-of-the-m-formatting-specifier
 - https://elixir.bootlin.com/glibc/glibc-2.31/source/NEWS
 - https://gcc.gnu.org/onlinedocs/gcc/C99-Thread-Local-Edits.html
 - https://man7.org/linux/man-pages/man3/printf.3.html
 - https://en.cppreference.com/w/c/string/byte/strerror
 - https://github.com/tavianator/bfs/blob/c1ac8a73589f9d27704e6bd8f99d0c42fac2100f/src/bfstd.c#L329


## strsignal

| C Library Function                  | glibc Support                | Requirements                                                                                                                                |
| ----------------------------------- | ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| `strsignal()` <br> defacto MT-Safe  | >= glibc 2.32                | man page says "MT-Unsafe race:strsignal locale". Yet source code reveals this uses thread local storage to make it safe.                    |
| `strsignal()` <br> attempts MT-Safe | < glibc 2.32 >= glibc 2.0.29 | Source code reveals `pthread_key_create()` is used. Falls back to unsafe global buffer.                                                     |
| `strsignal()` <br> MT-Unsafe        | >= glibc 1.09                | POSIX.1-2008. POSIX specifies "need not be thread-safe.". All version of `strsignal()` requires _POSIX_C_SOURCE >= 200809L or `_GNU_SOURCE` |
| `sigdescr_np`                       | >= glibc 2.32                | Requires `_GNU_SOURCE`                                                                                                                      |
| `sys_siglist` / `NSIG`              | >= glibc 1.09. < glibc 2.32  | glibc specific                                                                                                                              |

### References

 - https://elixir.bootlin.com/glibc/glibc-2.40/source/NEWS
 - https://pubs.opengroup.org/onlinepubs/9699919799.2016edition/functions/strsignal.html
 - https://peeterjoot.com/2019/09/20/an-example-of-linux-glibc-symbol-versioning/
 - https://elixir.bootlin.com/glibc/glibc-2.39/source/sysdeps/unix/sysv/linux/siglist-compat.h
 - https://discourse.llvm.org/t/targeting-old-glibc/56793
 - https://github.com/wheybags/glibc_version_header/blob/master/glibc_version_header_gen.py

## strerrorname

1. `strerrorname_np()`
2. `printf("%M")`
3. hardcode
