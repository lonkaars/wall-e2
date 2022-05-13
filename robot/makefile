DEVICE = atmega328p
MCU = atmega328p
AVRDUDE_DEVICE = m328p
DEVICE ?= atmega168
MCU ?= atmega168
AVRDUDE_DEVICE ?= m168
SIM = 

PORT ?= /dev/ttyACM0

CFLAGS=-g -Wall $(DEVICE_SPECIFIC_CFLAGS) -Os
LDFLAGS=-Wl,-gc-sections -Wl,-relax

CFLAGS += $(if $(SIM), -DW2_SIM, -mcall-prologues -mmcu=$(MCU))
LDFLAGS += $(if $(SIM), , -lpololu_$(DEVICE))

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o, $(SOURCES))

PREFIX := $(if $(SIM), , avr-)

AVRDUDE=avrdude
CC=$(PREFIX)gcc
OBJ2HEX=$(PREFIX)objcopy

BUILD_STR=$(shell git update-index -q --refresh; git describe --tags --dirty='*' --broken='x' | cut -c1-20)
CFLAGS += -DW2_BUILD_STR="$(BUILD_STR)"

all: $(if $(SIM), a.out, out.hex)

clean:
	rm -f *.o out.hex a.out compile_commands.json

a.out: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS)

.o:
	$(CC) -c $(CFLAGS) $<

out.hex: a.out
	$(OBJ2HEX) -R .eeprom -O ihex $< $@
	$(info build $(BUILD_STR) complete)

flash: out.hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c avrisp2 -P $(PORT) -U flash:w:out.hex

format:
	SOURCES := $(filter-out sim.c, $(SOURCES))
	HEADERS := $(filter-out sim.h, $(HEADERS))
	clang-format -i $(SOURCES) $(HEADERS)
	clang-tidy --fix-errors $(SOURCES) $(HEADERS)

compile_commands: clean
	bear -- make
