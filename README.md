# LowLevel AI Library (C)

A lightweight, optimized Machine Learning library written in pure C from scratch.

## Features
- **Matrix Operations:** Multiplication, creation, and memory management.
- **Performance:** Optimized loops (comparable to NumPy speeds).
- **No Dependencies:** Runs on standard C libraries.

## Structure
- `src/`: The core logic (Matrix multiplication engine).
- `include/`: Header files and struct definitions.
- `examples/`: Test files and usage demos.

## How to Build
To compile the test:
```bash
gcc -I./include src/matrix.c examples/test_matrix.c -o ai_test
./ai_test
