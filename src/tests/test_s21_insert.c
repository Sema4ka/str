#include "tests.h"

START_TEST(test_s21_insert_1) {
  char str1[] = "HEllo,!";
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = "HEllo, WoRld!";
  str3 = s21_insert(str1, str2, 6);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_2) {
  char str1[] = "HEllo,!";
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = " WoRldHEllo,!";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_3) {
  char str1[] = "HEllo,!";
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = "HEllo,! WoRld";
  str3 = s21_insert(str1, str2, 7);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_4) {
  char str1[] = "HEllo,!";
  char str2[] = "";
  char* str3 = S21_NULL;
  char* res = "HEllo,!";
  str3 = s21_insert(str1, str2, 2);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_5) {
  char str1[] = "";
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = " WoRld";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_6) {
  char str1[] = "HEllo,!";
  char str2[] = "";
  char* str3 = S21_NULL;
  char* res = "HEllo,!";
  str3 = s21_insert(str1, str2, 2);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_7) {
  char str1[] = "";
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = " WoRld";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_8) {
  char* str1 = S21_NULL;
  char str2[] = " WoRld";
  char* str3 = S21_NULL;
  char* res = " WoRld";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_9) {
  char str1[] = " WoRld";
  char* str2 = S21_NULL;
  char* str3 = S21_NULL;
  char* res = " WoRld";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_10) {
  char str1[] = " WoRld";
  char* str2 = S21_NULL;
  char* str3 = S21_NULL;
  char* res = " WoRld";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

START_TEST(test_s21_insert_11) {
  char* str1 = S21_NULL;
  char* str2 = S21_NULL;
  char* str3 = S21_NULL;
  char* res = "";
  str3 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(res, str3);
  if (str3) free(str3);
}
END_TEST

Suite* s21_insert_suite(void) {
  Suite* s = suite_create("s21_insert");
  TCase* tc = tcase_create("s21_insert");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_s21_insert_1);
  tcase_add_test(tc, test_s21_insert_2);
  tcase_add_test(tc, test_s21_insert_3);
  tcase_add_test(tc, test_s21_insert_4);
  tcase_add_test(tc, test_s21_insert_5);
  tcase_add_test(tc, test_s21_insert_6);
  tcase_add_test(tc, test_s21_insert_7);
  tcase_add_test(tc, test_s21_insert_8);
  tcase_add_test(tc, test_s21_insert_9);
  tcase_add_test(tc, test_s21_insert_10);
  tcase_add_test(tc, test_s21_insert_11);
  return s;
}