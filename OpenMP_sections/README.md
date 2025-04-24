# Sections Clause and Throwing an Exception:

The 'parallel for' directive in OpenMP can be used for the parallelization of the data parallel section of the code, and the 'parallel section' directive can be used to run multiple independent tasks simultaneously, which is known as task parallelism.

The syntax of the sections construct is as follows:

```c
#pragma omp sections [clauses]
{
#pragma omp section
{
block 1
}
#pragma omp section
{
block2
}
...
}

```

Different clauses, e.g. shared, can be used after the 'sections' directive, but they are not allowed after the 'section' directive.

The blocks in each 'section' directive are executed just by one of the threads in the thread team created by the 'parallel' directive. The number of threads in the team can be more or less than the number of the 'section' directives.

The assignment of the blocks to the threads in the team is implementation-specific.

If an exception is thrown within a section, the exception should be captured inside the same section; otherwise, the behaviour is undefined. For instance, the program might terminate if the exception is caught outside the 'section' directive, such as in the main thread.

The attached sample code demonstrates the usage of the 'sections' directive.
