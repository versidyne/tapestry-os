# Makefile for Vexis OS x86

# Directory Locations
MAIN=src
CORE=$(MAIN)/core
DRIVERS=$(MAIN)/drivers
LIB=$(MAIN)/lib
MM=$(MAIN)/mm
NET=$(MAIN)/net
PROC=$(MAIN)/proc
UI=$(MAIN)/ui
VFS=$(MAIN)/vfs

# File Locations
SOURCES=$(CORE)/boot.o $(CORE)/main.o $(CORE)/common.o $(CORE)/cpu.o $(CORE)/acpi.o $(CORE)/apm.o $(CORE)/ordered_array.o \
        $(DRIVERS)/keyboard.o $(DRIVERS)/monitor.o $(DRIVERS)/mouse.o $(DRIVERS)/pit.o $(DRIVERS)/sound.o $(DRIVERS)/vga.o \
        $(LIB)/stdio.o $(LIB)/string.o $(LIB)/syscall.o \
        $(MM)/descriptor_tables.o $(MM)/gdt.o $(MM)/kheap.o $(MM)/paging.o \
        $(NET)/net.o \
        $(PROC)/isr.o $(PROC)/interrupt.o $(PROC)/process.o $(PROC)/task.o \
        $(UI)/cli.o $(UI)/gui.o \
        $(VFS)/fs.o $(VFS)/initrd.o \

# Detect OS
UNAME := $(shell uname)

# Compilers (Universal)
AS=nasm
ASFLAGS=-felf

#Compilers (Platform)
ifeq ($(UNAME), Linux)
CC=gcc
CFLAGS=-nostdlib -nostdinc -fno-builtin -m32
#CFLAGS=-nostdlib -nostdinc -fno-builtin -m64
CXX=g++
#CXXFLAGS=
CPP=cpp
#CPPFLAGS=
LD=ld
LDFLAGS=-Tlink.ld -melf_i386
endif

ifeq ($(UNAME), Darwin)
CC=gcc-5
CFLAGS=-nostdlib -nostdinc -fno-builtin -m32
#CFLAGS=-nostdlib -nostdinc -fno-builtin -m64
CXX=g++
CXX=g++-5
#CXXFLAGS=
CPP=cpp-5
#CPPFLAGS=
LD=gcc-5
LDFLAGS=
endif

# Make Silent
.SILENT:

# User Functions
all: $(SOURCES) link

clean:
	-rm bin/kernel src/*/*.o

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	$(AS) $(ASFLAGS) $<
