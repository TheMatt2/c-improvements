CC := gcc
CFLAGS += -std=c11 -Wall
CFLAGS += -D_GNU_SOURCE -DTEST_STRSIGNAL -DHAS_SYS_SIGLIST
CFLAGS += -g -fsanitize=address -pthread

.PHONY:
all: strsignal_test strsignal_race_test

strsignal_test: strsignal_.o strsignal_test.o
	$(CC) $(CFLAGS) $^ -o $@

strsignal_race_test: strsignal_.o strsignal_race_test.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY:
clean:
	rm -f *.o strsignal_test strsignal_race_test
