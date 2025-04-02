# OpenMP Needs a For Loop to Be in the Canonical Form

## Overview
Loops are the best candidates for using OpenMP to parallelize code with minimal effort from the software developer. However, there are restrictions on the loop variable, termination condition, increment expression, and flow control statements for loops in the following form:

```cpp
for(loop_control_variable ; termination_condition ; incrementing_expression) {
    statements
}
```

## Loop Control Variable
- Must be an integer type, a pointer (in C), or a random access iterator (in C++).
- Cannot be modified inside the loop body.

## Termination Condition
- Must follow the logic:
  ```cpp
  var OP bound
  ```
- The `bound` variable must remain constant during loop execution.
- The relational operation (`OP`) can be one of `<, <=, >, >=`.

## Incrementing Expression
- Must follow the form:
  ```cpp
  var OP incr
  ```
- The `incr` must be a constant.
- The `OP` can be `+=, -=`.
- The increment expression can also take the forms `var++, ++var, var--, --var`.

## Control Statements Inside the Loop Body
- The loop body **cannot** contain `break`, `goto`, or `throw` statements.
- If these restrictions pose challenges, highly performant STL algorithms can be used with execution policies.

## Range-Based For Loop in C++
- A range-based loop with a random access iterator can be parallelized using an OpenMP directive.

## Reference
[1] OpenMP Application Programming Interface Version 5.0
