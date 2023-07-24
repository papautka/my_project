#include "s21_matrix.h"

// Очистка памяти
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++)  // цикл по строкам
      free(A->matrix[i]);  // освобождение памяти под строку
    free(A->matrix);
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code_errors = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    // Выделение памяти под указатели на строки
    result->matrix = (double **)malloc(rows * sizeof(double *));
    // Ввод элементов массива
    for (int i = 0; i < rows; i++) {
      // Выделение памяти под хранение строк
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      // цикл по столбцам
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  } else {
    result = NULL;
    code_errors = 1;
  }
  return code_errors;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code_errors = s21_check_err(A, B);
  if (code_errors == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
      }
    }
  }
  return code_errors;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code_errors = s21_check_err(A, B);
  if (code_errors == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
      }
    }
  }
  return code_errors;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1;
  if (A == NULL || B == NULL) {
    flag = 0;
  } else if (A->matrix == NULL || B->matrix == NULL) {
    flag = 0;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = 0;
  } else {
    for (int i = 0; i < A->rows && flag == 1; ++i) {
      for (int j = 0; j < B->columns && flag == 1; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code_errors = 0;
  if ((A->rows <= 0 || A->columns <= 0 || !(A || A->matrix))) {
    code_errors = 1;
  }
  if (code_errors == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->rows == 1 && A->columns == 1) {
          result->matrix[i][j] = number;
        } else {
          result->matrix[i][j] = number * (A->matrix[i][j]);
        }
      }
    }
  }
  return code_errors;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code_errors = 0;
  if (!(A->columns == B->rows)) {
    code_errors = 2;
  }
  if (code_errors == 0 && ((A->rows <= 0 || A->columns <= 0) ||
                           (B->rows <= 0 || B->columns <= 0))) {
    code_errors = 1;
  }
  if (code_errors == 0) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return code_errors;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code_errors = 0;
  if (A->rows <= 0 || A->columns <= 0 || !(A || A->matrix)) {
    code_errors = 1;
  }
  if (code_errors == 0 && result) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return code_errors;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code_errors = s21_check_matrix(A);
  if (code_errors == 0 && result) {
    matrix_t tmp = {0};
    double res = 0;
    s21_determinant(A, &res);
    if (res != 0) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
          s21_Minion_minor_forij(i, j, A, &tmp);
          s21_determinant(&tmp, &res);
          result->matrix[i][j] = res * pow(-1, i + j);
          s21_remove_matrix(&tmp);
        }
      }
    } else {
      code_errors = 1;
    }
  }
  return code_errors;
}

int s21_determinant(matrix_t *A, double *result) {
  int code_errors = 0;
  if (result && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      matrix_t Buffer = {0};
      s21_buffer_matrix(A, &Buffer);
      *result = s21_determinant_help(Buffer);
      s21_remove_matrix(&Buffer);
    } else {
      code_errors = 2;
    }
  } else {
    code_errors = 1;
  }
  return code_errors;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code_err = s21_check_matrix_inv(A);
  if (code_err == 0 && result) {
    double x = 0;
    s21_determinant(A, &x);
    if (x != 0) {
      matrix_t Buffer = {0};
      if (A->rows > 1) {
        s21_calc_complements(A, result);
        s21_transpose(result, &Buffer);
        s21_remove_matrix(result);
        s21_mult_number(&Buffer, (1. / x), result);
        s21_remove_matrix(&Buffer);
      } else if (A->rows == 1) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1. / A->matrix[0][0];
      }
    } else {
      code_err = 2;
    }
  }
  return code_err;
}
