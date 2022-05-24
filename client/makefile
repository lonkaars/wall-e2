CC = gcc
LD = gcc
RM = rm -f
CFLAGS =
EXECNAME = main

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
include ../shared/makefile
OBJECTS := $(patsubst %.c,%.o, $(SOURCES))

all: main

.o:
	$(CC) -c $(CFLAGS) $<

$(EXECNAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECNAME)

clean:
	$(RM) $(EXECNAME) *.o

format:
	clang-format -i $(SOURCES) $(HEADERS)
	clang-tidy --fix-errors $(SOURCES) $(HEADERS)

compile_commands: clean
	bear -- make

