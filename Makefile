.PHONY: all run clean

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99
OUTPUT = build/example

all: run

run: build
	./$(OUTPUT)

build: src/*.h src/*.c
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c

clean:
	rm -f $(OUTPUT)
