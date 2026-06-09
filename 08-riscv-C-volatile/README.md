# Lesson 8: RISC-V `volatile` Qualifier and Compiler Optimization

## Overview
This lesson demonstrates how the `volatile` qualifier affects compiler behavior during optimization. You'll learn how the C compiler optimizes away unused local variables without `volatile`, and how the `volatile` keyword forces the compiler to preserve all memory operations even at high optimization levels. This is critical for embedded systems where hardware registers or memory-mapped I/O must be accessed predictably.

## Prerequisites
- Lesson 5: RISC-V C and Assembly recommended
- Lesson 6: RISC-V C Data Types recommended
- Understanding of compiler optimization flags (-O0, -O1, -O2, -O3)

## Concepts Covered
- C `volatile` qualifier and its semantics
- Compiler optimization levels and their effects on code generation
- Dead code elimination and compiler optimization
- Memory operations and side effects
- RISC-V calling conventions
- Hardware register access patterns
- Embedded systems memory-mapped I/O considerations

## Program Details

### C Source Code (without `volatile`)

```c
int bharath()
{
    int a = 10;
    a = a + 1;
    a = a + 20;

    return 0;
}
```

This function:
1. Initializes a local variable `a` to 10
2. Increments `a` by 1 (a = 11)
3. Adds 20 to `a` (a = 31)
4. Returns 0 (the value of `a` is never used)

## Build & Run

### Compile with Optimization (-O1)
```bash
cd 08-riscv-C-volatile
make compile
```

This uses the `assembler_without_gdb` target which compiles with `-O1` optimization:
```bash
riscv64-unknown-elf-gcc -O1 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.c -S -o main.s
```

### Compile without Optimization (-O0)
To see the unoptimized version:
```bash
riscv64-unknown-elf-gcc -O0 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.c -S -o main_O0.s
```

## Expected Output

### With `-O1` Optimization (current main.s)
```asm
bharath:
    li      a0,0
    ret
```

**Analysis**: The compiler completely optimizes away all operations on variable `a` because:
- `a` is a local variable with no external visibility
- Its final value is never used (the function returns 0, not `a`)
- There are no side effects or I/O operations
- Dead code elimination removes all operations

**Code size**: 2 instructions (8 bytes)

### With `-O0` No Optimization (main_O0.s)
```asm
bharath:
    addi    sp,sp,-32           # Allocate 32 bytes on stack
    sw      s0,28(sp)           # Save frame pointer
    addi    s0,sp,32            # Set frame pointer
    li      a5,10               # a = 10
    sw      a5,-20(s0)          # Store 10 to stack
    lw      a5,-20(s0)          # Load a from stack
    addi    a5,a5,1             # a + 1
    sw      a5,-20(s0)          # Store result back
    lw      a5,-20(s0)          # Load a again
    addi    a5,a5,20            # a + 20
    sw      a5,-20(s0)          # Store result back
    li      a5,0                # Return value = 0
    mv      a0,a5               # Move to return register
    lw      s0,28(sp)           # Restore frame pointer
    addi    sp,sp,32            # Deallocate stack
    jr      ra                  # Return
```

**Analysis**: Without optimization, the compiler:
- Allocates a full stack frame (32 bytes, 16-byte aligned)
- Performs all operations exactly as written in source code
- Loads and stores `a` multiple times from memory
- Preserves all variable assignments even though they're unused

**Code size**: 18 instructions (72 bytes)

**Performance impact**: 
- Load/store operations dominate
- Extra memory traffic: 6 stack accesses vs. 0 in optimized version
- Stack frame overhead adds latency

## Files

| File | Purpose |
|------|---------|
| `main.c` | C source with function demonstrating variable operations without volatile |
| `main.s` | Generated RISC-V assembly with `-O1` optimization (optimized away) |
| `main_O0.s` | Generated RISC-V assembly with `-O0` (no optimization) |
| `main.ld` | RISC-V linker script placing `.text` in RAM |
| `main.elf` | Linked RISC-V ELF executable image |
| `main.bin` | Raw binary image produced by `objcopy` |
| `Makefile` | Build automation supporting multiple optimization levels |

## Makefile Compilation Targets

### `assembler_without_gdb` (used by `compile` target)
```makefile
assembler_without_gdb: *.c
    riscv64-unknown-elf-gcc -O1 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld *.c -S -o main.s
```
Compiles C to assembly with `-O1` optimization (dead code elimination enabled)

### `assembler` (debugging version)
```makefile
assembler: *.c
    riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld *.c -S
```
Compiles C to assembly with `-O0` (no optimization) and debug symbols (`-ggdb`)

## Optimization Comparison

| Aspect | -O0 (No Optimization) | -O1 (Basic Optimization) |
|--------|----------------------|--------------------------|
| **Code Size** | 72 bytes (18 instructions) | 8 bytes (2 instructions) |
| **Stack Frame** | 32 bytes allocated | No stack allocation |
| **Load Operations** | 3 (load a twice + return setup) | 0 |
| **Store Operations** | 3 (store a three times) | 0 |
| **Purpose** | Debugging, development | Production, minimal footprint |

## Why This Matters for `volatile`

In **embedded systems and hardware interaction**, local variables are not always "dead code":

### Example: Memory-Mapped Hardware Register
```c
volatile int *hardware_register = (int *)0x40000000;

void read_sensor()
{
    volatile int reading = *hardware_register;  // Must not be optimized away
    reading = reading + 1;                      // Processing required
    *hardware_register = reading;               // Must not be optimized away
}
```

Without `volatile`:
- Compiler assumes the reads/writes have no effect on observable behavior
- Compiler optimizes away memory operations
- Hardware never gets read or written
- **Result: System fails**

With `volatile`:
- Compiler preserves all memory operations
- Each read and write happens exactly as written
- Hardware interaction works correctly
- **Result: System works**

## Key Takeaways
- **Dead Code Elimination**: Compilers remove operations on variables whose results are never used
- **Optimization Levels**: `-O1` and above aggressively eliminate dead code; `-O0` preserves all operations
- **volatile Necessity**: Embedded systems need `volatile` for hardware memory-mapped I/O to prevent unwanted optimization
- **Code Size vs. Debuggability**: `-O0` produces larger code but preserves all source logic; `-O1+` shrinks code but complicates debugging
- **RISC-V Stack Alignment**: Even unused local variables consume aligned stack space at `-O0`
- **Performance Trade-off**: Optimization reduces instruction count from 18 to 2; critical for performance-sensitive embedded code

## Assembly Instruction Breakdown

### Key RISC-V Instructions Used
- `li a5, value`: Load immediate value into register
- `sw a5, offset(s0)`: Store word from register to memory
- `lw a5, offset(s0)`: Load word from memory to register
- `addi a5, a5, value`: Add immediate value
- `addi sp, sp, -32`: Adjust stack pointer (allocate)
- `addi sp, sp, 32`: Adjust stack pointer (deallocate)
- `mv a0, a5`: Move register to register (pseudo-instruction for `add`)
- `jr ra`: Jump to return address

## Exercises (Optional)
1. Add the `volatile` keyword to variable `a` and recompile with `-O1`. Observe how the assembly changes.
2. Compare `main.s` (optimized) with `main_O0.s` (unoptimized). Count the difference in instruction count.
3. Modify the function to return the value of `a`. Does the compiler still optimize it away with `-O1`?
4. Create a version that modifies a pointer to a hardware register; observe how `volatile` prevents optimization.
5. Experiment with `-O2` and `-O3` optimization levels and compare assembly output.

## Resources
- [RISC-V ISA Specification](https://riscv.org/specifications/)
- [RISC-V Calling Convention (ABI)](https://github.com/riscv-non-profit/riscv-elf-psabi-doc)
- [GCC Optimization Levels Documentation](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [C volatile Qualifier - cppreference](https://en.cppreference.com/w/c/language/volatile)
- [Embedded Systems and Memory-Mapped I/O](https://en.wikibooks.org/wiki/Embedded_Systems/Memory_Mapped_I-O)
