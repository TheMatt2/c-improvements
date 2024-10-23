#ifndef TEST_COMMON_H
#define TEST_COMMON_H

/*
 * Common test code for testing functions, considering all of the tests
 * are for functions with the approximate signature:
 *   const char *func(int);
 *
 * Where that char buf does not get deallocated.
 */
#include "str_common.h"

#include <stddef.h>
#include <stdbool.h>


// Print GLIBC version
#ifdef __GLIBC__
#pragma message "GLIBC " STR(__GLIBC__) "." STR(__GLIBC_MINOR__)
#endif /* __GLIBC__ */
#ifdef __MUSL__
#pragma message "MUSL"
#endif /* __MUSL__ */
#pragma message "__STDC_WANT_LIB_EXT1__ " STR(__STDC_WANT_LIB_EXT1__)

// All internal methods that can activated
const char* strerror_s_safe(int errnum);
const char* strerror_printf_m(int errnum);
const char* strerror_posix(int errnum);

const char* strsignal_posix(int signum);

const char* strerrorname_gnu_np(int errnum);
const char* strerrorname_printf_m(int errnum);
const char* strerrorname_hardcode(int errnum);

const char* strsignalname_sigabbrev_np(int signum);
const char* strsignalname_sig2str(int signum);
const char* strsignalname_sys_signame(int signum);
const char* strsignalname_sys_sigabbrev(int signum);
const char* strsignalname_hardcode(int signum);

struct test_func {
    char *name;
    const char* (*func)(int);
};

struct test_table {
    struct test_func *test_funcs;
    size_t *test_funcs_maxlen;
    size_t size;
    // Number of rows to print in table
    unsigned int rows;
    // Width of each test function output for formatting
    unsigned int columns;
};

// Print column headers
void print_header(struct test_table *test_table);

// Print column with function values
void print_column(int value, struct test_table *test_table);

// Print max lengths in each column
void print_maxlen(struct test_table *test_table);
#endif /* TEST_COMMON_H */
