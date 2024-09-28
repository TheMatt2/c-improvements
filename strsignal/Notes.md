| C Library Function     | glibc Support               | Requirements                                                                                                   |
| ---------------------- | --------------------------- | -------------------------------------------------------------------------------------------------------------- |
| `strsignal()`          | >= glibc 1.09               | POSIX.1-2008. POSIX specifies "need not be thread-safe.". Requires _POSIX_C_SOURCE >= 200809L or `_GNU_SOURCE` |
| `sigdescr_np`          | >= glibc 2.32               | Requires `_GNU_SOURCE`                                                                                         |
| `sys_siglist` / `NSIG` | >= glibc 1.09. < glibc 2.32 | glibc specific                                                                                                 |

## References

 - https://elixir.bootlin.com/glibc/glibc-2.40/source/NEWS
 - https://pubs.opengroup.org/onlinepubs/9699919799.2016edition/functions/strsignal.html
 - https://peeterjoot.com/2019/09/20/an-example-of-linux-glibc-symbol-versioning/
 - https://elixir.bootlin.com/glibc/glibc-2.39/source/sysdeps/unix/sysv/linux/siglist-compat.h
 - https://discourse.llvm.org/t/targeting-old-glibc/56793
 - https://github.com/wheybags/glibc_version_header/blob/master/glibc_version_header_gen.py