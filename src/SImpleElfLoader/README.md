# ELF Loader and Executor

This project is a simple ELF (Executable and Linkable Format) loader and executor implemented in C++. It reads an ELF binary file, loads the necessary segments into memory, and then executes the binary.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
  - [Global Variables](#global-variables)
  - [System Calls](#system-calls)
  - [Main Loading and Execution Logic](#main-loading-and-execution-logic)
  - [Cleanup](#cleanup)
  - [Main Function](#main-function)
- [Contributions](#contributions)
- [License](#license)

## Introduction

This project provides a basic example of how to load and execute an ELF binary file. The ELF loader reads the ELF headers, locates the program headers, loads the segments into memory, and then transfers control to the entry point of the ELF binary.

## Features

- Reads ELF headers and program headers
- Loads the segments into memory using `mmap`
- Executes the loaded ELF binary
- Cleans up resources after execution

## Requirements

- Linux-based operating system
- C++ compiler
- Make utility

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/elf-loader.git
   cd elf-loader
   ```

2. Build the project using `make`:
   ```bash
   make
   ```

3. Run the ELF loader with an ELF binary file:
   ```bash
   ./elf_loader path/to/elf/binary
   ```

## Implementation Details

### Global Variables

- `Elf32_Ehdr *ehdr`: Pointer to the ELF header.
- `Elf32_Phdr *phdr`: Pointer to the program header.
- `int fd`: File descriptor for the ELF binary.
- `size_t sizeStored`: Size of the loaded segment.
- `char *virtual_mem`: Memory where the ELF segment is loaded.

### System Calls

- `munmap()`: Unmap memory.
- `close()`: Close a file descriptor.
- `open()`: Open a file.
- `exit()`: Terminate the program.
- `malloc()`: Allocate memory.
- `lseek()`: Reposition file offset.
- `read()`: Read from a file descriptor.
- `mmap()`: Map files or devices into memory.

### Main Loading and Execution Logic

The `load_and_run_elf()` function orchestrates the entire process of loading and executing the ELF binary. It reads the ELF header, locates the PT_LOAD segment, loads it into memory, and then jumps to the entry point to execute the binary.

### Cleanup

The `loader_cleanup()` function releases memory and performs cleanup operations after the execution is complete.

### Main Function

The `main()` function validates the command-line argument, then calls `load_and_run_elf()` to load and execute the provided ELF binary. It also invokes the cleanup routine.

## Contributions

1. **Angadjeet Singh (2022071)**: Contribution – 50%
   - Focused on the code implementation.
   - Defined the logic framework and required system calls and variables.

2. **Apaar IIITD (2022089)**: Contribution – 50%
   - Structured the basic code and worked intensively on error analysis.
   - Created Makefiles for the assignment and documented the project.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
```

This `README.md` provides a structured and comprehensive overview of your ELF loader project, including instructions for usage, details on the implementation, and credits for contributions.
