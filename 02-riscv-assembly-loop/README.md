# Lesson 2: RISC-V Assembly - Infinite Loop

Introduction to RISC-V assembly with an infinite loop example.

## Quick Commands

| Command | Description |
|---------|-------------|
| `make compile` | Build assembly to ELF and binary |
| `make printbinary` | Show binary in hex format |
| `make startqemu` | Run QEMU emulator |
| `make startgdb` | Connect GDB debugger |
| `make clean` | Remove build files |

## File Overview

- **main.s**: RISC-V assembly source code
- **main.ld**: Linker script (RAM at 0x80000000, 4KB)
- **Makefile**: Build automation

## GDB Setup

```bash
wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit
pip install pygments
```

## Workflow

```bash
make compile       # Build
make printbinary   # View binary
make startqemu     # Terminal 1
make startgdb      # Terminal 2
```
