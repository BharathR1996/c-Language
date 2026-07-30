# Lesson 9: If-Else Conditions in C and RISC-V Assembly

## Overview
This lesson demonstrates how an if/else-if/else control-flow structure in C is translated into RISC-V assembly. The C function in C-asm.c checks the value of a variable and updates another variable based on the matching branch. The assembly file main.s then calls that function from the program entry point.

## Prerequisites
Basic knowledge of:
- C variables and functions
- simple if/else conditional logic
- the idea of calling a function from assembly

## Concepts Covered
- if/else-if/else decision making in C
- control-flow branching
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
| main.s | Contains the minimal RISC-V assembly that calls the C function. |
| Makefile | Builds the RISC-V ELF binary and prepares the binary output. |
| main.ld | Linker script used for the bare-metal RISC-V target. |

## Key Takeaways
- Conditional logic in C translates into branch instructions in assembly.
- The assembly program can call a C function directly.
- This example focuses on control flow rather than console I/O.

## Exercises (Optional)
1. Change the condition values from 10 and 20 to other numbers and observe the branch behavior.
2. Add a new else-if branch and update the C logic accordingly.
3. Extend the example to print a value using a supported bare-metal-friendly approach.

## Resources
- RISC-V GCC documentation
- Bare-metal embedded C programming basics
