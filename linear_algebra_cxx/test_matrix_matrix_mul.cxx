
#include "linear_algebra.hxx"

#include <stdio.h>
#include <assert.h>

static inline int
min(int i, int j)
{
  if (i < j) {
    return i;
  } else {
    return j;
  }
}

// ----------------------------------------------------------------------
// setup_test_matrices
//
// initializes the two matrices A, B, and the reference solution C_ref

static void
setup_test_matrices(struct matrix *A, struct matrix *B, struct matrix *C_ref)
{
  // the test matrices are diagonal, which isn't really good,
  // a more general test case would be better.

  // the matrices are initialized to zero, so we only set the non-zero elements
  // on the diagonal
  for (int i = 0; i < min(A->m, A->n); i++) {
    MAT(A, i, i) = i;
  }
  for (int i = 0; i < min(B->m, B->n); i++) {
    MAT(B, i, i) = i;
  }
  for (int i = 0; i < min(min(C_ref->m, C_ref->n), A->n); i++) {
    MAT(C_ref, i, i) = i * i;
  }
}

// ----------------------------------------------------------------------
// main
//
// test the mat_vec_mul() function

int
main(int argc, char **argv)
{
  const int m = 500, n = 500, k = 200;

  matrix *A = new matrix(m, k);
  matrix *B = new matrix(k, n);
  matrix *C = new matrix(m, n);
  matrix *C_ref = new matrix(m, n);

  // build a test matrix
  setup_test_matrices(A, B, C_ref);

  // calculate C = AB
  matrix_matrix_mul(A, B, C);

  /* printf("C = "); */
  /* matrix_print(C); */
  /* printf("\n"); */

  // the resulting vector for this test should equal our reference result
  // FIXME, matrix_is_equal() is missing
  //  assert(matrix_is_equal(C, C_ref));

  // clean up
  delete A;
  delete B;
  delete C;
  delete C_ref;

  return 0;
}

