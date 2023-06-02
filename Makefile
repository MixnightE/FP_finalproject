# 變數設定
CC=gcc
CFLAGS=-Iinclude src
DEPS := $(shell find include -name "*.h")
OBJ := $(shell find src -name "*.c") dist/main.c
TARGET=myproject

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
