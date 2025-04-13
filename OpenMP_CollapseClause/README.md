# The Collapse Clause in OpenMP

The 'parallel for' directive in OpenMP parallelizes the closest loops below the directive, provided that the loops are in Canonical form. Multiple nested loops in Canonical form can be collapsed into a single loop and distributed among the threads, as long as they are perfectly nested with no intervening code between them. This can be achieved by the following clause: 

collapse(n)

Where n is the number of nested loops we want to collapse.

Using the collapse clause with n > 1 probably results in better performance when the outer loop has a few iterations to distribute between the threads.

However, caution should be taken when there is a chance that different threads write to the same memory location after collapsing the loops or parallelization of the nested loops. As an example of this issue, consider the matrix-matrix multiplication using the Rank-1 update:

/* There is a race condition and incorrect results will be produced */
#pragma omp parallel for collapse(2)
for (int p = 0; p < k; ++p){
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      C[i][j] += A[i][p] * B[p][j];
    }
  }
}