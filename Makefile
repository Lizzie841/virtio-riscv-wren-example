CC := riscv64-elf-gcc
CFLAGS := -ffreestanding -I$(PWD)/libc -I$(PWD)vm

LD := riscv64-elf-gcc
LDFLAGS := -nostdlib

VM_SOURCES := \
	vm/wren_compiler.o \
	vm/wren_core.o \
	vm/wren_debug.o \
	vm/wren_primitive.o \
	vm/wren_utils.o \
	vm/wren_value.o \
	vm/wren_vm.o \
	libc/libc.o

all: build

build: libvm.a

clean:
	rm vm/*.o
	rm libc/*.o

.PHONY: all build clean

libvm.a: $(VM_SOURCES)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
