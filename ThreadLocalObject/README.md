# Process, Thread, and Thread-Local Storage in Linux OS & `thread_local` Object in C++

## Executable File
The compiler compiles source files into object files, which the linker combines to create an executable file. In Linux, an executable file typically follows the **ELF (Executable and Linkable Format)** standard.

This file is a **passive entity**; it is **not** a process.

## Process
A process is a group of resources such as:
- **Address space** (including machine code and data)
- **Program counter**
- **Registers**
- **Open files**
- **Memory limits**
- Other resources stored in the **Process Control Block (PCB)**

In Linux, a process is created using the `fork()` library procedure, which internally calls the `clone()` system call to create a new process.

## Thread
A **process** has a **thread of execution**, consisting of:
- **Registers**
- **Program Counter (PC)**
- **Stack**

In a **multithreaded** process, each thread has its **own** registers, PC, and stack but shares:
- **Code**
- **Data**
- **Open files**

### Linux Thread Model
Linux follows a **one-to-one** multithreading model, meaning each user-space thread created via the **Pthread** library corresponds to a **kernel-level thread**.

Threads can store data **locally** using **Thread-Local Storage (TLS)**, meaning each thread maintains its **own** copy of certain data throughout its execution lifetime.

A thread is created via the `clone()` system call, using specific flags that determine how much resource sharing occurs between parent and child threads.

Linux does not make a strict distinction between **threads** and **processes**. Instead, both are treated as **tasks**, represented by a unique kernel structure: **`task_struct`**.

## `thread_local` Object in C++
A **`thread_local`** variable is unique to each thread and cannot be accessed by other threads. Even if it is declared outside the thread function, each thread stores its copy in a **different memory location**.

- The lifetime of a `thread_local` variable starts with the creation of the thread and ends when the thread terminates.
- A `thread_local` variable **is not initialized by default** unless explicitly assigned a value. If it is of a fundamental type (`int`, `char`, etc.), its value is **indeterminate** until set.

## Example Code
The C++ program demonstrates how **each thread has its own copy of a `thread_local` variable**, stored at a different memory address.