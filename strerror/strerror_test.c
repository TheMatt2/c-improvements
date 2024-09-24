#if __STDC_VERSION__ >= 202311L
#define NO_DISCARD [[ nodiscard ]]
#elif defined(__GNUC__)
#define NO_DISCARD __attribute__ ((warn_unused_result))
#else
#define NO_DISCARD /* nothing */
#endif

NO_DISCARD const char* strerror_(int errnum);

#define __STDC_WANT_LIB_EXT1__ 1
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

#include <pthread.h>


/* Define thread_local for thread specific buffer */
#if __STDC_VERSION__ <= 199901L
#define thread_local __thread
#elif __STDC_VERSION__ < 202311L
// C23 changes thread_local to be a keyword
#define thread_local _Thread_local
#endif


// Just call strerror() when safe.
const char* strerror_mt_safe(int errnum)
{
    return strerror(errnum);
}

// Use strerror_s() to print error message.
const char* strerror_s_(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    strerror_s(errbuf, sizeof(errbuf), errnum);
    return errbuf;
}

// Use printf("%m") to get errno string
// Pedantic warnings warns about usage of %m, but this code already checks
// %m is only used if available.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif /* __GNUC__ */
const char* strerror_printf_m(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    int prev_errno = errno;
    errno = errnum;

    snprintf(errbuf, sizeof(errbuf) - 1, "%m");
    errno = prev_errno;
    return errbuf;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */

// POSIX General Solution.
const char* strerror_pthread(int errnum)
{
    // Thread local buffer for errors.
    // Longest EN error message on linux is EILSEQ is 49 characters + null.
    static thread_local char errbuf[50] = {0};
    const char *buf;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Call strerror() to get error status
    buf = strerror(errnum);
    // Copy to a thread specific buffer. Always leave null terminator.
    buf = strncpy(errbuf, buf, sizeof(errbuf) - 1);
    pthread_mutex_unlock(&mutex);
    return buf;
}

struct strerror_func {
    char *name;
    void *func;
}

strerror_func test_funcs[] = {
    {"strerror_mt_safe",    &strerror_mt_safe},
    {"strerror_s_",         &strerror_s_},
    {"strerror_printf_m",   &strerror_printf_m},
    {"strerror_pthread",    &strerror_pthread},
    {NULL, NULL}
};

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

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

}
