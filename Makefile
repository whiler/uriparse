CFLAGS = -Wall -g -fprofile-arcs -ftest-coverage
LINKS =

TARGET = test
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: clean

default: $(TARGET)

$(OBJECTS): %.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINKS) $^ -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
