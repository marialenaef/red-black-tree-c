CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm
TARGET = rbt
SRC = src/red_black_tree.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
