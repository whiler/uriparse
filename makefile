CFLAGS = -Wall -g
LINKS = 

TARGET = a.out
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: cleanall cleanobj clean

default: $(TARGET)

$(OBJECTS): %.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINKS) $^ -o $@

cleanall: cleanobj clean

cleanobj:
	rm -f $(OBJECTS)

clean:
	rm -f $(TARGET)
