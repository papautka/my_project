#include "../s21_math.h"
int abs(int b);

int main(void) {
  double a;
  double x;
  int b;
  scanf("%lf", &a);
  scanf("%lf", &x);
  scanf("%d", &b);
  printf("\n");

  printf("%d\n", s21_abs(b));
  printf("%d\n\n", abs(b));

  printf("%Lf\n", s21_fabs(a));
  printf("%f\n\n", fabs(a));

  printf("%Lf\n", s21_ceil(a));
  printf("%f\n\n", ceil(a));

  printf("%Lf\n", s21_floor(a));
  printf("%f\n\n", floor(a));

  printf("%Lf\n", s21_fmod(a, x));
  printf("%f\n\n", fmod(a, x));

  return 0;
}
