CC := gcc
CFLAGS += -std=c11 -Wall -Os
CFLAGS += -D_GNU_SOURCE -DTEST_STRSIGNAL
# CFLAGS += -g -fsanitize=address -pthread

# musl makes a point of not having a test macro
# If we know it is musl, we can optimize the code, so make a macro exist.
ifneq ("$(shell sh -c 'ldd 2>&1 | grep musl')",)
CFLAGS += -D__MUSL__
endif

TEST_TARGETS = strsignal_test strsignal_race_test strerror_test strerrorname_test

# Disable implicit rules

.SUFFIXES:
.PHONY:
all: $(TEST_TARGETS)

$(TEST_TARGETS): % : strsignal_.o strerror_.o strerrorname_.o test_common.o %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $^

.PHONY: tests
tests: $(TEST_TARGETS)
	@for test in $^; do echo $$test && ./$$test; done

.PHONY: clean
clean:
	rm -f *.o $(TEST_TARGETS)
