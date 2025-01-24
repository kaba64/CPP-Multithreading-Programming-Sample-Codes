Example

# Concurrent Programming in C++ (`std::thread`)

This repository demonstrates the use of `std::thread` in C++ for concurrent programming. It includes examples of multithreaded computation, a custom thread management class, and code for calculating the sum of an array using multiple threads.

---

## Table of Contents

- [Introduction](#introduction)
- [Key Concepts](#key-concepts)
- [Code Overview](#code-overview)
- [References](#references)

---

## Introduction

A **task** is a computation that can potentially run concurrently with other tasks. In C++, tasks are represented as **threads**, which are lightweight abstractions over system-level hardware threads.

This project demonstrates:
- The use of `std::thread` (introduced in C++11)
- A custom thread management class to avoid common pitfalls, such as failing to join threads.

---

## Key Concepts

### Task and Thread

- **Task:** A unit of computation that can run concurrently.
- **Thread:** The system-level representation of a task. Threads in a process share the same address space, but each has its own program counter, stack, and register files.

### `std::thread`

- Represents system-level resources such as stack space and registers.
- APIs are implemented on top of platform-specific libraries (e.g., Pthread or Windows Threads).
- Functions:
  - **Constructor:** Accepts a function to execute on a new thread.
  - **Destructor:** Calls `std::terminate` if the thread is joinable and goes out of scope.
  - **`join()`:** Waits for the thread to finish execution.
  - **`detach()`:** Runs the thread in the background (use with caution).

### `std::jthread`

Introduced in C++20, `std::jthread` is a safer alternative to `std::thread` because it automatically joins threads in its destructor, preventing accidental `std::terminate`.

### Custom Thread Management (`threadGuard`)

For versions of C++ prior to C++20, failing to join a thread before it goes out of scope can cause program termination. To avoid this, we define a custom `threadGuard` class that automatically joins threads in its destructor.

---

## Code Overview

### Example: Multithreaded Sum of an Array

The example computes the sum of an array using multiple threads. It uses:
1. A function (`partialSum`) to compute partial sums.
2. A custom thread management class (`threadGuard`).
3. A main program to launch threads and accumulate the final result.


## References

1. C++ Concurrency in Action, Second Edition

2. The C++ Programming Language, Fourth Edition