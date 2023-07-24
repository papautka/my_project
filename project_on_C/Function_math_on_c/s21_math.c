#include "s21_math.h"

double is_S21_NAN(double x) { return x != x; }

int is_S21_INF(double x) {
  int flag = 0;
  if (x == S21_INF || x == -S21_INF || is_S21_NAN(x)) {
    flag = 1;
  }
  return flag;
}

long double s21_factorial(double a) {  // факториал
  double res = 1;
  for (int i = 1; i <= a; i++) {
    res *= i;
  }
  return res;
}

long double s21_pow(double a, double x) {
  long double res = 1;
  if ((res = s21_find(a, x)) == 2) {
    if (x == (int)x) {
      res = 1;
      int flag = 1;
      if (x < 0) {
        x = x * (-1);
        flag = 0;
      }
      for (int i = 0; i < x; i++) {
        res = res * a;
      }
      if (!flag) {
        res = 1 / res;
      }

    } else if (a > 0 && x != (int)x) {
      res = s21_exp((x * s21_log(a)));
    } else {
      res = S21_NAN;
    }
  }
  if (res > S21_MAX_DOUBLE) {
    res = S21_INF;
  }
  return res;
}

long double s21_exp(double x) {
  long double add_value = 1;
  long double res = 1;
  long double n = 1;
  int znak = 0;
  if (x < 0 && x != S21_OTR_INF) {
    x = x * (-1);
    znak = -1;
  }
  if (x == 1) {
    res = S21_EXPON;
  } else if (x == S21_OTR_INF) {
    res = 0;
  } else {
    while (add_value > S21_EPS) {
      add_value *= x / n;
      n += 1;
      res += add_value;
      if (res > S21_MAX_DOUBLE) {
        res = S21_INF;
        break;
      }
      if (znak == -1 && x >= 710) {
        res = 0;
        znak = znak * (-1);
        break;
      }
    }
  }
  return res != S21_INF ? znak == -1 ? 1 / res : res : S21_INF;
}

long double s21_log(double x) {
  int ex_pow = 0;
  long double func_N_1 = 0;
  long double func_N = 0;
  if (x == 1) {
    func_N_1 = 0;
  } else if (x > 0 && (x != 1 && x != S21_INF)) {
    for (; x >= s21_exp(x); x /= s21_exp(x), ex_pow++) continue;
    for (int n = 0; n < 100; n++) {
      func_N_1 = func_N;
      func_N =
          func_N_1 + 2 * ((x - s21_exp(func_N_1)) / (x + s21_exp(func_N_1)));
    }
  } else if (x < 0 || is_S21_NAN(x)) {
    func_N_1 = S21_NAN;
  } else if (x == +0 || x == -0) {
    func_N_1 = -S21_INF;
  } else if (x == S21_INF) {
    func_N_1 = S21_INF;
  }
  return (func_N_1 + ex_pow);
}

long double s21_find(double a, double x) {
  long double res = 2;
  if (a == 0) {
    if (x == 0) {
      res = 1;
    } else if (x == -S21_INF || x < 0) {
      res = S21_INF;
    } else if (x == S21_INF || x > 0) {
      res = 0;
    } else if (x == S21_NAN) {
      res = S21_NAN;
    }
  }
  if (a > 0 && a < 1) {
    if (x == S21_INF) {
      res = 0;
    } else if (x == -S21_INF) {
      res = S21_INF;
    } else if (x == S21_NAN || x == -S21_NAN) {
      res = S21_NAN;
    }
  }
  if (a == 1) {
    res = 1;
  }
  if (a > 1) {
    if (x == -S21_INF) {
      res = 0;
    }
  }
  if (a > -1 && a < 0) {
    if (x == S21_INF) {
      res = 0;
    } else if (x == -S21_INF) {
      res = S21_NAN;
    } else if (x != (int)x) {
      res = S21_NAN;
    }
  }
  if (a == -1) {
    if (x == S21_INF || x == -S21_INF) {
      res = 1;
    }
  }
  if (a < -1) {
    if (x == S21_INF) {
      res = S21_INF;
    } else if (x == -S21_INF) {
      res = 0;
    } else if (x != (int)x) {
      res = S21_NAN;
    }
  }
  if (a == S21_NAN || a == -S21_NAN) {
    if (x == 0) {
      res = 1;
    } else {
      res = S21_NAN;
    }
  }
  if (a == S21_INF) {
    if (x == S21_INF || x > 0) {
      res = S21_INF;
    } else if (x == -S21_INF || x < 0) {
      res = 0;
    }
  }
  if (a == -S21_INF) {
    if (x == S21_INF || x > 0) {
      res = S21_INF;
      if (x == (int)x && (int)x % 2 == 1) {
        res = -S21_INF;
      }
    } else if (x == -S21_INF || x < 0) {
      res = 0;
      x = x * (-1);
      if (x == (int)x && (int)x % 2 == 1) {
        res *= (-1);
      }
    }
  }
  return res;
}

long double s21_sin(double x) {
  long double res = 0;
  long double value = 1;
  if (s21_fabs(x) <= 0.000001) {
    value = 0.0;
    res = 0.0;
  }
  s21_round_to_PI(&x);
  for (double i = 0.0; value > S21_EPS && i < 100; i++) {
    value =
        (s21_pow(-1.00, i) * s21_pow(x, 1 + 2 * i)) / s21_factorial(1 + 2 * i);
    res = res + value;
    if (value < 0) {
      value = value * (-1);
    }
  }
  return res;
}

long double s21_cos(double x) {
  long double res = 0;
  long double value = 1;
  if (s21_fabs(x) <= 0.000001) {
    value = 0.0;
    res = 1;
  }
  s21_round_to_PI(&x);
  for (double i = 0.0; value > S21_EPS && i < 100; i++) {
    value = (s21_pow(-1.00, i) * s21_pow(x, 2 * i)) / s21_factorial(2 * i);
    res = res + value;
    if (value < 0) {
      value = value * (-1);
    }
  }
  return res;
}

long double s21_tan(double x) {
  long double res = 0;
  if (x == S21_PI / 2 || x == S21_PI / 2) {
    res = S21_NAN;
  } else {
    res = s21_sin(x) / s21_cos(x);
  }
  return res;
}

long double s21_atan(double x) {
  long double res = 0;
  long double value = 1;
  int flag_no_inf = 1;
  if (x == S21_OTR_INF || x == S21_INF || is_S21_NAN(x)) {
    flag_no_inf = 0;
    res = S21_PI / 2;
    if (x == S21_OTR_INF) {
      res = (-1) * res;
    }
    if (is_S21_NAN(x)) {
      res = S21_NAN;
    }
  }
  if (flag_no_inf == 1) {
    if (x < 1 && x > -1) {
      for (register int i = 1; i < 10000 && value > S21_EPS; i++) {
        value = (s21_pow(-1.00, i - 1) * s21_pow(x, 2 * i - 1)) / (2 * i - 1);
        res = res + value;
        if (value < 0) {
          value = value * (-1);
        }
      }
    } else if (x > 1 || x < -1) {
      for (register int i = 0; value > S21_EPS; i++) {
        value = s21_pow(-1, i) * s21_pow(x, -1 - (2 * i)) / (1 + (2 * i));
        res += value;
        if (value < 0) {
          value = value * (-1);
        }
      }
      res = S21_PI * s21_fabs(x) / (2 * x) - res;
    } else if (x == 1 || x == -1) {
      res = S21_PI / 4.;
      if (x == -1) {
        res = res * (-1);
      }
    }
  }

  return res;
}

int s21_abs(int x) {
  if (x < 0) x = -x;
  return x;
}

long double s21_fabs(double x) {
  if (x < 0.0) x = -x;
  return x;
}

long double s21_floor(double x) {
  long double y = x;
  if (is_S21_INF(x) != 1) {
    if (y - (long long)x < 0) {
      x = y - (y - (long long)x) - 1;
    } else {
      x = (long long)x;
    }
  }
  return x;
}

long double s21_ceil(double x) {
  long double y = x;
  if (is_S21_INF(x) != 1) {
    if (y - (long long)x > 0) {
      x = y - (y - (long long)x) + 1;
    } else {
      x = y - (y - (long long)x);
    }
  }
  return x;
}

long double s21_fmod(double x, double y) {
  long double div_rem = 0;
  if (is_S21_INF(x) || is_S21_INF(y)) {
    div_rem = S21_NAN;
    if ((y == S21_INF || y == -S21_INF) && (!is_S21_INF(x))) {
      div_rem = x;
    }
  } else {
    int m = 0;
    if (x < 0) {
      x = -x;
      m++;
    }
    if (y < 0) {
      y = -y;
    }
    double z = s21_floor(x / y);
    div_rem = x - z * y;
    if (m == 1) {
      div_rem = -div_rem;
    }
  }
  return div_rem;
}

long double s21_sqrt(double x) {
  long double res = 0;
  if (x >= 0) {
    if (x == S21_INF) {
      res = S21_INF;
    } else {
      res = s21_pow(x, 0.5);
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_asin(double x) {
  long double res = 0;
  if (x > -1 && x < 1) {
    res = s21_atan(x / s21_sqrt(1 - x * x));
  } else if (x == 1 || x == -1) {
    res = S21_PI / 2.;
    if (x == -1) {
      res = -S21_PI / 2.;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_acos(double x) {
  long double res = 0;
  if (x > 0 && x < 1) {
    res = s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (x > -1 && x < 0) {
    res = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (x == 0 || x == 1 || x == -1) {
    if (x == 0) {
      res = S21_PI / 2;
    } else if (x == 1) {
      res = 0;
    } else {
      res = S21_PI;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

void s21_round_to_PI(double *a) {
  int i = 0;
  if (*a != -S21_INF) {
    if (*a != S21_INF) {
      while (s21_fabs(*a) > (2.0 * S21_PI)) {
        i++;
        if (*a < 0) {
          *a = *a + S21_PI;
        } else {
          *a = *a - S21_PI;
        }
      }
    }
  }
}
