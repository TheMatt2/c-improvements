CC := gcc
CFLAGS += -std=c11 -Wall -Os
CFLAGS += -D_GNU_SOURCE -DTEST_STR_UTILS
# CFLAGS += -g -fsanitize=address -pthread

# musl makes a point of not having a test macro
# If we know it is musl, we can optimize the code, so make a macro exist.
ifneq ($(shell sh -c 'ldd 2>&1 | grep musl'),)
CFLAGS += -D__MUSL__
endif

TEST_TARGETS := strsignal_test strsignal_race_test
TEST_TARGETS += strerror_test strerrorname_test strsignalname_test

STR_UTILS := strsignal_.o strerror_.o strerrorname_.o strsignalname_.o test_common.o

# Disable implicit rules
.SUFFIXES:

.PHONY:
all: $(TEST_TARGETS) main

$(TEST_TARGETS): % : $(STR_UTILS) %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $^

main: % : $(STR_UTILS) %.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: tests
tests: $(TEST_TARGETS)
	@for test in $^; do echo $$test && ./$$test; done

.PHONY: clean
clean:
	rm -f *.o $(TEST_TARGETS) main
