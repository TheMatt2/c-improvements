// gcc -std=c11 -Wall ./strsignal_test.c
#define _GNU_SOURCE
// #define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <signal.h>

#define MAX(a,b) ({ \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; \
})


int main()
{
    int maxlen = 0;

    printf("strsignal\n");
    for (int i = 0; i < 70; i++)
    {
        const char *msg = strsignal(i);
        printf("%d: %s\n", i, msg);
        maxlen = MAX(maxlen, strlen(msg));
    }

    printf("Max length %d (+ \\0)\n", maxlen);

    printf("sigdescr_np\n");
    for (int i = 0; i < 35; i++)
    {
        const char *msg = sigdescr_np(i);
        if (msg == NULL) msg = "(null)";
        printf("%d: %s\n", i, msg);
        maxlen = MAX(maxlen, strlen(msg));
    }

    printf("Max length %d (+ \\0)\n", maxlen);

    return 0;
}
