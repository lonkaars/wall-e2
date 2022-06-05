# os info
OS=$(strip $(shell uname -o))
ifeq ($(OS),GNU/Linux)
CFLAGS += -DW2_HOST_LINUX
LINUX := true
TARGET := a.out
endif
ifeq ($(OS),Msys)
CFLAGS += -DW2_HOST_WIN32
WIN32 := true
TARGET := a.exe
endif