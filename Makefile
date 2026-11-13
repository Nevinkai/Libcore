CC      = cc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
SAN     = -fsanitize=address,undefined

OBJS = build/vec.o build/str.o

all: build/libcore.a

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/libcore.a: $(OBJS)
	ar rcs $@ $^

test: build/libcore.a tests/test_main.c
	$(CC) $(CFLAGS) $(SAN) tests/test_main.c src/*.c -o build/tests
	./build/tests

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: all test clean