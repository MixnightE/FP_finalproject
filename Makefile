# 變數設定
CC=gcc
CFLAGS=-Iinclude -IGUI -Isrc
DEPS := $(shell find include -name "*.h") GUI/callback.h
OBJ := $(shell find src -name "*.c") GUI/callback.c dist/App.c
TARGET=myproject

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $^ `pkg-config --libs gtk+-3.0` $(CFLAGS)
