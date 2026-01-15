CC = g++

CFLAGS = -Wall -Wextra -Wpedantic -O3

SRC = $(wildcard src/*.cpp)
TARGET = cppcat

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

clean:
	rm -rf $(TARGET)