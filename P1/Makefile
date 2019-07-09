
TARGET = output
CC = g++
CFLAGS = -Wall

.PHONY: default all clean

default: $(TARGET)

all: default

OBJECTS = main.cpp
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

run:
	./$(TARGET)

test:
	./$(TARGET) < input.txt
clean:
	-rm -f *.o
	-rm -f $(TARGET)