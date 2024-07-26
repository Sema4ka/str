#include "tests.h"

START_TEST(test_trim_1) {
  char str1[] = "     \t   \n     HEllo, WoRld!   \n    \t        ";
  char str2[] = " \t\n";
  char* str3 = S21_NULL;
  char* res = "HEllo, WoRld!";
  str3 = s21_trim(str1, str2);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_trim_2) {
  char str1[] = "     \t   \n     H E\tl l\to, W\toRld!   \n    \t        ";
  char str2[] = " \t\n";
  char* str3 = S21_NULL;
  char* res = "H E\tl l\to, W\toRld!";
  str3 = s21_trim(str1, str2);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_trim_3) {
  char str1[] = "            ";
  char str2[] = " ";
  char* str3 = S21_NULL;
  char* res = "";
  str3 = s21_trim(str1, str2);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_trim_4) {
  char* str1 = S21_NULL;
  char str2[] = " ";
  char* str3 = S21_NULL;
  char* res = S21_NULL;
  str3 = s21_trim(str1, str2);
  ck_assert_ptr_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_trim_5) {
  char* str1 = S21_NULL;
  char* str2 = S21_NULL;
  char* str3 = S21_NULL;
  char* res = S21_NULL;
  str3 = s21_trim(str1, str2);
  ck_assert_ptr_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_trim_6) {
  char str1[] = " ";
  char* str2 = S21_NULL;
  char* str3 = S21_NULL;
  char* res = S21_NULL;
  str3 = s21_trim(str1, str2);
  ck_assert_ptr_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

Suite* s21_trim_suite(void) {
  Suite* s = suite_create("s21_trim");
  TCase* tc = tcase_create("s21_trim");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_trim_1);
  tcase_add_test(tc, test_trim_2);
  tcase_add_test(tc, test_trim_3);
  tcase_add_test(tc, test_trim_4);
  tcase_add_test(tc, test_trim_5);
  tcase_add_test(tc, test_trim_6);

  return s;
}