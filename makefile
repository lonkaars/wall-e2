DEVICE = atmega328p
MCU = atmega328p
AVRDUDE_DEVICE = m328p
DEVICE ?= atmega168
MCU ?= atmega168
AVRDUDE_DEVICE ?= m168

CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) $(DEVICE_SPECIFIC_CFLAGS) -Os
LDFLAGS=-Wl,-gc-sections -lpololu_$(DEVICE) -Wl,-relax

PORT ?= /dev/ttyACM0

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o, $(SOURCES))

AVRDUDE=avrdude
CC=avr-gcc
OBJ2HEX=avr-objcopy 

all: out.hex

clean:
	rm -f *.o out.hex a.out compile_commands.json

a.out: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS)

.o:
	$(CC) -c $(CFLAGS) $<

out.hex: a.out
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

flash: out.hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c avrisp2 -P $(PORT) -U flash:w:out.hex

format:
	clang-format -i $(SOURCES) $(HEADERS)

compile_commands: clean
	bear -- make
