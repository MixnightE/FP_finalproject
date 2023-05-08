# which OS
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
endif

CC=

ifndef CC
	ifeq ($(detected_OS),Windows)
		CC=cl
	else ifeq ($(detected_OS),Darwin)
		CC=clang
	else
		CC=gcc
	endif
endif

CFLAGS=

ifndef CFLAGS
	ifeq ($(CC),cl)
		CFLAGS=/W4 /sdl
	else
		CFLAGS:=-Wall -Wextra -std=$(C_STD)
	endif
endif

ifneq (,$(DEBUG))
	ifeq ($(CC),cl)
		CFLAGS+=/DDEBUG /Zi /Od
	else
		CFLAGS+=-DDEBUG -g -O0
	endif
else
	ifeq ($(CC),cl)
		CFLAGS+=/O2
	else
		CFLAGS+=-O2
	endif
endif

export CFLAGS

ifeq ($(detected_OS),Windows)
	RM=del /q /f
endif

export RM

# modify it
SOURCE=$(PROGRAM:.exe=).c

ifeq ($(CC),cl)
	OBJS=$(SOURCE:.c=.obj)
else
	OBJS=$(SOURCE:.c=.o)
endif

export OBJS

$(PROGRAM): $(OBJS)
ifeq ($(CC),cl)
    $(CC) /Fe:$(PROGRAM) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
else
    $(CC) -o $(PROGRAM) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
endif

%.obj: %.c
    $(CC) /c $< $(CFLAGS)

%.o: %.c
    $(CC) -c $< $(CFLAGS)