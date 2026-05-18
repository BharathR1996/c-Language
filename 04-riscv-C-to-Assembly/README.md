# Lesson 04 — RISC-V: C to Assembly

## Overview
This lesson demonstrates compiling a simple C function to RISC-V assembly and explains the assembler output produced by `-S` and `-g` (DWARF) options.

## Build & Run

```bash
make assembler                # Generate assembly with debug info
make assembler_without_gdb    # Generate clean assembly (minimal directives)
make compile                  # Assemble/link to ELF
make startqemu                # Boot in QEMU (gdb port 1234)
make startgdb                 # Connect GDB to QEMU
make clean                    # Remove artifacts
```

## About C-asm.s — Assembly Directives

**Clean assembly** (without debug info):
```asm
.file "C-asm.c"
.option nopic
.attribute arch, "rv32i2p1"
.text                         # Code section
.globl bharath                # Global symbol
.type bharath, @function
bharath:                       # Function entry
  addi sp,sp,-16
  sw s0,12(sp)
  li a5,42
  mv a0,a5                     # Return value
  jr ra
```

**Key directives:**
- `.text`: Code section
- `.globl`, `.type`: Symbol declaration
- `.cfi_*`, `.loc`: Debug info (only with `-ggdb`)
- `.debug_*`: DWARF debug sections (only with `-ggdb`)

**With debug info** (`-ggdb`): Adds `.cfi_startproc`, `.cfi_offset`, `.loc`, and `.debug_*` sections for GDB debugging.

## Source Code & Function

**C source** (`C-asm.c`):
```c
int bharath()
{
    return 42;
}
```

**Assembly structure:**
- **Prologue**: `addi sp,sp,-16` (allocate stack) → `sw s0,12(sp)` (save register)
- **Body**: `li a5,42` (load 42) → `mv a0,a5` (return value in `a0`)
- **Epilogue**: Restore registers → `jr ra` (jump back)

**Note**: Even trivial functions get prologue/epilogue with `-O0`. Use `-O3` to optimize away unnecessary code.

## Files

| File | Purpose |
|------|---------|
| `C-asm.c` | C source (returns 42) |
| `C-asm.s` | Generated RISC-V assembly |
| `main.ld` | Linker script |
| `Makefile` | Build targets |

## Quick Notes

- `.text` = code section; `.data`/`.bss` = data sections
- `-ggdb` adds debug info (larger, enables GDB); omit for clean assembly
- `-O0` = no optimization; use `-O2`/`-O3` for production
- RISC-V calling convention: return values in `a0`, saved registers must be preserved
