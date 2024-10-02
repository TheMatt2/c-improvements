#include "strsignal_.h"
#include "str_common.h"
#include "test_common.h"


// Print GLIBC version
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#pragma message "NSIG" STR(NSIG)

// Output Formatting
#define ROWS 75
#define COLUMNS 25

struct test_func test_funcs[] = {
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
