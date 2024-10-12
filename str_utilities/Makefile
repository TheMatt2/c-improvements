CC := gcc
CFLAGS += -std=c11 -Wall
CFLAGS += -D_GNU_SOURCE -DTEST_STRSIGNAL
CFLAGS += -g -fsanitize=address -pthread

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
