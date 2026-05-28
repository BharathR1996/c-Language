# ============================================
# Makefile Template - For C Programs
# ============================================
# Uncomment the C section below if using main.c

# --- C Program Compilation ---
# CC = gcc
# CFLAGS = -Wall -Wextra -std=c99
# PROGRAM = program
#
# $(PROGRAM): main.c
# 	$(CC) $(CFLAGS) -o $(PROGRAM) main.c
#
# run: $(PROGRAM)
# 	./$(PROGRAM)
#
# clean:
# 	rm -f $(PROGRAM) *.o


# ============================================
# Makefile Template - For RISC-V Assembly
# ============================================
# Uncomment the assembly section below if using main.s

assembler: C-asm.c
	riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld C-asm.c -S

assembler_without_gdb: C-asm.c
	riscv64-unknown-elf-gcc -O0 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld C-asm.c -S -o main.s
	
compile: main.s main.ld
	riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.s -o main.elf
	riscv64-unknown-elf-objcopy -O binary main.elf main.bin

printbinary: main.bin
	xxd -e -c 4 -g 4 main.bin

startqemu: main.elf
	qemu-system-riscv32 -S -M virt -nographic -bios none -kernel main.elf -gdb tcp::1234

startgdb: main.elf
	gdb-multiarch main.elf -ex "target remote localhost:1234" -ex "break _start" -ex "continue" -q

clean:
	rm -rf *.out *.bin *.elf *.gdb_history

help:
	@echo "Makefile Usage:"
	@echo "  assembler:				Compile C-asm.c to assembly (with debug symbols)"
	@echo "  assembler_without_gdb: 		Compile C-asm.c to assembly (without debug symbols)"
	@echo "  compile: 				Compile main.s to main.elf and create main.bin"
	@echo "  printbinary: 				Display the contents of main.bin in hexadecimal format"
	@echo "  startqemu: 				Start QEMU with main.elf for debugging"
	@echo "  startgdb: 				Start GDB and connect to QEMU for debugging"
	@echo "  clean: 				Remove generated files"