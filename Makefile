TESTCFLAGS := -Wall -g -fprofile-arcs -ftest-coverage
TESTLINKS :=
CFLAGS ?=
LINKS ?=

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: clean test uriparse

nothing:

$(OBJECTS): %.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	CFLAGS="$(TESTCFLAGS)" LINKS="$(TESTLINKS)" $(MAKE) _test
	mv _test test

_test: src/uriparse.o src/test.o
	$(CC) $(CFLAGS) $(LINKS) $^ -o $@

uriparse:
	$(MAKE) _uriparse
	mv _uriparse uriparse

_uriparse: src/uriparse.o src/cli.o
	$(CC) $(CFLAGS) $(LINKS) $^ -o $@

clean:
	rm -f $(OBJECTS) test uriparse

