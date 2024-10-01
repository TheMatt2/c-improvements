CC := gcc
CFLAGS += -std=c11 -Wall
CFLAGS += -D_GNU_SOURCE -DTEST_STRSIGNAL -DHAS_SYS_SIGLIST
CFLAGS += -g -fsanitize=address -pthread

TEST_TARGETS = strsignal_test strsignal_race_test strerror_test

# Disable implicit rules

.SUFFIXES:
.PHONY:
all: $(TEST_TARGETS)

$(TEST_TARGETS): % : strsignal_.o strerror_.o %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $^

.PHONY:
clean:
	rm -f *.o $(TEST_TARGETS)
