SOURCES += $(wildcard ../shared/*.c)
HEADERS += $(wildcard ../shared/*.h)

# debug build info string
BUILD_STR=$(shell git update-index -q --refresh; git describe --tags --dirty='*' --broken='x' | cut -c1-20)
CFLAGS += -DW2_BUILD_STR=\"$(BUILD_STR)\"

# os info
OS=$(strip $(shell uname -o))
ifeq ($(OS),GNU/Linux)
CFLAGS += -DW2_HOST_LINUX
endif
ifeq ($(OS),Msys)
CFLAGS += -DW2_HOST_WIN32
endif

clean::
	rm -f ../shared/*.o
