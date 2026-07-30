# C Language & Assembly Learning Repository

A comprehensive learning resource for C programming and RISC-V assembly language.

## 📚 Lessons

### [Lesson 1: C Basics](./01-c-basics/)
- Hello World program
- Basic C syntax introduction

### [Lesson 2: RISC-V Assembly - Infinite Loop](./02-riscv-assembly-loop/)
- Introduction to RISC-V assembly
- Infinite loop example
- QEMU emulation & GDB debugging

### [Lesson 3: RISC-V Assembly - Multiplication](./03-riscv-assembly-multiplication/)
- RISC-V multiplication using loops
- Repeated addition algorithm (2 × 5 = 10)
- Advanced debugging techniques

### [Lesson 4: RISC-V C to Assembly](./04-riscv-C-to-Assembly/)
- Compile C functions to RISC-V assembly
- Assembly directives and debug info (DWARF)
- Clean vs. debug assembly output

### [Lesson 5: RISC-V C and Assembly Integration](./05-riscv-C-and-assembly/)
- Integrating assembly and C code in a single project
- Assembly entry point calling C functions
- Linker scripts and compilation order
- QEMU emulation with GDB debugging

### [Lesson 6: RISC-V C Data Types & Stack Memory Layout](./06-riscv-C-dataTypes/)
- C data types allocation in RISC-V: `int`, `char`, `float`, `double`, `short`, `long`
- Stack frame allocation and memory alignment
- Frame pointer and stack pointer management
- RISC-V calling conventions (ABI)
- Local variable storage on the stack

### [Lesson 7: RISC-V `const` and Pointer Behavior](./07-riscv-C-const/)
- C `const` qualifier semantics and compiler handling
- Pointer assignment to `const` objects
- Compiler warnings for discarded qualifiers
- RISC-V C to assembly compilation
- Const value storage and pointer arithmetic in assembly

### [Lesson 8: RISC-V `volatile` Qualifier and Compiler Optimization](./08-riscv-C-volatile/)
- C `volatile` qualifier effects on compiler behavior
- Dead code elimination and optimization levels (-O0, -O1, -O2, -O3)
- Memory operations and compiler optimization
- Hardware register access patterns
- Embedded systems memory-mapped I/O considerations

### [Lesson 9: If-Else Conditions in C and RISC-V Assembly](./09-riscv-C-if-else-condition/)
- If/else-if/else control flow in C
- Conditional branching in RISC-V assembly
- Comparing values and jumping with branch instructions
- Calling a C function from assembly entry code
- Bare-metal execution flow with QEMU and GDB

## 🚀 Getting Started

Each lesson has its own directory with:
- Source code files
- Makefile for building
- README with detailed instructions

### Prerequisites

```bash
# For RISC-V assembly lessons, install:
sudo apt update -y
sudo apt install -y gcc-riscv64-unknown-elf qemu-system-misc gdb-multiarch

# For GDB Dashboard, install:
wget -P ~ https://github.com/cyrus-and/gdb-dashboard/raw/master/.gdbinit
pip install pygments
```

## 📖 How to Use

1. Navigate to the lesson directory
2. Read the lesson's README.md
3. Follow the build instructions
4. Experiment with the code

---

**Note**: This repository consolidates lessons from a single `main` branch with organized directories. This is the standard practice for educational repositories.
