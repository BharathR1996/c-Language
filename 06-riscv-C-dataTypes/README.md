# Lesson 6: RISC-V C Data Types & Stack Memory Layout

## Overview
This lesson demonstrates how different C data types are allocated and stored in stack memory when compiled to RISC-V assembly. You'll learn how the compiler manages local variables, allocates stack frames, and how different data types consume memory resources.

## Prerequisites
- Lesson 5: RISC-V C and Assembly recommended
- Understanding of function prologue/epilogue
- Basic knowledge of stack frames and calling conventions

## Concepts Covered
- C data types in RISC-V: `int`, `char`, `float`, `double`, `short`, `long`
- Stack frame allocation and deallocation
- Local variable storage on the stack
- Frame pointer and stack pointer management
- RISC-V calling conventions (ABI)
- Memory alignment in stack frames

## Program Details

The C program defines a function `bharath()` with multiple local variables of different data types:

```c
int bharath()
{
    int integer = 10;                          // 4 bytes
    char character = 'A';                      // 1 byte
    float floating_point = 3.14;               // 4 bytes
    double double_precision = 3.141592653589793; // 8 bytes
    short short_integer = 5;                   // 2 bytes
    long long_integer = 1000000;               // 4 bytes (RV32I)
    return 0;
}
```

**Total local variables: 23 bytes** (but 32 bytes allocated due to alignment)

## Build & Run

### Compile and Generate Assembly
```bash
cd 06-riscv-C-dataTypes
make assembler_without_gdb
```

### View Assembly Output
```bash
cat main.s
```

### Expected Output
```
Assembly file generated showing function prologue, variable initialization, and epilogue
```

## Files

| File | Purpose |
|------|---------|
| `C-asm.c` | C source code with function containing multiple data type variables |
| `main.s` | Generated RISC-V assembly code |
| `main.ld` | Linker script for RISC-V compilation |
| `Makefile` | Build automation script |

## Stack Memory Layout

### Function Prologue (Lines 11-13)
```
addi sp,sp,-32        # Allocate 32 bytes on stack
sw s0,28(sp)          # Save old frame pointer
addi s0,sp,32         # Set new frame pointer
```

### Stack Frame Layout (32 bytes allocated)
```
┌────────────────────────────┐ sp + 32 = s0 (Frame Pointer)
│        (empty)             │
│        (empty)             │
│        (empty)             │
├────────────────────────────┤ sp + 28
│      [old s0]              │ ← Saved frame pointer
├────────────────────────────┤ sp + 24
│  long_integer (4 bytes)    │ ← s0 - 8 = sp + 24
├────────────────────────────┤ sp + 20
│  short_integer (2 bytes)   │ ← s0 - 12 = sp + 20
│  + padding (2 bytes)       │
├────────────────────────────┤ sp + 16
│ double_precision (8 bytes) │ ← s0 - 16 = sp + 16
├────────────────────────────┤ sp + 8
│ floating_point (4 bytes)   │ ← s0 - 24 = sp + 8
│ + padding (4 bytes)        │
├────────────────────────────┤ sp + 4
│    character (1 byte)      │ ← s0 - 28 = sp + 4
│    + padding (3 bytes)     │
├────────────────────────────┤ sp + 0
│    integer (4 bytes)       │ ← s0 - 32 = sp + 0
└────────────────────────────┘ sp (Stack Pointer)
```

### Local Variables Storage Offsets
| Variable | Type | Size | Offset from s0 |
|----------|------|------|-----------------|
| integer | int | 4 bytes | -32 (sp + 0) |
| character | char | 1 byte | -28 (sp + 4) |
| floating_point | float | 4 bytes | -24 (sp + 8) |
| double_precision | double | 8 bytes | -16 (sp + 16) |
| short_integer | short | 2 bytes | -12 (sp + 20) |
| long_integer | long | 4 bytes | -8 (sp + 24) |

### Function Epilogue (Lines 18-19)
```
lw s0,28(sp)          # Restore old frame pointer
addi sp,sp,32         # Deallocate 32 bytes
jr ra                 # Return to caller
```

## Why Stack Allocation is 32 Bytes?

### RISC-V ABI Stack Alignment Requirement
The RISC-V Application Binary Interface (ABI) **requires the stack pointer (`sp`) to remain 16-byte aligned** at all times. This means `sp` must always be divisible by 16.

### The Calculation

```
23 bytes needed for all variables:
  - int: 4 bytes
  - char: 1 byte
  - float: 4 bytes
  - double: 8 bytes
  - short: 2 bytes
  - long: 4 bytes
  ────────────────
  Total: 23 bytes

Rounded up to nearest multiple of 16: 32 bytes
Padding added: 32 - 23 = 9 bytes
```

### Alignment Verification

```
Stack Alignment Check:

Before prologue:
  sp = 0x1000 (16-byte aligned) ✓

After prologue (if allocated 24 bytes):
  sp = 0x1000 - 24 = 0xFE8
  0xFE8 mod 16 = 8 (NOT aligned) ✗

After prologue (if allocated 32 bytes):
  sp = 0x1000 - 32 = 0xFE0
  0xFE0 mod 16 = 0 (16-byte aligned) ✓
```

### Why Alignment Matters

1. **SIMD Instructions**: Aligned memory enables efficient SIMD operations (128-bit registers)
2. **Consistency**: Guarantees predictable memory layout across function calls
3. **Compatibility**: Ensures interoperability with system libraries and ABI compliance
4. **Performance**: Some CPUs have penalties for unaligned memory access
5. **Safety**: Prevents undefined behavior in certain operations

### Conclusion
The compiler adds **9 bytes of padding** to maintain the critical **16-byte alignment requirement**, even though the actual variables only need 23 bytes. This is a trade-off between memory efficiency and performance/compatibility.

## Key Takeaways
- **Stack Allocation**: 32 bytes are allocated (multiples of 16 for alignment)
- **Frame Pointer (s0)**: Points to the base of the current stack frame for easy variable access
- **Negative Offsets**: Local variables are accessed using negative offsets from s0
- **Data Type Sizes**: Different data types consume different amounts of memory
- **Alignment**: Memory is aligned to 4-byte boundaries for efficient access
- **Calling Convention**: RISC-V ABI defines how registers and stack are used for function calls
- **Prologue/Epilogue**: Essential for maintaining proper stack state and register restoration

## Exercises (Optional)
1. Modify the C program to add more local variables and observe how the stack frame grows
2. Try different data type combinations and predict the stack layout
3. Analyze the assembly to find where each variable is stored
4. Create a function that takes parameters and observe how arguments are passed in registers

## Resources
- [RISC-V ISA Specification](https://riscv.org/specifications/)
- [RISC-V Calling Convention (ABI)](https://github.com/riscv-non-profit/riscv-elf-psabi-doc)
- [GCC RISC-V Documentation](https://gcc.gnu.org/wiki/RISC-V)
