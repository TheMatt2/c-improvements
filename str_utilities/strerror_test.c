#include "strerror_.h"
#include "str_common.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Print GLIBC version
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#pragma message "NSIG" STR(NSIG)
#pragma message "__STDC_WANT_LIB_EXT1__" STR(__STDC_WANT_LIB_EXT1__)

// Output Formatting
// #define ROWS 35
#define ROWS 140
#define COLUMNS 50

struct test_func {
    char *name;
    const char* (*func)(int);
};

struct test_func test_funcs[] = {
    {"strerror", (void *) strerror},
#if HAS_STRERROR_S
    {"strerror_s_safe", strerror_s_safe},
#elif HAS_PRINTF_M
    {"strerror_printf_m", strerror_printf_m},
#endif
    {"strerror_posix", strerror_posix},
};

size_t test_funcs_maxlen[ARRAY_SIZE(test_funcs)];

void print_header()
{
    printf("###  ");
    for (size_t i = 0; i < ARRAY_SIZE(test_funcs) - 1; i++)
    {
        printf("%-" STR(COLUMNS) "s ", test_funcs[i].name);
    }

    // Last column
    printf("%s\n", test_funcs[ARRAY_SIZE(test_funcs) - 1].name);
}

/*
 * Print column with strsignal info
 */
void print_column(int signum)
{
    printf("%3d: ", signum);

    // printf("SIG%-10s ", sigabbrev_np(signum));

    for (size_t i = 0; i < ARRAY_SIZE(test_funcs); i++)
    {
        const char *msg = test_funcs[i].func(signum);
        if (msg == NULL) msg = "(null)";
        test_funcs_maxlen[i] = MAX(test_funcs_maxlen[i], strlen(msg));

        if (i != ARRAY_SIZE(test_funcs) - 1)
        {
            printf("%-" STR(COLUMNS) "s ", msg);
        }
        else
        {
            printf("%s\n", msg);
        }
    }
}

void print_maxlen()
{
    printf("MAX  ");
    for (size_t i = 0; i < ARRAY_SIZE(test_funcs) - 1; i++)
    {
        printf("%-" STR(COLUMNS) "zu ", test_funcs_maxlen[i]);
    }

    // Last column
    printf("%zu\n", test_funcs_maxlen[ARRAY_SIZE(test_funcs_maxlen) - 1]);
}

int main()
{
    print_header();

    for (size_t i = 0; i < ROWS; i++)
    {
        print_column(i);
    }

    print_maxlen();
    return 0;
}
