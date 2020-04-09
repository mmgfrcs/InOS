KRN_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c src/cpu/x86/*.c)
HEADERS = $(wildcard src/kernel/*.h src/drivers/*.h src/cpu/x86/*.h)
OBJS = ${KRN_SOURCES:.c=.o src/cpu/x86/interrupt.o}

bootsect: src/cpu/x86/boot/boot_sector.bin kernel.bin
	mkdir -p bin/img
	cat $^ > bin/img/os-image.bin

kernel.bin: src/cpu/x86/boot/kernel_entry.o ${OBJS}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	i686-elf-gcc -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -i src/cpu/x86/boot/ $< -f elf -o $@

%.bin: %.asm
	nasm -i src/cpu/x86/boot/ $< -f bin -o $@

iso:
	mkdir -p src/iso
	cd bin && dd if=/dev/zero of=floppy.img bs=1024 count=1440 && dd if=img/os-image of=floppy.img seek=0 count=1 conv=notrunc && mv floppy.img iso/ && genisoimage -quiet -V 'InOS' -input-charset iso8859-1 -o iso/inos.iso -b floppy.img -hide floppy.img iso/ && rm -rf iso/floppy.img

clean:
	rm -rf *.bin *.o
	rm -rf bin/*
	rm -rf src/kernel/*.o src/cpu/x86/boot/*.bin src/drivers/*.o src/cpu/x86/boot/*.o src/cpu/x86/*.o
