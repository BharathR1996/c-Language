# Lesson 10: Switch-Case Conditions in C and RISC-V Assembly

## Overview
This lesson demonstrates how a switch-case control-flow structure in C is translated into RISC-V assembly. The C function in C-asm.c evaluates a variable and chooses a matching case. The generated assembly file C-asm.s shows the compiler implementing the logic with comparisons and branches rather than a simple jump table. The example also highlights break statements and fall-through behavior.

## Prerequisites
Basic knowledge of:
- C variables and functions
- switch-case syntax in C
- basic control-flow concepts such as break and default
- how a small assembly program can call a C function

## Concepts Covered
- switch-case decision making in C
- case labels and the default case
- break statements
- fall-through behavior when break is omitted
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
| C-asm.c | Contains the C implementation of the switch-case logic, including break and fall-through behavior. |
| C-asm.s | Generated RISC-V assembly from the C source, showing the compiler’s branching approach. |
| main.s | Contains the minimal RISC-V assembly that calls the C function from the program entry point. |
| Makefile | Builds the RISC-V ELF binary and creates the raw binary output. |
| main.ld | Linker script used for the bare-metal RISC-V target. |

## How the switch-case works in C
The C function uses a switch statement on the variable `i`.

```c
switch (i)
{
    case 1:
        j = j + 1;
        break;
    case 2:
        j = j + 2;
        break;
    case 3:
        j = j + 3;
    default:
        j = j + 4;
}
```

In this example:
- `i` is initialized to `10`.
- None of the `case 1`, `case 2`, or `case 3` labels match.
- The program falls to the `default` case.
- Because `case 3` does not end with `break`, execution continues into the `default` block.

This demonstrates that `switch` is a compact way to branch based on a value, and that `break` can prevent fall-through.

## How switch-case maps to assembly
The generated assembly in C-asm.s follows a clear pattern that matches the C source:
- `li` instructions initialize the local variables `i` and `j` on the stack.
- `lw` loads the value of `i` from memory into a register.
- `li` loads the comparison constant `3`.
- `beq` checks whether `i` equals `3` and jumps to the case-3 block when it does.
- `bgt` checks whether `i` is greater than `3` and branches to the default-style path.
- `beq` checks whether `i` equals `1` or `2` and jumps to the corresponding case blocks.
- `j` is used to skip over the remaining logic once a matching branch has completed.

In this example, the compiler does not use a jump table. Instead, it uses a sequence of comparisons and conditional branches, which is why the assembly contains labels such as `.L2`, `.L3`, `.L4`, `.L5`, and `.L6`.

## Program execution flow from main.s
The startup code in main.s is minimal and shows how a bare-metal RISC-V program can call a C function:

```asm
_start:
    li x2, 0x80002000
    jal bharath
j .
```

- `_start` is the entry point.
- `li x2, 0x80002000` initializes the stack pointer register with a memory address.
- `jal bharath` jumps and links to the `bharath` function.
- `j .` creates an infinite loop so the program stays halted after the function returns.

## Compilation and build flow
The build process for this lesson is handled by the Makefile:

1. The C source file `C-asm.c` is compiled with `riscv64-unknown-elf-gcc` using the `assembler` target.
2. The assembly and C object code are linked into a bare-metal ELF executable named `main.elf`.
3. `riscv64-unknown-elf-objcopy` converts the ELF file into a raw binary `main.bin`.
4. QEMU can load the resulting ELF file for debugging or execution.

## Key Takeaways
- `switch` is useful when a program must choose between multiple constant values.
- `case` labels define the possible paths.
- `break` stops execution from falling into the next case.
- When `break` is omitted, execution falls through to the next case or to `default`.
- `default` handles values that do not match any case.

## Exercises (Optional)
1. Change the value of `i` to `1`, `2`, or `3` and observe how the behavior changes.
2. Add a `break` to the `case 3` block and see how it changes the flow.
3. Add a new case and update the logic to match it.

## Resources
- RISC-V GCC documentation
- Bare-metal embedded C programming basics
