#include "strerror_.h"
#include "str_common.h"
#include "test_common.h"


// Print GLIBC version
#ifdef __GLIBC__
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#endif /* __GLIBC__ */
#ifdef __MUSL__
#pragma message "MUSL " STR(__MUSL_VER_MAJOR__) "." STR(__MUSL_VER_MINOR__)
#endif /* __MUSL__ */
#pragma message "__STDC_WANT_LIB_EXT1__" STR(__STDC_WANT_LIB_EXT1__)

// Output Formatting
#define ROWS 140
#define COLUMNS 50

struct test_func test_funcs[] = {
#if HAS_STRERROR_S
    {"strerror_s_safe", strerror_s_safe},
#elif HAS_PRINTF_M
    {"strerror_printf_m", strerror_printf_m},
#endif
    {"strerror_posix", strerror_posix},
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
