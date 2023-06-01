# 變數設定
CC=gcc
CFLAGS=-Iinclude
DEPS := Buff.h Card.h cJSON.h Constant.h Enemy.h Field.h fileIO.h head.h Player.h Relic.h
OBJ := src/Card.c src/cJSON.c src/fileIO.c src/FuncTable.c dist/main.c
TARGET=myproject

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
