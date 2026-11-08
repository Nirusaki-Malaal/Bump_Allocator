CC      := gcc
CFLAGS  := -Wall -std=c11 -Iinclude
SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:src/%.c=build/%.o)
BIN     := neutron

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(BIN)
	./$(BIN)

clean:
	rm -rf build $(BIN)
