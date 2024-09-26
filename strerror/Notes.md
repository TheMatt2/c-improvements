Goals

1. Works on everything
2. Don't care about locale support
3. "Successful call to strerror() or strerror_l() shall leave errno unchanged..." (man strerror)
4. C11. At least glibc 2.15


;sadASD
5. Ideally don't need to hardcode all possible value.
6. Ideally don'
7. AA  h.u4t need explicit buffer.


POSIX.1-2008

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

## References

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