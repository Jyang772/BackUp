NASM64 = nasm -f elf64
GCC64 = gcc -c -m64 -ffreestanding
LD64 = ld -melf_x86_64 -T ../elf_x86_64.x -nostdlib -e main -Ttext 0x200000
OBJCOPY64 = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECTDIRECTORY = temp
SOURCEDIRECTORY = source

all: prepare kernel_64.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)

dep:
	@echo ===    Make Dependancy File    ===	
	make -C $(OBJECTDIRECTORY) -f ../Makefile internal_dependency
	@echo === Dependancy Search Complete ===

execute_internal_build: dep
	make -C $(OBJECTDIRECTORY) -f ../Makefile kernel_64.elf

kernel_64.bin: execute_internal_build
	$(OBJCOPY64) $(OBJECTDIRECTORY)/kernel_64.elf $@

clean:
	rm -f *.bin
	rm -f $(OBJECTDIRECTORY)/*.*

ENTRYPOINTSOURCEFILE = ../$(SOURCEDIRECTORY)/entry_point.s
ENTRYPOINTOBJECTFILE = entry_point.o 
CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(notdir $(patsubst %.c,%.o,$(CSOURCEFILES)))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLYSOURCEFILES)))

$(ENTRYPOINTOBJECTFILE): $(ENTRYPOINTSOURCEFILE)
	$(NASM64) -o $@ $<

%.o: ../$(SOURCEDIRECTORY)/%.c
	$(GCC64) -c $<

%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM64) -o $@ $<

internal_dependency:
	$(GCC64) -MM $(CSOURCEFILES) > dependency.dep

kernel_64.elf: $(CENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD64) -o $@ $^

ifeq (dependency.dep, $(wildcard dependency.dep))
include dependency.dep
endif
