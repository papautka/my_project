#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;     // Ряды - строки
  int columns;  // Столбцы
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

double s21_determinant_help(matrix_t A);
int s21_check_err(matrix_t *A, matrix_t *B);
int s21_check_matrix_inv(matrix_t *A);
int s21_check_matrix(matrix_t *A);
void s21_Minion_minor_forij(int i, int j, matrix_t *A, matrix_t *B);
void s21_buffer_matrix(matrix_t *A, matrix_t *Buffer);
double deter_2_2(matrix_t *A);
void matrix_null(matrix_t *A, matrix_t *result);
