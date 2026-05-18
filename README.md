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
