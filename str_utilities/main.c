#include "strerror_.h"
#include "strsignal_.h"
#include "strerrorname_.h"
#include "strsignalname_.h"

#include <stdio.h>


void usage(char *argv[]) {
    fprintf(stderr,
        "Usage: %s strerror|strsignal|strerrorname|strsignalname [value]\n", argv[0]);
}

int main(int argc, char *argv[]) {
    int value = 0;
    char *func_name = NULL;
    const char* (*func)(int) = NULL;

    switch (argc) {
      case 3:
        // Parse second argument, an integer
        if (sscanf(argv[2], "%d", &value) != 1) {
            fprintf(stderr, "error: invalid value: %s", argv[2]);
            usage(argv);
            return 1;
        }
        // fallthrough
      case 2:
        // Parse first argument, the function to call
        func_name = argv[1];
        if (strcmp(func_name, "strerror") == 0) {
            func = (void *) strerror_;
        } else if (strcmp(func_name, "strsignal") == 0) {
            func = (void *) strsignal_;
        } else if (strcmp(func_name, "strerrorname") == 0) {
            func = (void *) strerrorname_;
        } else if (strcmp(func_name, "strsignalname") == 0) {
            func = (void *) strsignalname_;
        } else {
            fprintf(stderr, "error: invalid error function: %s", func_name);
            usage(argv);
            return 1;
        }
        break;
      case 1:
        // Show usage
        usage(argv);
        return 0;
      default:
        // General error. Show usage.
        usage(argv);
        return 1;
    }

    // Call the function
    const char *msg = func(value);

    printf("%s(%d) = %s\n", func_name, value, msg);
    return 0;
}
