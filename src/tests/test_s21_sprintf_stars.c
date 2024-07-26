#include <stdio.h>

#include "tests.h"

START_TEST(test_sprintf_stars_1) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "%*.*ftest";
  float chr_in = 127.1515;
  int res1 = sprintf(str_out1, str_in, 2, 3, chr_in);
  int res2 = s21_sprintf(str_out2, str_in, 2, 3, chr_in);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sprintf_stars_2) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "%*ctest";
  char chr_in = 88;
  int res1 = sprintf(str_out1, str_in, 11, chr_in);
  int res2 = s21_sprintf(str_out2, str_in, 11, chr_in);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sprintf_stars_3) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "%*dtest";
  int chr_in = -127;
  int res1 = sprintf(str_out1, str_in, 11, chr_in);
  int res2 = s21_sprintf(str_out2, str_in, 11, chr_in);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sprintf_stars_4) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "%*stest";
  char chr_in[] = "New file";
  int res1 = sprintf(str_out1, str_in, 3, chr_in);
  int res2 = s21_sprintf(str_out2, str_in, 3, chr_in);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sprintf_stars_5) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "%*utest";
  int chr_in = -127;
  int res1 = sprintf(str_out1, str_in, 20, chr_in);
  int res2 = s21_sprintf(str_out2, str_in, 20, chr_in);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sprintf_stars_suite(void) {
  Suite *s = suite_create("s21_sprintf_stars");
  TCase *tc = tcase_create("s21_sprintf_stars");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_sprintf_stars_1);
  tcase_add_test(tc, test_sprintf_stars_2);
  tcase_add_test(tc, test_sprintf_stars_3);
  tcase_add_test(tc, test_sprintf_stars_4);
  tcase_add_test(tc, test_sprintf_stars_5);
  return s;
}
