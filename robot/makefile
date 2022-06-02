DEVICE = atmega328p
MCU = atmega328p
AVRDUDE_DEVICE = m328p
DEVICE ?= atmega168
MCU ?= atmega168
AVRDUDE_DEVICE ?= m168

PORT ?= /dev/ttyACM0
# SIM = true

CFLAGS=-g -Wall $(DEVICE_SPECIFIC_CFLAGS) -Os
LDFLAGS=-Wl,-gc-sections -Wl,-relax

include ../shared/os.mk
all: $(if $(SIM), $(TARGET), out.hex)

SOURCES := $(filter-out sim.c, $(wildcard *.c))
HEADERS := $(filter-out sim.h, $(wildcard *.h))
include ../shared/makefile

# simulation
CFLAGS += $(if $(SIM), -DW2_SIM -DDBG_ENABLE_COLOR, -mcall-prologues -mmcu=$(MCU))
LDFLAGS += $(if $(SIM), , -lpololu_$(DEVICE))
PREFIX := $(if $(SIM), , avr-)
SOURCES += $(if $(SIM), sim.c, )
HEADERS += $(if $(SIM), sim.h, )

OBJECTS := $(patsubst %.c,%.o, $(SOURCES))

AVRDUDE=avrdude
CC=$(PREFIX)gcc
OBJ2HEX=$(PREFIX)objcopy

clean::
	rm -f *.o out.hex $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS)

.o:
	$(CC) -c $(CFLAGS) $<

out.hex: $(TARGET)
	$(OBJ2HEX) -R .eeprom -O ihex $< $@
	$(info build $(BUILD_STR) complete)

flash: out.hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c avrisp2 -P $(PORT) -U flash:w:out.hex

format:
	$(eval SOURCES := $(filter-out sim.c, $(SOURCES)))
	$(eval HEADERS := $(filter-out sim.h, $(HEADERS)))
	clang-format -i $(SOURCES) $(HEADERS)
	clang-tidy --fix-errors $(SOURCES) $(HEADERS)

compile_commands: clean
	compiledb make
