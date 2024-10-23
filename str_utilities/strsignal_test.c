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
#ifdef HAS_STRSIGNAL_MT_SAFE
#pragma message "HAS_STRSIGNAL_MT_SAFE " STR(HAS_STRSIGNAL_MT_SAFE)
#endif

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
