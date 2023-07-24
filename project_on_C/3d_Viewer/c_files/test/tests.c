#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../3D_Viewer.h"

START_TEST(shift_dot_x_2) {
  obj_data info;
  info.facets_count = 0;
  info.verts_count = 0;
  char *name = "c_files/test/cube.obj";
  count(name, &info);
  parser(name, &info);
  shift_dot_x(&info, 2.000000);
  shift_dot_y(&info, 2.000000);
  shift_dot_z(&info, 2.000000);
  double vert_test[] = {3.000000, 3.00000,  3.000000, 3.000000, 3.000000,
                        3.000000, 3.000000, 3.000000, 3.000000, 3.000000,
                        3.000000, 3.000000, 3.000000, 3.000000, 3.000000,
                        3.000000, 3.000000, 3.000000, 3.000000, 3.000000,
                        3.000000, 3.000000, 3.000000, 3.000000};
  for (unsigned int i = 0; i < info.verts_count; i++) {
    ck_assert_double_eq(info.verts[i], vert_test[i]);
  }
  free(info.verts);
  free(info.facets);
}
END_TEST

START_TEST(rotate_x_2) {
  obj_data info;
  info.facets_count = 0;
  info.verts_count = 0;
  char *name = "c_files/test/cube.obj";
  count(name, &info);
  parser(name, &info);
  rotate_x(&info, 45);
  rotate_y(&info, 45);
  rotate_z(&info, 45);
  double vert_test[] = {1.207107,  -1.207107, 0.292893,  1.207107,  -1.207107,
                        0.292893,  1.207107,  -1.207107, 0.292893,  1.207107,
                        -1.207107, 0.292893,  1.207107,  -1.207107, 0.292893,
                        1.207107,  -1.207107, 0.292893,  1.207107,  -1.207107,
                        0.292893,  1.207107,  -1.207107, 0.292893};
  for (unsigned int i = 0; i < info.verts_count; i++) {
    ck_assert_ldouble_eq_tol(info.verts[i], vert_test[i], 0.000001);
  }
  free(info.verts);
  free(info.facets);
}
END_TEST

START_TEST(scale_c_2) {
  obj_data info;
  info.facets_count = 0;
  info.verts_count = 0;
  char *name = "c_files/test/cube_scale.obj";
  count(name, &info);
  parser(name, &info);
  scale_c(&info);
  double vert_test[] = {1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000,
                        1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000,
                        -1.000000, -1.000000, 1.000000,  1.000000,  -1.000000,
                        1.000000,  1.000000,  1.000000,  -1.000000, 1.000000,
                        1.000000,  -1.000000, 1.000000,  -1.000000};
  for (unsigned int i = 0; i < info.verts_count; i++) {
    ck_assert_ldouble_eq_tol(info.verts[i], vert_test[i], 0.000001);
  }
  free(info.verts);
  free(info.facets);
}
END_TEST

START_TEST(normal) {
  obj_data info;
  char *name = "file.txt";
  count(name, &info);
  parser(name, &info);
  double vert_test[] = {1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000,
                        1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000,
                        -1.000000, -1.000000, 1.000000,  1.000000,  -0.999999,
                        0.999999,  1.000000,  1.000001,  -1.000000, 1.000000,
                        1.000000,  -1.000000, 1.000000,  -1.000000};
  int facet_test[] = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                      5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                      0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                      1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  for (unsigned int i = 0; i < info.verts_count * 3; i++) {
    ck_assert_double_eq(info.verts[i], vert_test[i]);
  }
  for (unsigned int k = 0; k < info.facets_count; k++) {
    ck_assert_double_eq(info.facets[k], facet_test[k]);
  }
  free(info.verts);
  free(info.facets);
}
END_TEST

START_TEST(no_file) {
  obj_data info;
  char *name = "no";
  int a = count(name, &info);
  int b = parser(name, &info);
  ck_assert_int_eq(a, 0);
  ck_assert_int_eq(b, 0);
}
END_TEST

Suite *suite() {
  Suite *s;
  s = suite_create("Viewer");
  TCase *tc_all;
  tc_all = tcase_create("all tests");
  tcase_add_test(tc_all, shift_dot_x_2);
  tcase_add_test(tc_all, rotate_x_2);
  tcase_add_test(tc_all, scale_c_2);
  tcase_add_test(tc_all, normal);
  tcase_add_test(tc_all, no_file);

  suite_add_tcase(s, tc_all);

  return s;
}

int main(void) {
  int success = 0;
  Suite *s;
  SRunner *runner;
  s = suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  success = srunner_ntests_failed(runner);
  srunner_free(runner);
  return !(success == 0);
}
