#include "test_common.h"
#include "str_common.h"

#include <stdio.h>
#include <string.h>


// Show Feature Test Macros
#pragma message "__STDC_WANT_LIB_EXT1__ " STR(__STDC_WANT_LIB_EXT1__)
#ifdef __GLIBC__
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#endif /* __GLIBC__ */
#ifdef __MUSL__
#pragma message "MUSL"
#endif /* __MUSL__ */
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#pragma message "MAC_OS_X_VERSION_MIN_REQUIRED " STR(__MAC_OS_X_VERSION_MIN_REQUIRED)
#endif

void print_header(struct test_table *test_table)
{
    printf("###  ");
    for (size_t i = 0; i < test_table->size - 1; i++)
    {
        printf("%*s ", -test_table->columns, test_table->test_funcs[i].name);
    }

    // Last column
    printf("%s\n", test_table->test_funcs[test_table->size - 1].name);
}

void print_column(int value, struct test_table *test_table)
{
    printf("%3d: ", value);

    for (size_t i = 0; i < test_table->size; i++)
    {
        const char *msg = test_table->test_funcs[i].func(value);
        if (msg == NULL) msg = "(null)";
        test_table->test_funcs_maxlen[i] = MAX(test_table->test_funcs_maxlen[i], strlen(msg));

        if (i != test_table->size - 1)
        {
            printf("%*s ", -test_table->columns, msg);
        }
        else
        {
            printf("%s\n", msg);
        }
    }
}

void print_maxlen(struct test_table *test_table)
{
    printf("MAX  ");
    for (size_t i = 0; i < test_table->size - 1; i++)
    {
        printf("%*zu ", -test_table->columns, test_table->test_funcs_maxlen[i]);
    }

    // Last column
    printf("%zu\n", test_table->test_funcs_maxlen[test_table->size - 1]);
}
