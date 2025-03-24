# Internal Control Variables (ICV) in OpenMP

There are two ways to convert a sequential program to a parallel one on a shared memory multi-core system. The first one requires that a program developer uses thread libraries such as Pthread and C++ Thread Library to divide a task into smaller chunks and synchronize them. In the second approach, the creation and management of the threads are transferred from the application developer to the compiler and runtime libraries such as OpenMP and Intel Threading Building Blocks (TBB).

## OpenMP

OpenMP consists of compiler directives, library routines, and environmental variables. A programmer uses specific directives and pragmas to instruct the compiler to generate parallel code using the fork-join model. The runtime system then manages the threads and resources to execute the assigned workload.

OpenMP supports execution on both CPU and GPU.

## Internal Control Variables (ICV)

OpenMP spawns the same number of hardware threads available in the system when encountering a parallel pragma by default, but the number of active threads in the parallel region can be controlled by modifying the ICV of the OpenMP runtime using the following function:

```c
void omp_set_num_threads(int num_threads);
```

Parallel regions can be nested, meaning that each thread in a parallel region can spawn new threads. The number of active nested parallel regions, which is an ICV, can be set by the following function:

```c
void omp_set_max_active_levels(int max_levels);
```

If the number of nested parallel regions exceeds `max_levels`, the nested parallel region is executed by a single thread.