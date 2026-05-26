# Lesson 5: RISC-V C and Assembly Integration

## Overview
This lesson demonstrates how to integrate RISC-V assembly code with C code to create a complete executable program. You'll learn how the assembly entry point calls C functions and how the linker combines object files from different source languages.

## Prerequisites
- Lesson 2: RISC-V Assembly Loop fundamentals
- Lesson 3: RISC-V Assembly Multiplication concepts
- Lesson 4: C-to-Assembly compilation understanding
- Basic knowledge of function calls and calling conventions

## Concepts Covered
- Mixing assembly and C source files in a single project
- Assembly entry point (`_start`) calling C functions
- Function calling conventions in RISC-V
- Linker scripts and memory layout
- Compiler flags for cross-compilation (RISC-V 32-bit)
- Object file linking order and symbol resolution

## Build & Run

### Compile
```bash
cd 05-riscv-C-and-assembly
make compile
```

### Run with QEMU and GDB
```bash
# Terminal 1: Start QEMU
make startqemu

# Terminal 2: Start GDB and connect
make startgdb
```

### View Generated Binary
```bash
make printbinary
```

### Clean Build Artifacts
```bash
make clean
```

## Files

| File | Purpose |
|------|---------|
| `main.s` | RISC-V assembly entry point (`_start`) that initializes stack pointer and calls C function |
| `C-asm.c` | C function implementation (`bharath()`) that returns a value |
| `main.ld` | Linker script defining memory layout and sections (RAM: 0x80000000, 4KB) |
| `Makefile` | Build automation with compilation, binary conversion, QEMU, and GDB targets |

## Compilation Order: Why main.s First?

The compilation command lists source files in a specific order for a critical reason:

```bash
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 \
    -Wl,-Tmain.ld main.s C-asm.c -o main.elf
```

### Why main.s is compiled/linked FIRST:

1. **Entry Point Definition**: `main.s` contains the `_start` symbol, which is the entry point where the program begins execution. The linker must place this at the beginning of the executable.

2. **First Code to Execute**: Since `main.s` is listed first, its object code is placed first in memory. This ensures that when the CPU starts, it executes the `_start` instruction first.

3. **Symbol Resolution**: When the linker processes `main.s` first, it registers the `_start` symbol. When it then processes `C-asm.c`, it can resolve the `bharath` function call from assembly to the C function definition.

4. **Memory Layout**: The linker script (`main.ld`) specifies that all `.text` sections go into RAM starting at 0x80000000. Processing `main.s` first ensures its code is placed at this base address.

5. **Call Sequence**: The execution flow is:
   - CPU jumps to `_start` (defined in main.s)
   - `_start` initializes stack pointer with `li x2, 0x80002000`
   - `jal bharath` instruction calls the C function (defined in C-asm.c)
   - `bharath()` returns 30
   - Program continues with `j .` (infinite loop)

### Consequence of Wrong Order:

If we reversed the order (`main.c C-asm.c main.s`), the linker would:
- Place `C-asm.c` object code first
- Later place `main.s` object code at a different address
- The program might not start at the correct entry point
- This would likely result in undefined behavior or linker errors

## Key Takeaways
- Assembly and C code can be seamlessly integrated in a single project
- The order of source files in compilation matters for entry points and symbol resolution
- The assembly entry point is responsible for setting up the execution environment
- C functions are callable from assembly code following the RISC-V calling convention
- Linker scripts provide fine-grained control over memory layout and symbol placement

## Exercises (Optional)
1. Modify `C-asm.c` to accept parameters and perform calculations
2. Create additional assembly routines that call multiple C functions
3. Experiment with different optimization levels (`-O0`, `-O2`) and observe code changes
4. Trace through execution using GDB breakpoints in both assembly and C code
5. Modify `main.ld` to place code at a different memory address and observe the impact

## Resources
- [RISC-V ISA Specification](https://riscv.org/technical/specifications/)
- [RISC-V Calling Convention](https://github.com/riscv-non-isa/riscv-elf-psabi-doc)
- [GNU Linker Script Documentation](https://sourceware.org/binutils/docs/ld/Scripts.html)
- [GCC Cross-Compiler Documentation](https://gcc.gnu.org/onlinedocs/)
