#include "strerror_.h"
#include "str_common.h"
#include "test_common.h"


// Output Formatting
#define ROWS 140
#define COLUMNS 50

struct test_func test_funcs[] = {
#if HAS_STRERROR_MT_SAFE
    {"strerror_mt_safe", (void *) strerror_},
#endif
#if HAS_STRERROR_S
    {"strerror_s_safe", strerror_s_safe},
#endif
#if HAS_PRINTF_M
    {"strerror_printf_m", strerror_printf_m},
#endif
#if HAS_STRERROR_R
    {"strerror_r_xpg", strerror_r_xpg},
#endif
    {"strerror_posix", strerror_posix}
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
