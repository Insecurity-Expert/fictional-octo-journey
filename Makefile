CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lncurses
TARGET = pingpong
SRC = pingpong.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
