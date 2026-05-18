# Lesson 3: RISC-V Assembly - Multiplication Program

Bare-metal 32-bit RISC-V program that multiplies **2 × 5 = 10** using a loop with repeated addition.

---

## Code Overview

```asm
_start:
    addi x1, x0, 2      # x1 = 2 (multiplicand)
    addi x2, x0, 5      # x2 = 5 (loop counter)
    addi x3, x0, 0      # x3 = 0 (accumulator)

loop: 
    add x3, x3, x1      # x3 += x1
    addi x2, x2, -1     # x2 -= 1
    bne x2, x0, loop    # repeat if x2 != 0
j .                     # halt
```

**Result**: x3 = 10 after 5 iterations

---

## Build & Run

| Command | Purpose |
|---------|----------|
| `make compile` | Build: assembly → ELF → binary |
| `make startqemu` | Terminal 1: Start QEMU emulator (Exit: 0) |
| `make startgdb` | Terminal 2: Debug with GDB (Exit: 130 = Ctrl+C) |
| `make clean` | Remove build files |

---

## Files

| File | Purpose |
|------|----------|
| `main.s` | Assembly code |
| `main.ld` | Linker script (RAM: 0x80000000, 4KB) |
| `Makefile` | Build automation |

---

## Debug Workflow

```bash
# Terminal 1
make compile
make startqemu

# Terminal 2
make startgdb

# GDB commands
(gdb) step           # Single instruction
(gdb) info registers # View registers
(gdb) continue       # Run to next breakpoint
(gdb) quit           # Exit
```

---

## Compiler Flags

- `-O0` : No optimization
- `-ggdb` : Debug symbols
- `-nostdlib` : Bare-metal (no libc)
- `-march=rv32i` : 32-bit RISC-V ISA
- `-mabi=ilp32` : 32-bit ABI
