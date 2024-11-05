CC := riscv64-elf-gcc
CFLAGS := -mcmodel=medany -ffreestanding -Ilibc -Ivm -O1 -g

LD := riscv64-elf-gcc
LDFLAGS := -Tlibc/linker.ld -lgcc -nostdlib -g

VM_SOURCES := \
	vm/wren_compiler.o \
	vm/wren_core.o \
	vm/wren_debug.o \
	vm/wren_primitive.o \
	vm/wren_utils.o \
	vm/wren_value.o \
	vm/wren_vm.o \
	libc/libc.o \
	libc/start.o

all: build

run: vm.exe
	qemu-system-riscv64 -s -S -M virt -bios none -kernel $<

build: vm.exe

clean:
	rm vm/*.o
	rm libc/*.o

.PHONY: all build clean

vm.exe: $(VM_SOURCES)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.S
	$(CC) $(CFLAGS) $< -c -o $@
