/*
 * Common test code for testing functions, considering all of the tests
 * are for functions with the approximate signature:
 *   const char *func(int);
 *
 * Where that char buf does not get deallocated.
 */
#include <stddef.h>
#include <stdbool.h>

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
