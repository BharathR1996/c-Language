# Lesson 7: RISC-V `const` and Pointer Behavior

## Overview
This lesson explores how the C `const` qualifier works when a pointer is used to modify a constant value. You'll learn how the compiler handles `const` variables, the warning generated when a non-`const` pointer is assigned to a `const` object, and how RISC-V assembly is generated from this code.

## Prerequisites
- Lesson 5: RISC-V C and Assembly recommended
- Lesson 6: RISC-V C Data Types recommended
- Basic understanding of C pointers and the `const` qualifier

## Concepts Covered
- C `const` qualifier semantics
- Pointer assignment to `const` objects
- Compiler warnings for discarded qualifiers
- RISC-V C to assembly compilation
- Linker script usage for RISC-V builds

## Build & Run

### Compile
```bash
cd 07-riscv-C-const
make compile
```

If you want to run the build steps manually:
```bash
cd 07-riscv-C-const
riscv64-unknown-elf-gcc -O0 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.c -S -o main.s
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.s -o main.elf
riscv64-unknown-elf-objcopy -O binary main.elf main.bin
```

### Expected Output
```
Assembly file generated showing a const integer stored in memory,
pointer arithmetic to that storage, and a compiler warning about
discarding the const qualifier.
```

> Note: This lesson is focused on compiler behavior and assembly generation. The source defines a function and does not include a complete runtime `main` program.

## Files

| File | Purpose |
|------|---------|
| `main.c` | C source showing a `const int` and pointer modification attempt |
| `main.ld` | RISC-V linker script placing `.text` in RAM |
| `main.s` | Generated RISC-V assembly output |
| `main.elf` | Linked RISC-V ELF executable image |
| `main.bin` | Raw binary image produced by `objcopy` |
| `Makefile` | Build automation for compiling and inspecting output |

## Key Takeaways
- `const` in C is a compile-time qualifier; using a non-`const` pointer to modify it is undefined behavior.
- The compiler emits a warning when the `const` qualifier is discarded.
- RISC-V assembly generation shows how the constant is loaded and how the pointer write is translated.
- `make compile` produces `main.s`, `main.elf`, and `main.bin` for inspection.
- The RISC-V toolchain uses `-march=rv32i -mabi=ilp32` for this lesson.

## Exercises (Optional)
1. Add a `main()` function that calls `bharath()` and compile the program again.
2. Change the pointer type to `const int *pa = &a;` and observe the compiler output.
3. Inspect `main.s` and identify the instructions that store the constant and the pointer write.
4. Modify the linker script to set a different RAM origin and rebuild.

## Resources
- [RISC-V ISA Specification](https://riscv.org/specifications/)
- [RISC-V Calling Convention (ABI)](https://github.com/riscv-non-profit/riscv-elf-psabi-doc)
- [GCC `const` qualifier documentation](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/Type-Attributes.html)
