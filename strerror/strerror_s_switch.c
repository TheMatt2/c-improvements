// gcc -c -std=c11 -Os
#include <errno.h>
#include <stdio.h>

const char* strerror_s(int err)
{
    // Return short name of errno values
    switch (err) {
        case E2BIG          : return "E2BIG";
        case EACCES         : return "EACCES";
        case EADDRINUSE     : return "EADDRINUSE";
        case EADDRNOTAVAIL  : return "EADDRNOTAVAIL";
        case EAFNOSUPPORT   : return "EAFNOSUPPORT";
        case EAGAIN         : return "EAGAIN";
        case EALREADY       : return "EALREADY";
        case EBADE          : return "EBADE";
        case EBADF          : return "EBADF";
        case EBADFD         : return "EBADFD";
        case EBADMSG        : return "EBADMSG";
        case EBADR          : return "EBADR";
        case EBADRQC        : return "EBADRQC";
        case EBADSLT        : return "EBADSLT";
        case EBUSY          : return "EBUSY";
        case ECANCELED      : return "ECANCELED";
        case ECHILD         : return "ECHILD";
        case ECHRNG         : return "ECHRNG";
        case ECOMM          : return "ECOMM";
        case ECONNABORTED   : return "ECONNABORTED";
        case ECONNREFUSED   : return "ECONNREFUSED";
        case ECONNRESET     : return "ECONNRESET";
        case EDEADLK        : return "EDEADLK";
#if EDEADLK != EDEADLOCK
        case EDEADLOCK      : return "EDEADLOCK";
#endif
        case EDESTADDRREQ   : return "EDESTADDRREQ";
        case EDOM           : return "EDOM";
        case EDQUOT         : return "EDQUOT";
        case EEXIST         : return "EEXIST";
        case EFAULT         : return "EFAULT";
        case EFBIG          : return "EFBIG";
        case EHOSTDOWN      : return "EHOSTDOWN";
        case EHOSTUNREACH   : return "EHOSTUNREACH";
        case EHWPOISON      : return "EHWPOISON";
        case EIDRM          : return "EIDRM";
        case EILSEQ         : return "EILSEQ";
        case EINPROGRESS    : return "EINPROGRESS";
        case EINTR          : return "EINTR";
        case EINVAL         : return "EINVAL";
        case EIO            : return "EIO";
        case EISCONN        : return "EISCONN";
        case EISDIR         : return "EISDIR";
        case EISNAM         : return "EISNAM";
        case EKEYEXPIRED    : return "EKEYEXPIRED";
        case EKEYREJECTED   : return "EKEYREJECTED";
        case EKEYREVOKED    : return "EKEYREVOKED";
        case EL2HLT         : return "EL2HLT";
        case EL2NSYNC       : return "EL2NSYNC";
        case EL3HLT         : return "EL3HLT";
        case EL3RST         : return "EL3RST";
        case ELIBACC        : return "ELIBACC";
        case ELIBBAD        : return "ELIBBAD";
        case ELIBMAX        : return "ELIBMAX";
        case ELIBSCN        : return "ELIBSCN";
        case ELIBEXEC       : return "ELIBEXEC";
        case ELNRNG         : return "ELNRNG";
        case ELOOP          : return "ELOOP";
        case EMEDIUMTYPE    : return "EMEDIUMTYPE";
        case EMFILE         : return "EMFILE";
        case EMLINK         : return "EMLINK";
        case EMSGSIZE       : return "EMSGSIZE";
        case EMULTIHOP      : return "EMULTIHOP";
        case ENAMETOOLONG   : return "ENAMETOOLONG";
        case ENETDOWN       : return "ENETDOWN";
        case ENETRESET      : return "ENETRESET";
        case ENETUNREACH    : return "ENETUNREACH";
        case ENFILE         : return "ENFILE";
        case ENOANO         : return "ENOANO";
        case ENOBUFS        : return "ENOBUFS";
        case ENODATA        : return "ENODATA";
        case ENODEV         : return "ENODEV";
        case ENOENT         : return "ENOENT";
        case ENOEXEC        : return "ENOEXEC";
        case ENOKEY         : return "ENOKEY";
        case ENOLCK         : return "ENOLCK";
        case ENOLINK        : return "ENOLINK";
        case ENOMEDIUM      : return "ENOMEDIUM";
        case ENOMEM         : return "ENOMEM";
        case ENOMSG         : return "ENOMSG";
        case ENONET         : return "ENONET";
        case ENOPKG         : return "ENOPKG";
        case ENOPROTOOPT    : return "ENOPROTOOPT";
        case ENOSPC         : return "ENOSPC";
        case ENOSR          : return "ENOSR";
        case ENOSTR         : return "ENOSTR";
        case ENOSYS         : return "ENOSYS";
        case ENOTBLK        : return "ENOTBLK";
        case ENOTCONN       : return "ENOTCONN";
        case ENOTDIR        : return "ENOTDIR";
        case ENOTEMPTY      : return "ENOTEMPTY";
        case ENOTRECOVERABLE: return "ENOTRECOVERABLE";
        case ENOTSOCK       : return "ENOTSOCK";
        case ENOTSUP        : return "ENOTSUP";
        case ENOTTY         : return "ENOTTY";
        case ENOTUNIQ       : return "ENOTUNIQ";
        case ENXIO          : return "ENXIO";
#if ENOTSUP != EOPNOTSUPP
        case EOPNOTSUPP     : return "EOPNOTSUPP";
#endif
        case EOVERFLOW      : return "EOVERFLOW";
        case EOWNERDEAD     : return "EOWNERDEAD";
        case EPERM          : return "EPERM";
        case EPFNOSUPPORT   : return "EPFNOSUPPORT";
        case EPIPE          : return "EPIPE";
        case EPROTO         : return "EPROTO";
        case EPROTONOSUPPORT: return "EPROTONOSUPPORT";
        case EPROTOTYPE     : return "EPROTOTYPE";
        case ERANGE         : return "ERANGE";
        case EREMCHG        : return "EREMCHG";
        case EREMOTE        : return "EREMOTE";
        case EREMOTEIO      : return "EREMOTEIO";
        case ERESTART       : return "ERESTART";
        case ERFKILL        : return "ERFKILL";
        case EROFS          : return "EROFS";
        case ESHUTDOWN      : return "ESHUTDOWN";
        case ESPIPE         : return "ESPIPE";
        case ESOCKTNOSUPPORT: return "ESOCKTNOSUPPORT";
        case ESRCH          : return "ESRCH";
        case ESTALE         : return "ESTALE";
        case ESTRPIPE       : return "ESTRPIPE";
        case ETIME          : return "ETIME";
        case ETIMEDOUT      : return "ETIMEDOUT";
        case ETOOMANYREFS   : return "ETOOMANYREFS";
        case ETXTBSY        : return "ETXTBSY";
        case EUCLEAN        : return "EUCLEAN";
        case EUNATCH        : return "EUNATCH";
        case EUSERS         : return "EUSERS";
#if EAGAIN != EWOULDBLOCK
        case EWOULDBLOCK    : return "EWOULDBLOCK";
#endif
        case EXDEV          : return "EXDEV";
        case EXFULL         : return "EXFULL";
    }

    static _Thread_local char errno_msg[22];

    // Save custom message to thread local memory
    snprintf(errno_msg, sizeof(errno_msg), "Unknown error: %d", err);
    return errno_msg;
}

// https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYMQAJlIOAMngMmABy7gBGmMQSAMwAHKQADqgKhLYMzm4e3onJqQIBQaEsEVFccRaYVjYCQgRMxAQZ7p5cFVVptfUEBSHhkXoKdQ1NWa2DXT1FJRIAlBaorsTI7BwApF7RgchuWADUq9GOkcQMqAB0CAfYqxoAguubDNuueweOg/jnl9HXdze3aAYg12yAQ9QAVLtBsRjiRjAoIIECLtjjN/qsAOwAIX%2BuzxuzwVF2EGO%2B2iABEDuTdtgvFiAJIAcRm%2BNZrJhBEWDH2Xi8tIZjPWXgOOLurMJxNJVKpNNujkc2CELLZ7MwnJOPL5coVQiFItx%2BIlJOIxDJlIpsvJ5IASvTgnIhNhlar1dyhdhblbbfbHXroqLbuKicbTdKLR6vcEAPIAFVuADVbvS/M6OVzNRGbdG44nk36A0HJSazTKPQAxaNCOTKZRR60x527NMa923CtRqs1usx/MGvFGqUU0u3RlJ4KNlXNt28j2ju29sWG4OD83Uj1%2Ba0RgCaE/xU4ztw324XgaXRdDQ/DWM9TpVbP37uv5OuvP1i/7y%2BLYbXT7Lu/varpo%2BnpliehYhiWV4geS/57oBLYzr%2BlKvv6fYEp%2BF6rjST4ALJCMyd54g%2BiGenhgooQWZ4Qd%2B2GetasFwa6GZPtaYFUSupYsQAio4DHEXy3GOGxH7npBP6ekIfgNoRTbwdOAkSVJwnoaJNHYFiDo7jJRFycxmnKQOX6Xmuji3MECp%2BNgMF3vx2CmeZ2CWchwqoe%2BKnUcZNKOAAEsm1kybZPl%2BQZGFiV53nWsEBEBbp7o%2BZF5EuZRIkeVhdlRjhOEMTpTFxRlOEhapnnpcEwS3Fi3ZWY2gVRqV5WVc5b6nilHHho4tXBJuZYOlVLpATO7WlV1PWNa5zXua1JkdZujrSQBuUDdNirYD2FFoYZmGls%2Bnp%2BAA0nxsUztt5J7YVqVbRGfhRo4%2B02YdfLHVdN1nZNNLPkIcZepuXHVfdVmKp9NrfS9RlpeSGXZTl/UPRlIObeG5JcXIsbZbZiPI6tSXraFanYAAGvSH2o39%2BOE5jTXga92BlrcchScTC18jTdPk2NlOg6WZYCpDtlc0ycNhdg3kdjG4MAOrjndjNCyL4vBALanCx9cidR6Pm/dLSsxirm5yt5CvFd5Yu1oTtX/rZRsm0ItUG2l9I2ll2mydL9vWgVa1uRtgvJo6P3abZPvYFxtulnayjWlGjIzUq83Q9gYcR1Hiq6h741e2pdoxvRTsB8EWch%2BGdqJim/t/UXh4F2u9JRpDUMIXy1eVzShODZLhEB0IrdN/HQjkvS2cxS7vf993hNlY7g9x2Ptzu1jns48Vu3YFu%2BPKP3vV9fX2BLyveNr5uo3JRNHPhjvm4AFJ2TGG91/J2/LxfV9Wd3Z/YPGUZL/5jFx6/7%2Bf93fgvDeXpqXaWgDgGsyPunYqgDghCC3OZWCtlYHwPMgA6IECGZxz8BgpSqd2bwzXDg60RNQHYOiCQyB2MippT8PSa88oDpgPodqAB9CnxMOwewz0bCsQ4VuHjThW86F8IEbwzubcpZcKxBI3h%2BM7JIL%2BiI%2BRQl8HsRPkQzqUUsHCK0YlCm6jCE0iulGZQPMlFRlMd3HCVl6RyBwjGLcyhbybzvjYvu9jHHOOsWWZMLj25/Rwr4yy1i6HBFupPLeOEwm7WsfhIQ9IABa/jY5RPiUkl8c804LzSjhFm9JhZmKkVE/JhTu7jxWpYq62jXEZgqTGKptV9Fs0MYLYIK05aKOlu00WUYJblJWjNFa5s/o9KGVQ%2BeNDSw9J1mrbyE5bIzNVnrcpwSUmTlGWs8pUYzI1zIVvaMuztkaTLDHAJ3SownJTlkghbSozkluHGIRd9owPLjNs588YdEvPuW/bZ2A87fLqVGAFEzslTPDNGFRzzgUqO2TvIF7pow722X4G6iKZzRjRbEtRLUNE0ixXaCJxSfkxO2e4uxE9Uk/IpfY8l2AqUkuBTY2eBi8VGIBRlfCGK%2BTRjItsnpPLOU9O2coXa0Vzlx2jGK5pUCcnTNMRHBppi5rfwOYq2MljlBgtuWpSsyheL7J%2BUIA12yhAD0ica1iuLj4csrFnIV9rrU3NaXqjsW4zmSvVfA65bLbV3JjFiPaMKkWxiDTil17KA2ty6VK2MXcbXQLStmPuFqNkXNFiPRN8rIWxgZdqrS6a43XxwgW7ZWd0rxmwNacqlkWSLNjJudqVaa1BsyX6pNCqYzW3RV6n53broRo7Tmtc2ZOwhsxbGTs5bHGOtjI48tKt6R%2ByZaG7WwRl3lIJnso1dTt3d1MWO6sRTqUZkPVO49B6W1liumLEZ0sozXtvQeiW1bjq7lsn09p1pjrd2cW7cx0t/2spaVGtSyh2ydlrPWDWccIOVmPd2P99JnGAbgyh9toH/XgaVTuvtGZw6ar/bhhDXYYPOzgyRjsiH6zEc1V49ZFGt6EYaQx7uNaoqMdqe6DjjJMNyohWuTcOEfISqLVvYTon2MMrzROvkwm83SZwnm6u9644Kevo3bNgmaQzTjOR1dM49O3Fo9p864ZrRll2smEu%2BGeNWZs%2BxqMpy0MSec76rDnbwxCG8nIXpEs1Nbx835uW3cTUYaFeF7xZmqY9t2jGUj0HpK2Tiwl6jZGdWuuKua9WOc/o5f1jF/FANDxcbVXfD6pWwtZzXqhuzM4PrWlq/x6h5m1wxnpDY1zd8Os2O7r1qyUY/OBZ651wbfn%2BuWP4cELcXVPVMZ61Nsys3qYeYE21mkMY8aBvgXJla22ZFbm7nIRwlkzJ7ZO2d%2BWRWOUq0ebl%2BrfI7sxh8sdx0JChU9RId3MWQ2/DkiDYOhZf1ft0wB09IdnmR00jxp87rGZYd/Ju4LPG3U/C2ce/jNHfgTxoQAPR45RLQJQaFxg2GQLsYwMYEAwiYOgYwtBUCiFoCCMEppjinGMCwBQwBVgAFYsSvj5%2BaI%2BCgGAJGIEiKgIZOfc%2BAKQKEeAABemBUDS456gLnPO5iajkAwAA1qcAA7tyWEUQeR8/QEKBXqI/X7g11r3nY1MTkg4HMWgnA%2Be8E8NwXgqBOCOChAsJYmAeTRB4KQAgmg3dzH194Pn%2BhOCSG99H0g/uOC8AUCADQkfo9zDgLAJAaAWAJDoJEcglBi%2Bl/oFEZAwAuAaATzQWgBBIhZ4gGEVPYRAj1AAJ6cAj935gxBe9RjCNoTA1gB%2B8GL2wQQUYGC0H7xwLQpAsBhFcMARwYhifT7X5gFghhgDiBX7wfAMJrB4AAG6YCz6f3wqhJ%2BuFb3vpElRU%2B0DwGEYgffnBYFTwQJLiwHvjfsQGEMkJgOSAfkfp/kYHnnwAYMAAoPGHgJgEblGAkIwHvvwIICIGIOwFIDIIIIoCoOoPfroK0AYHAaYMYOYJ/mEFnpAHMKgAkNUECJwAALQU4cEfBUjIBcBcC7AcFRgKB%2B6gGS5YCMEQBzCWCT5sH2AMBOAuDNB6D%2BCBC9DFD9CtBJApBsEjAtA5C6FpCTB9ClBtByEdBDCNDKGjDmGX41BWEmGaFmHjDDA2EGGuHdDqFTBaEyHB7LCzCJ4cBe6kA%2B6r7p67CqCxAABsHB0RkguwwAyAFODeZwfOxIuAhAJAYeXAMwvAUep%2BMwse3gsQZw0RXA0R0QfOvIGgXAXgfOGIMRQRyeoRqe6eme2euehRpABeiAKAGAOA%2BARAZAFA1AZezAbA2BsgeB4ghBOB8gSgagqeugPgVBJgZgdh8hJIih%2Bh2QahhQphEgkg8QOheQ6Q7h2QpxbBTh0wUg8Qsh9hDAnQbhmQHhlQFhDhEw3hhxYwVhuxvxXxBxzhgRCg/hKwDwWwOwoebwGuFwVw6IGwkJLw0JhwHwtgcJPw6IdwgIwIoIEIUIgBZu8IiIggKIJoaIfw2I%2BOhO1oukCgCAJAyIExoeauZJJwqAuwV%2BYgrgt%2BpORuhAoI54LImIR8rIogSgNIdITI2kIAC2GYUpsqaEYpTAEpasOoMksptk2oioykypqpnoNodoPUbImpf0Bp3oPUup%2BI4poemYkUsYCYSYfgeIpp0s5p2YjpeYNqeptpbYiW3Y%2BIrpccfp6WSWVpeINpsoc4wQGpcprY0Z4ZIIKpvpR4noW4d4QZW8h4us5IR23p1pyZtEz4MpcZJEz4iZkZ6kIEJZtkv4FZhZVZ5IZY1IhEmZd8SE9ZqpuE%2BErZpZCk5I/K%2BZEZDZLENZf0LEnZtpgkvZtZdEPEk5RZkkMYM545ikmWKolZGk8CY50sW5eZkabIlZ9kFkVkKobZGYx5jkz8Q5SZqpQU/2sZgUvk/2C5dkEUUUj5f08UUUr57UmUO5ccf5IGopBZd5HU9U9Yp5LpfZJUZUFUkFh8SpoFtprcw0joLZuw55eUQ01MI0v5S0s0JpMFqFy065h5DZj0u0K50slFuOiJRI/0O0VFYAYAF0O0g6SFw5qpj0g6Z5MFPFz0qcDwDghInFt5tp70gM1o30gZ/FJWX0Qcr54MOETsWFR0sMN5lZ6MsYn5NFSMsYr5pMH0ulccRlZFPpNIzMUkJlW8Vl5lyFllAoAFtlAor5WscsfFFsssX6blIssyesslXlysyyr2mlDZlsUYpsMZRFFsxskV1s12B5Fl8cDszld8rswFYllZgcXENl6Vfgvsr5Cckc0crIalDcwQhGScQga2WVDZmc1oaVGYDVRVwQxceVzVbVFcYVqp1cTsmFMFWmSVDlPcrc1FU8ncHURVw8jV41W8hMqa0148HV7o08mVbkyVO8q868GFA1tkW1e8O1r5r8l8jg18GF5V98K2p151x1D8b8H8UF0F%2B191f815w1XFtp4C1lc1d8319ln1xiXgcCCCgenlSiwNqCqiH14lxiuCy5v1GYOCECr5xCxliN7oaNANsNjkLC8oGNM4IirCPVX13Cu1ZVMFIiT4qN9C/CeMBNfIIidNNNMijg0V4NzCrNiVfqyVyieMdkGZlN9CcKJNxieiK1hNeiqNWqTVmNWqr5tKDiTi2AFNtkitbGotDKayEtfIQSfiCtMSOtDKZKmtZECSySgtat6SySCtpSpiHNcceSUkBSVimt9SjSH5z1oyM8lSUY1SipG1I1PSHlDtByHSPlbtgypFodLyUds0r5SyusPkqtoyK0/loVMNlZwQ2tDNAKWybtOy0YRthy0YCdlycgpyud0YVyZdby40KdFyddtdb8xdvy8YZdoKrdoKHd/NYNMdsKvdZdO8rdKKBd2Krd2KZdhtltoyftRKZdit/doaitC9DKrdLKC9PZVdXKAd9dQdtUK0rdIqBdMqrdMqZdLGWqCNXtFyl9KqZdJqfdS9k6j9D9s1295qD9WcrdjWD9HqP9HqZdgae029wDkOIFgNnKL2HUM9GaCamdDZKa/coDi1BdJaBaz9vKeapaC6aDTaj61ata2Al12Y%2BDLaRDQDcWsDxacWlD1YoD06aDjirdMYuDCDqp2YS6uVmDUDXDCd26stmK%2B6Ql9FBKF6yguwLFpY563al6gdkDMjUGMVf0ijl6Ij0QIlVAdVqpBDlmt6PDujN6fSr5X6b6EYyjD6r6P6EYr5wGgjfIwGtjkGNG19l18GoZSGmtzW9j2AzWtjuGRtl9/jmq/p9YbjVGUGnj7Dtpl9DGFjlG9Gytr5vGKtudKTyTDKomaTmT3ku9hElZGmqTPDhTGTymmmUYxTMm5TGTlW9Y1DEmJWpm0TumDm6OaTrTOOmtEcldRt3TtV8jONwW/m7NgV%2BWvmwzr5UWRTPDUzkzg6aWkTYTMFqWoT2NlZBWPjBWkzcYlkRtlWISmtjW3jMzNWGGr5A2PjA25zY24MfmPDA2tzazDZyq02K2PTe1f0Lzy2c25zB2259TPWfz%2B5PNI1l2HoIzDdccYLZkr5z2ydALGYcLhWzT2AX2QgRtaLdFmwDFI4Y4kjrF4YoO/2gOz0AzlZRL4OvFoz0sFLJL4DCJGjiholZLDZiO8YPjbLr5qOdMzpud3L6OykLuWJ40ZOeAFOVONOmAdODOTOYgrO9QbJsuPO/OguwowuTU1JuwQgTAN%2BIIrggwqALAuwbACgCgTAwAoeRAuwBAkrdOuwjOzOxrB%2BJAvepO4ukugg6uJoSr8uiuKuauMumucuOuQoeuhuqAJubJJAsp6wlu1ubJaIWG9u3rQbyrzuGIru7unuKe9%2B6egeoJiwywYeXg%2BReexRXgXAZwcQ0Q8RGIGIAAnLEBiJIBW9IB7hwC0WEX7pwB0TngUVoPnjAH0VXmXiMZXoa9Xv0HXlID4M3q3sQO3p3vfkPn3nviuyPmPhPlPr7qQLPowAQAvkvqnuvpvtvrQLvju1gIfkYCfqvufhYTfnfqvpgI/sgM/isBHm/u26vvQT/iPn/isKvoAXgMATu6AeAUoFAde8foEKAN0VQIgcgagegZgT7hHvMTMQQdIPMSQUseQdkGsSADQXQV/lIcwawWkHflwUIbwRSPwYIcIaIWnuIXgJIfADIe8Y8QoUoa8aoYoTcVoYYWcf8UJ9cd8cCWMJx2wc8dYbx5J%2B0J8Q0AJy4X8RcQCUp%2BJ7cX4YW%2BwF4Fm8ETm%2BEZwJETEXEQkUkSkZIGcF4BkUMdkQ8Hp6W4UeWwnu25220T2xYJ0f2zHkESW60bm55z50UaQKASkHYJIEAA
