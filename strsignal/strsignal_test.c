#include "strsignal_.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>


// Max function that only evaluates its values once
#define MAX(a,b) ({ \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; \
})

// Macro to get number of elements in array
#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

// Macro to put quotes around a macro
#define XSTR(x) #x
#define STR(x) XSTR(x)

// Print GLIBC version
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#pragma message "NSIG" STR(NSIG)

// Output Formatting
// #define ROWS 35
#define ROWS 75
#define COLUMNS 25

struct test_func {
    char *name;
    const char* (*func)(int);
};

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
