
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES  // for C

#include "../s21_math.h"

//
int main() {
  //   x = S21_INF, y = S21_INF;
  // ck_assert_ldouble_nan(s21_fmod(x, y));
  printf("%lf\n", 100 * fmod(S21_INF, S21_INF));

  printf("%Lf\n", 100 * s21_fmod(S21_INF, S21_INF));

  return 0;
}