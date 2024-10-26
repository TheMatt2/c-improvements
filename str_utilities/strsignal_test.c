#include "strsignal_.h"
#include "str_common.h"
#include "test_common.h"

#include <signal.h> // NSIG


// Output Formatting
#define ROWS NSIG
#define COLUMNS 30

struct test_func test_funcs[] = {
#if HAS_STRSIGNAL_MT_SAFE
    {"strsignal_mt_safe", (void *) strsignal_},
#endif
    {"strsignal_posix", strsignal_posix}
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
