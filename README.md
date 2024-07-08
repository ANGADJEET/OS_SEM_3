# System-Level C Application: Overview and Components

This document provides an overview of a comprehensive system-level C application developed by Angadjeet Singh(2022071) & Apaar IIITD(2022089). The application integrates multiple components, each addressing different aspects of system programming and software development.

## Overview

The system-level C application encompasses five major components, each contributing to the overall functionality and demonstrating various system programming concepts:

1. **Simple Multithreading Example**
2. **Simple ELF Loader**
3. **Smart ELF Loader**
4. **Shell Program Explanation**
5. **ELF Loader Program**

Each component serves a specific purpose, from demonstrating multithreading and parallelism to loading and executing ELF files, implementing a shell interface, and handling system-level signals and memory management.

## 1. Simple Multithreading Example

### Introduction

The Simple Multithreading Example showcases basic implementation of parallelized loops using pthreads in C++. It includes examples of parallel_for with both single and nested double loops, demonstrating the use of lambda functions for task definition.

### Usage

To compile and run the Simple Multithreading Example:

1. **Navigate to the Directory:**
   ```bash
   cd path/to/simple_multithreading_example
   ```

2. **Compile the Code:**
   ```bash
   make
   ```

3. **Run the Executable:**
   ```bash
   ./filename (NUM_THREADS) (SIZE)
   ```
   Replace `(NUM_THREADS)` and `(SIZE)` with your desired values.

### Functions

- `demonstration`: Executes a lambda function.
- `parallel_for` (Single Loop): Executes a lambda function across a range using pthreads.
- `parallel_for` (Double Loop): Executes a nested double loop using pthreads.

For detailed function descriptions and examples, refer to the provided README in the respective project directory.

## 2. Simple ELF Loader

### Introduction

The Simple ELF Loader is a C program that loads and executes ELF (Executable and Linkable Format) files. It handles basic functionalities such as loading ELF files, allocating memory for program segments, and executing the `_start` function.

### Usage

To run the Simple ELF Loader:

1. **Navigate to the Directory:**
   ```bash
   cd path/to/simple_elf_loader
   ```

2. **Compile the Code:**
   ```bash
   make
   ```

3. **Run the Executable:**
   ```bash
   ./simple_elf_loader [ELF_FILE]
   ```
   Replace `[ELF_FILE]` with the path to your ELF executable file.

### Functions

- `load_and_run_elf`: Main function to load and execute ELF files.
- `custom_handler`: Signal handler for segmentation faults.
- `check_heapoverflow_ehdr`, `check_heapoverflow_phdr`: Functions to check heap overflow.
- `allocate_memory_ehdr`, `allocate_memory_phdr`: Functions to allocate memory for ELF headers and program headers.

For more details, refer to the README provided in the `simple_elf_loader` directory.

## 3. Smart ELF Loader

### Introduction

The Smart ELF Loader extends the functionality of the Simple ELF Loader by introducing advanced features such as dynamic memory management, segmentation fault handling, and detailed program execution statistics.

### Usage

To run the Smart ELF Loader:

1. **Navigate to the Directory:**
   ```bash
   cd path/to/smart_elf_loader
   ```

2. **Compile the Code:**
   ```bash
   make
   ```

3. **Run the Executable:**
   ```bash
   ./smart_elf_loader [ELF_FILE]
   ```
   Replace `[ELF_FILE]` with the path to your ELF executable file.

### Functions

- `load_and_run_elf`: Enhanced function with dynamic memory allocation and detailed execution statistics.
- `custom_handler`: Advanced signal handler for segmentation faults.
- `calculate_fragmentation`: Calculates memory fragmentation based on program execution.
- `print_details`: Prints detailed execution information including page faults and memory usage.

For detailed function descriptions and examples, refer to the README provided in the `smart_elf_loader` directory.

## 4. Shell Program Explanation

### Overview

The Shell Program provides a command-line interface for users to interact with the system. It supports executing single commands, handling pipes for command chaining, maintaining command history, and executing scripts.

### Usage

To run the Shell Program:

1. **Navigate to the Directory:**
   ```bash
   cd path/to/shell_program
   ```

2. **Compile the Code:**
   ```bash
   make
   ```

3. **Run the Shell:**
   ```bash
   ./shell_program
   ```
   The shell will start, displaying a command prompt where users can enter commands.

### Features

- Command execution with and without pipes.
- Command history tracking and printing.
- Script execution from a file.
- Signal handling for Ctrl+C (SIGINT) to print command history.
- User-friendly command-line interface.

For detailed usage instructions and examples, refer to the README provided in the `shell_program` directory.

## 5. ELF Loader Program

### Overview

The ELF Loader Program loads and executes ELF (Executable and Linkable Format) files. It includes a custom handler for segmentation faults, dynamically allocates memory for program segments, and provides detailed information about memory usage and page faults.

### Usage

To run the ELF Loader Program:

1. **Navigate to the Directory:**
   ```bash
   cd path/to/elf_loader_program
   ```

2. **Compile the Code:**
   ```bash
   make
   ```

3. **Run the Executable:**
   ```bash
   ./elf_loader_program [ELF_FILE]
   ```
   Replace `[ELF_FILE]` with the path to your ELF executable file.

### Functions

- `load_and_run_elf`: Main function to load and execute ELF files.
- `custom_handler`: Signal handler for segmentation faults.
- `check_heapoverflow_ehdr`, `check_heapoverflow_phdr`: Functions to check heap overflow.
- `allocate_memory_ehdr`, `allocate_memory_phdr`: Functions to allocate memory for ELF headers and program headers.

For more details, refer to the README provided in the `elf_loader_program` directory.

## Contribution

- **Angadjeet Singh(2022071):** Worked on the implementation of structures, core logic, and system calls for all components.
- **Apaar IIITD(2022089):** Focused on logic implementation, error handling, and integration of components.
