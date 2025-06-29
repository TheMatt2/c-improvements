#define _GNU_SOURCE
#define _POSIX_C_SOURCE 202405L

#include <stdio.h>
#include <signal.h>
#include <string.h>

#define SYMVER(s) __asm__(".symver " s)
SYMVER("sys_siglist,sys_siglist@GLIBC_2.3.3");
SYMVER("sys_sigabbrev,sys_sigabbrev@GLIBC_2.3.3");

extern const char *const sys_siglist[];
extern const char *const sys_sigabbrev[];

int main()
{
    printf("sigabbrev_np: %s\n", sigabbrev_np(1));
    printf("sys_siglist: %s\n", sys_siglist[2]);
    printf("sys_sigabbrev: %s\n", sys_sigabbrev[3]);

    char msg[1024];
    sig2str(4, msg);
    printf("sig2str: %s\n", msg);

    return 0;
}
