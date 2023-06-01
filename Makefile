# 變數設定
CC=gcc
CFLAGS=-Iinclude
DEPS := cJSON.h fileIO.h
OBJ := src/cJSON.c src/fileIO.c dist/main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
