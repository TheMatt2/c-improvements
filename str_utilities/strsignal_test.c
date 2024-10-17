#include "strsignal_.h"
#include "str_common.h"
#include "test_common.h"

#include <signal.h> // NSIG

// Print libc version
#ifdef __GLIBC__
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#endif
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#pragma message "MAC_OS_X_VERSION_MIN_REQUIRED " STR(__MAC_OS_X_VERSION_MIN_REQUIRED)
#endif
#ifdef NSIG
#pragma message "NSIG " STR(NSIG)
#endif
#ifdef HAS_STRSIGNAL
#pragma message "HAS_STRSIGNAL " STR(HAS_STRSIGNAL)
#endif
#ifdef HAS_STRSIGNAL_MT_SAFE
#pragma message "HAS_STRSIGNAL_MT_SAFE " STR(HAS_STRSIGNAL_MT_SAFE)
#endif
#ifdef HAS_SIGDESCR_NP
#pragma message "HAS_SIGDESCR_NP " STR(HAS_SIGDESCR_NP)
#endif
#ifdef HAS_SYS_SIGLIST
#pragma message "HAS_SYS_SIGLIST " STR(HAS_SYS_SIGLIST)
#endif

// Output Formatting
#define ROWS 75
#define COLUMNS 30

struct test_func test_funcs[] = {
    {"strsignal_", (const char *(*)(int)) strsignal_},
#if HAS_SIGDESCR_NP
    {"strsignal_sigdescr", strsignal_sigdescr},
#endif /* HAS_SIGDESCR_NP */
#if HAS_STRSIGNAL
    {"strsignal_posix", strsignal_posix},
#endif /* HAS_STRSIGNAL */
#if HAS_SYS_SIGLIST
    {"strsignal_sys_siglist", strsignal_sys_siglist},
#endif /* HAS_SYS_SIGLIST */
    {"strsignal_hardcode", strsignal_hardcode}
};

size_t test_funcs_maxlen[ARRAY_SIZE(test_funcs)];

struct test_table test_table = {
    .test_funcs = test_funcs,
    .test_funcs_maxlen = test_funcs_maxlen,
    .size = ARRAY_SIZE(test_funcs),
    .rows = ROWS,
    .columns = COLUMNS
};

int main()
{
    print_header(&test_table);

    for (size_t i = 0; i < ROWS; i++)
    {
        print_column(i, &test_table);
    }

    print_maxlen(&test_table);
    return 0;
}
