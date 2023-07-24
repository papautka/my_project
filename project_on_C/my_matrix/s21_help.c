#include "s21_matrix.h"

void s21_Minion_minor_forij(int i, int j, matrix_t *A, matrix_t *B) {
  for (int k = 0, k1 = 0; k < A->rows; k++) {
    for (int q = 0, q1 = 0; q < A->columns; q++) {
      if (!(k == i || q == j)) {
        B->matrix[k1][q1] = A->matrix[k][q];
        q1++;
        if (q1 == A->rows - 1) {
          q1 = 0;
          k1++;
        }
      }
    }
  }
}

void s21_buffer_matrix(matrix_t *A, matrix_t *Buffer) {
  s21_create_matrix(A->rows, A->columns, Buffer);
  for (int i = 0; i < Buffer->rows; i++) {
    for (int j = 0; j < Buffer->columns; j++) {
      Buffer->matrix[i][j] = A->matrix[i][j];
    }
  }
}

double s21_determinant_help(matrix_t A) {
  double result = 0;
  if (A.rows == 1) {
    result = A.matrix[0][0];
  }
  if (A.rows == 2) {
    result = A.matrix[0][0] * A.matrix[1][1] - A.matrix[1][0] * A.matrix[0][1];
  }
  if (A.rows > 2) {
    int i = 0;
    for (int j = 0; j < A.rows; ++j) {
      matrix_t tmp;
      s21_create_matrix(A.rows - 1, A.columns - 1, &tmp);
      s21_Minion_minor_forij(i, j, &A, &tmp);
      double det = s21_determinant_help(tmp);
      result += pow(-1, i + j) * A.matrix[0][j] * det;
      s21_remove_matrix(&tmp);
    }
  }
  return result;
}

int s21_check_err(matrix_t *A, matrix_t *B) {
  int code_errors = 0;
  if (A == NULL || B == NULL) {
    code_errors = 1;
  }
  if (!(A->rows == B->rows && A->columns == B->columns) && code_errors == 0) {
    code_errors = 2;
  }
  if (((A->rows <= 0 || A->columns <= 0) ||
       (B->rows <= 0 || B->columns <= 0)) &&
      code_errors == 0) {
    code_errors = 1;
  }
  return code_errors;
}

int s21_check_matrix(matrix_t *A) {
  int code_err = 0;
  if (A == NULL) {
    code_err = 1;
  }
  if (A->matrix == NULL && code_err == 0) {
    code_err = 1;
  }
  if (code_err == 0) {
    if (A->rows <= 0 || A->columns <= 0) {
      code_err = 1;
    }
    if (code_err == 0 && (A->rows != A->columns)) {
      code_err = 2;
    }
  }
  return code_err;
}

int s21_check_matrix_inv(matrix_t *A) {
  int code_err = 1;
  if (A != NULL) {
    if (A->matrix != NULL) {
      if (A->columns > 0 && A->rows > 0) {
        if (A->rows == A->columns) {
          code_err = 0;
        } else {
          code_err = 2;
        }
      }
    }
  }
  return code_err;
}

void matrix_null(matrix_t *A, matrix_t *result) {
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
