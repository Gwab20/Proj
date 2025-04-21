CC := g++
CFLAGS := -I./src -std=c++17 -Wall -Wextra
LDFLAGS := -lwinmm
TARGET := game.exe

SRC_FILES := $(wildcard src/*.cpp)

all:
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET) $(LDFLAGS)

clean:
	del $(TARGET) 2> nul || exit 0

run: all
	./$(TARGET)

.PHONY: all clean run