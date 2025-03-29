# Memory Management in OpenMP

## Overview
In an OpenMP program, the scope of variables can be modified using OpenMP clauses. This document provides an overview of key clauses that manage memory and variable visibility across threads.

## OpenMP Variable Scope Clauses

### Shared (variable_list) Clause
By default, all variables declared outside OpenMP parallel regions are shared within those regions. This means that within parallel regions, any references to those variables resolve to the corresponding variables outside the parallel block (specifically, on the master thread).

If the `default(none)` clause is used in an OpenMP directive, no variables are shared unless explicitly declared using `shared(variable_list)`.

### Private (variable_list) Clause
This clause, placed after the parallel directive, creates separate instances of the specified variables for each thread. These instances are allocated in each thread's stack, and their scope is limited to the parallel block.

**Note:** Private variables are not initialized when encountered in the parallel region.

### Firstprivate (variable_list) Clause
This clause functions like the `private` clause but initializes the variables with the values from the master thread before entering the parallel region.

### Threadprivate (variable_list) Clause
This clause applies to global variables and ensures that each thread has its own persistent storage for the specified variables. It is used in the following format:

```cpp
#pragma omp threadprivate(variable_list)
```

In C and C++, variables in the list should have **file scope** (global variables), **namespace scope**, or be declared as **static block scope** (like static variables inside a class).

**Initialization:**
There is no strict guarantee of when these variables will be initialized, except that each thread initializes them before referencing them.

### Copyin (variable_list) Clause
This clause is used alongside `threadprivate` to initialize thread-private variables with the master thread's private variable values.


## Reference
[1] OpenMP Application Programming Interface Version 5.0
