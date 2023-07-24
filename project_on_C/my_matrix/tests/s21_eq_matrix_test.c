#include "unit.h"

START_TEST(eq_test_1) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(4, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_2) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = i + j + 1.9999999;
      B.matrix[i][j] = i + j + 1.9999998;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_3) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(10, 5, &A);
  s21_create_matrix(10, 5, &B);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_4) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(10, 50, &A);
  s21_create_matrix(10, 50, &B);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 50; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_5) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B.matrix[i][j] = A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_6) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(100, 500, &A);
  s21_create_matrix(100, 500, &B);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 500; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_7) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_8) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1, 2, &A);
  B.matrix = NULL;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_9) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(0, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_10) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_11) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = i + j + 0.999999999;
      B.matrix[i][j] = i + j + 0.999999998;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_12) {
  matrix_t A, B;
  A.matrix = NULL;
  B.matrix = NULL;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  // s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

Suite *suite_s21_eq_matrix(void) {
  Suite *s = suite_create("equality tests");
  TCase *tc_eq_test = tcase_create("equality tests");
  suite_add_tcase(s, tc_eq_test);
  tcase_add_test(tc_eq_test, eq_test_1);
  tcase_add_test(tc_eq_test, eq_test_2);
  tcase_add_test(tc_eq_test, eq_test_3);
  tcase_add_test(tc_eq_test, eq_test_4);
  tcase_add_test(tc_eq_test, eq_test_5);
  tcase_add_test(tc_eq_test, eq_test_6);
  tcase_add_test(tc_eq_test, eq_test_7);
  tcase_add_test(tc_eq_test, eq_test_8);
  tcase_add_test(tc_eq_test, eq_test_9);
  tcase_add_test(tc_eq_test, eq_test_10);
  tcase_add_test(tc_eq_test, eq_test_11);
  tcase_add_test(tc_eq_test, eq_test_12);
  return s;
}
