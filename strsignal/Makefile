CC := gcc
CFLAGS += -std=c11 -Wall
CFLAGS += -D_GNU_SOURCE -DTEST_STRSIGNAL -DHAS_SYS_SIGLIST
CFLAGS += -g -fsanitize=address -pthread

%.o : %.c
	$(CC) -c $(CFLAGS) $<

strsignal_test: strsignal_.o strsignal_test.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:
clean:
	rm -f *.o strsignal_test
