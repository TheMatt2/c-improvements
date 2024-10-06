#include "strerrorname_.h"
#include "str_common.h"
#include "test_common.h"


// Print GLIBC version
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)

// Output Formatting
#define ROWS 140
#define COLUMNS 25

struct test_func test_funcs[] = {
#if HAS_STRERRORNAME_NP
    {"strerrorname_gnu_np", strerrorname_gnu_np},
#endif /* HAS_STRERRORNAME_NP */
#if HAS_PRINTF_M
    {"strerrorname_printf_m", strerrorname_printf_m},
#endif /* HAS_PRINTF_M */
    {"strerrorname_hardcode", strerrorname_hardcode},
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
