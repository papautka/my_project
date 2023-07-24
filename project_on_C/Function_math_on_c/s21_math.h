#ifndef _S21_MATH_
#define _S21_MATH_

#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

// #ifdef __APPLE__
// #define _POSIX_C_SOURCE 200809L
// #endif

// #ifndef s21_isnan
// #define s21_isnan(a) (a != a)
// #endif

#define S21_EXPON 2.71828182845904523536028747
#define S21_PI 3.141592653589793238462643383279502884197169399375105820974944
#define S21_PI_HALF 1.57079632679489661923
#define S21_PI_4 0.785398163397448309616
#define S21_EPS 1e-12
#define S21_NAN 0.0 / 0.0
#define S21_INF __builtin_huge_vall()
#define S21_OTR_INF -__builtin_huge_vall()
#define S21_LN10 2.30258509299404590109
#define S21_MAX_DOUBLE 1.7976931348623158e308
#define MIN_DEGREE -713
#define MAX_DEGREE 709.782712
#define LN10 2.30258509299404568401799145468436421

int s21_abs(int x);  // вычисляет абсолютное значение целого числа
long double s21_acos(double x);  // вычисляет арккосинус
long double s21_asin(double x);  // вычисляет арксинус
long double s21_atan(double x);  // вычисляет арктангенс
long double s21_ceil(double x);  // возвращает ближайшее целое число, не меньшее
                                 // заданного значения
long double s21_cos(double x);   // вычисляет косинус
long double s21_exp(
    double x);  // возвращает значение e, возведенное в заданную степень
long double s21_fabs(double x);  // вычисляет абсолютное значение числа с
                                 // плавающей точкой
long double s21_floor(double x);  // возвращает ближайшее целое число, не
                                  // превышающее заданное значение
long double s21_fmod(double x,
                     double y);  // остаток операции деления с плавающей точкой
long double s21_log(double x);  // вычисляет натуральный логарифм
long double s21_pow(double base,
                    double exp);  // возводит число в заданную степень
long double s21_sin(double x);  // вычисляет синус
long double s21_sqrt(double x);  // вычисляет квадратный корень
long double s21_tan(double x);  // вычисляет тангенс

long double s21_find(double a, double x);
double is_nan(double x);
long double s21_factorial(double a);
void s21_round_to_PI(double *a);
int is_S21_INF(double x);
#endif  // _S21_MATH_
