# Lesson 9: If-Else Conditions in C and RISC-V Assembly

## Overview
This lesson demonstrates how an if/else-if/else control-flow structure in C is translated into RISC-V assembly. The C function in C-asm.c checks the value of a variable and updates another variable based on the matching branch. The compiler-generated assembly file C-asm.s contains the low-level instructions for that logic, while main.s provides a minimal program that calls the function from the entry point.

## Prerequisites
Basic knowledge of:
- C variables and functions
- simple if/else conditional logic
- the idea of calling a function from assembly

## Concepts Covered
- if/else-if/else decision making in C
- control-flow branching
- comparing values in assembly
- calling a C function from RISC-V assembly

## Build & Run

### Build
```bash
make compile_all_with_gdb
```

### Inspect the binary
```bash
make printbinary
```

### Run in QEMU
```bash
make startqemu
```

### Expected Output
No console output is produced by this example because the function only updates local variables and returns.

## Files

| File | Purpose |
|------|---------|
| C-asm.c | Contains the C implementation of the if/else-if/else logic. |
| C-asm.s | Generated RISC-V assembly for the C function, including the conditional branches. |
| main.s | Contains the minimal RISC-V assembly that calls the C function. |
| Makefile | Builds the RISC-V ELF binary and prepares the binary output. |
| main.ld | Linker script used for the bare-metal RISC-V target. |

## How the if-condition works in assembly
The C code checks whether `i` is equal to `10`, `20`, or neither. In assembly, this becomes a sequence of comparisons and branches:

- `lw` loads the value of `i` from memory into a register.
- `li` loads the constant `10` or `20` into another register.
- `bne` compares the two registers and jumps to the next label if they are not equal.
- If the comparison succeeds, execution continues with the matching block that increments `j`.
- The `j` instruction is used to skip over later branches after one case has already been handled.

In this example:
1. The first branch checks whether `i == 10`.
2. If not, execution jumps to the next label and checks whether `i == 20`.
3. If neither condition matches, the code falls through to the `else` block and increments `j` by `3`.

This is why the generated assembly in C-asm.s contains labels such as `.L2` and `.L4` and branch instructions like `bne` and `j`.

## Program execution flow from main.s
The startup code in main.s is very small and shows the basic execution flow for this bare-metal example:

```asm
_start:
    li x2, 0x80002000
    jal bharath
j .
```

- `_start` is the program entry point.
- `li x2, 0x80002000` sets up the stack pointer register with a memory address.
- `jal bharath` jumps and links to the `bharath` function, which means the CPU runs the C-based logic and then returns.
- `j .` creates an infinite loop so the program stays halted after the function returns.

This shows how a tiny assembly program can call a C function and then stop in a loop.

## Compilation and build flow
The build process for this lesson is handled by the Makefile and follows this flow:

1. The C source file `C-asm.c` is compiled with `riscv64-unknown-elf-gcc` into assembly using the `assembler` target.
2. The assembly file `main.s` is assembled and linked with the C object code into a bare-metal ELF executable named `main.elf`.
3. `riscv64-unknown-elf-objcopy` converts the ELF file into a raw binary file `main.bin`.
4. QEMU can then load `main.elf` for debugging or execution.

In short, the flow is:

`C-asm.c` -> `C-asm.s` (generated assembly) -> `main.elf` (linked executable) -> `main.bin` (raw binary)

## Key Takeaways
- Conditional logic in C translates into branch instructions in assembly.
- The assembly program can call a C function directly.
- Branches and labels are how the program decides which path to execute.
- This example focuses on control flow rather than console I/O.

## Exercises (Optional)
1. Change the condition values from 10 and 20 to other numbers and observe the branch behavior.
2. Add a new else-if branch and update the C logic accordingly.
3. Extend the example to print a value using a supported bare-metal-friendly approach.

## Resources
- RISC-V GCC documentation
- Bare-metal embedded C programming basics
