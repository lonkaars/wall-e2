CC = gcc
LD = gcc
RM = rm -f
CFLAGS = -DW2_LANG_EN_US
LDFLAGS = -lncursesw
EXECNAME = main

include ../shared/os.mk

all: $(EXECNAME)

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
include ../shared/makefile

CFLAGS += $(if $(WIN32),-I/mingw64/include/ncursesw,)

OBJECTS := $(patsubst %.c,%.o, $(SOURCES))

.o:
	$(CC) -c $(CFLAGS) $<

$(EXECNAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECNAME) $(LDFLAGS)

clean::
	$(RM) $(EXECNAME) *.o

format:
	clang-format -i $(SOURCES) $(HEADERS)
	clang-tidy --fix-errors $(SOURCES) $(HEADERS)

compile_commands: clean
	compiledb make

