all: Bootloader Kernel_32 Kernel_64 utility disk.img

Bootloader:
	@echo
	@echo === Build Bootloader ===
	@echo

	make -C bootloader

	@echo
	@echo ===  Build Complete  ===
	@echo

Kernel_32:
	@echo
	@echo === Build 32-bit Kernel ===
	@echo

	make -C kernel_32 

	@echo
	@echo ===   Build Complete    ===
	@echo

Kernel_64:
	@echo
	@echo === Build 64-bit Kernel ===
	@echo

	make -C kernel_64 

	@echo
	@echo ===   Build Complete    ===
	@echo

utility:
	@echo
	@echo ===  Build Utility   ===
	@echo

	make -C util
	mv util/image_maker/image_maker .

	@echo
	@echo ===  Build Complete  ===
	@echo

disk.img: bootloader/bootloader.bin kernel_32/kernel_32.bin kernel_64/kernel_64.bin
	@echo
	@echo === Build Disk Image ===
	@echo

	./image_maker $^

	@echo
	@echo ===  Build Complete  ===
	@echo

clean:
	make -C bootloader clean
	make -C kernel_32 clean
	make -C kernel_64 clean
	make -C util clean
	rm -f disk.img
