#include "strsignalname_.h"
#include "str_common.h"
#include "test_common.h"


// Output Formatting
#define ROWS NSIG
#define COLUMNS 25

struct test_func test_funcs[] = {
#if HAS_SIGABBREV_NP
    {"strsignalname_sigabbrev_np", strsignalname_sigabbrev_np},
#endif /* HAS_SIGABBREV_NP */
#if HAS_SYS_SIGNAME
    {"strsignalname_sys_signame", strsignalname_sys_signame},
#endif /* HAS_STRERRORNAME_NP */
    {"strsignalname_hardcode", strsignalname_hardcode}
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
