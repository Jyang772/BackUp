NASM32 = nasm
GCC32 = gcc -c -m32 -ffreestanding
LD32 = ld -melf_i386 -T ../elf_i386.x -nostdlib -e main -Ttext 0x10200
OBJCOPY32 = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECTDIRECTORY = temp
SOURCEDIRECTORY = source

all: prepare kernel_32.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)

$(OBJECTDIRECTORY)/entry_point.bin: $(SOURCEDIRECTORY)/entry_point.s
	$(NASM32) -o $@ $<

dep:
	@echo ===    Make Dependancy File    ===	
	make -C $(OBJECTDIRECTORY) -f ../Makefile internal_dependency
	@echo === Dependancy Search Complete ===

execute_internal_build: dep
	make -C $(OBJECTDIRECTORY) -f ../Makefile kernel_32.elf

$(OBJECTDIRECTORY)/kernel_32.elf.bin: execute_internal_build
	$(OBJCOPY32) $(OBJECTDIRECTORY)/kernel_32.elf $@

kernel_32.bin: $(OBJECTDIRECTORY)/entry_point.bin $(OBJECTDIRECTORY)/kernel_32.elf.bin
	cat $^ > $@

clean:
	rm -f *.bin
	rm -f $(OBJECTDIRECTORY)/*.*

CENTRYPOINTOBJECTFILE = main.o
CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(subst Main.o, ,$(notdir $(patsubst %.c,%.o,$(CSOURCEFILES))))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLYSOURCEFILES)))

%.o: ../$(SOURCEDIRECTORY)/%.c
	$(GCC32) -c $<

%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM32) -f elf32 -o $@ $<

internal_dependency:
	$(GCC32) -MM $(CSOURCEFILES) > dependency.dep

kernel_32.elf: $(CENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD32) -o $@ $^

ifeq (dependency.dep, $(wildcard dependency.dep))
include dependency.dep
endif
