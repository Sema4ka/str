#include <stdio.h>
#include <string.h>

#include "tests.h"

START_TEST(test_sscanf_1) {
  char str_format[] = "%c";
  char str_in[] = "a";
  char chr_in_a;
  char chr_in_b;
  int res1 = sscanf(str_in, str_format, &chr_in_a);
  int res2 = s21_sscanf(str_in, str_format, &chr_in_b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(chr_in_a, chr_in_b);
}
END_TEST

START_TEST(test_sscanf_2) {
  char str_format[] = "%c %*c %c";
  char str_in[] = "a b c";
  char chr_in_a_1;
  char chr_in_a_2;
  char chr_in_b_1;
  char chr_in_b_2;
  int res1 = sscanf(str_in, str_format, &chr_in_a_1, &chr_in_a_2);
  int res2 = s21_sscanf(str_in, str_format, &chr_in_b_1, &chr_in_b_2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(chr_in_a_1, chr_in_b_1);
  ck_assert_int_eq(chr_in_a_2, chr_in_b_2);
}
END_TEST

START_TEST(test_sscanf_3) {
  char str_format[] = "%c %c %c";
  char str_in[] = "abc";
  char chr_in_a_1;
  char chr_in_a_2;
  char chr_in_a_3;
  char chr_in_b_1;
  char chr_in_b_2;
  char chr_in_b_3;
  int res1 = sscanf(str_in, str_format, &chr_in_a_1, &chr_in_a_2, &chr_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &chr_in_b_1, &chr_in_b_2, &chr_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(chr_in_a_1, chr_in_b_1);
  ck_assert_int_eq(chr_in_a_2, chr_in_b_2);
  ck_assert_int_eq(chr_in_a_3, chr_in_b_3);
}
END_TEST

START_TEST(test_sscanf_4) {
  char str_format[] = "%d %d %d";
  char str_in[] = "127 256 0x12";
  int int_in_a_1;
  int int_in_a_2;
  int int_in_a_3;
  int int_in_b_1;
  int int_in_b_2;
  int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_5) {
  char str_format[] = "%hd %hd %hd";
  char str_in[] = "127 255 -10";
  short int int_in_a_1;
  short int int_in_a_2;
  short int int_in_a_3;
  short int int_in_b_1;
  short int int_in_b_2;
  short int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_6) {
  char str_format[] = "%hd %hd %hd";
  char str_in[] = "127 255 -10";
  short int int_in_a_1;
  short int int_in_a_2;
  short int int_in_a_3;
  short int int_in_b_1;
  short int int_in_b_2;
  short int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_7) {
  char str_format[] = "%ld %ld %ld";
  char str_in[] = "127 13151285255 -10";
  long int int_in_a_1;
  long int int_in_a_2;
  long int int_in_a_3;
  long int int_in_b_1;
  long int int_in_b_2;
  long int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_8) {
  char str_format[] = "%s";
  char str_in[] = "String to store";
  char str_in_a[100];
  char str_in_b[100];
  int res1 = sscanf(str_in, str_format, &str_in_a);
  int res2 = s21_sscanf(str_in, str_format, &str_in_b);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str_in_a, str_in_b);
}
END_TEST

START_TEST(test_sscanf_9) {
  char str_format[] = "%s %s %s";
  char str_in[] = "String to store";
  char str_in_a_1[100], str_in_a_2[100], str_in_a_3[100];
  char str_in_b_1[100], str_in_b_2[100], str_in_b_3[100];
  int res1 = sscanf(str_in, str_format, &str_in_a_1, &str_in_a_2, &str_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &str_in_b_1, &str_in_b_2, &str_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str_in_a_1, str_in_b_1);
  ck_assert_str_eq(str_in_a_2, str_in_b_2);
  ck_assert_str_eq(str_in_a_3, str_in_b_3);
}
END_TEST

START_TEST(test_sscanf_10) {
  char str_format[] = "%14f %4f %1f";
  char str_in[] = "123.123 15.9 10e15";
  float float_in_a_1;
  float float_in_a_2;
  float float_in_a_3;
  float float_in_b_1;
  float float_in_b_2;
  float float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_11) {
  char str_format[] = "%14lf %3lf %1lf";
  char str_in[] = "123.1223 3.0 10e127";
  double float_in_a_1;
  double float_in_a_2;
  double float_in_a_3;
  double float_in_b_1;
  double float_in_b_2;
  double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_12) {
  char str_format[] = "%14Lf %3Lf %1Lf";
  char str_in[] = "123.1223 3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_13) {
  char str_format[] = "%14Lf %3Lf %1Lf";
  char str_in[] = "123.1223 3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_14) {
  char str_format[] = "%hu %hu %hu";
  char str_in[] = "127 255 -10";
  short int int_in_a_1;
  short int int_in_a_2;
  short int int_in_a_3;
  short int int_in_b_1;
  short int int_in_b_2;
  short int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_15) {
  char str_format[] = "%u %u %u";
  char str_in[] = "127 256 -1000";
  int int_in_a_1;
  int int_in_a_2;
  int int_in_a_3;
  int int_in_b_1;
  int int_in_b_2;
  int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_16) {
  char str_format[] = "%lu %lu %lu";
  char str_in[] = "127 13151285255 -10";
  long int int_in_a_1;
  long int int_in_a_2;
  long int int_in_a_3;
  long int int_in_b_1;
  long int int_in_b_2;
  long int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_17) {
  char str_out1[100];
  char str_out2[100];
  char str_in[] = "abra%pcadabra";
  int chr_in_1 = 0;

  int res1 = sprintf(str_out1, str_in, &chr_in_1);
  int res2 = sprintf(str_out2, str_in, &chr_in_1);
  ck_assert_str_eq(str_out1, str_out2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_18) {
  char str_format[] = "%14g %4g %1g";
  char str_in[] = "123.123 15.9 10e15";
  float float_in_a_1;
  float float_in_a_2;
  float float_in_a_3;
  float float_in_b_1;
  float float_in_b_2;
  float float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_19) {
  char str_format[] = "%14lg %3lg %1lg";
  char str_in[] = "123.1223 3.0 10e127";
  double float_in_a_1;
  double float_in_a_2;
  double float_in_a_3;
  double float_in_b_1;
  double float_in_b_2;
  double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_20) {
  char str_format[] = "%14Lg %3Lg %1Lg";
  char str_in[] = "123.1223 -3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_21) {
  char str_format[] = "%14Lg %3Lg %1Lg";
  char str_in[] = "123.1223 3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_22) {
  char str_format[] = "%14f %4f %1f";
  char str_in[] = "123.123 15.9 10e15";
  float float_in_a_1;
  float float_in_a_2;
  float float_in_a_3;
  float float_in_b_1;
  float float_in_b_2;
  float float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_23) {
  char str_format[] = "%14lf %3lf %1lf";
  char str_in[] = "123.1223 3.0 10e127";
  double float_in_a_1;
  double float_in_a_2;
  double float_in_a_3;
  double float_in_b_1;
  double float_in_b_2;
  double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_24) {
  char str_format[] = "%14Lf %3Lf %1Lf";
  char str_in[] = "123.1223 3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_25) {
  char str_format[] = "%14Lf %3Lf %1Lf";
  char str_in[] = "123.1223 3.0 10e127";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_26) {
  char str_format[] = "%i %7i %3i %*i";
  char str_in[] = "0xfa5 0X2F6 -0171 181";
  int int_in_a_1;
  int int_in_a_2;
  int int_in_a_3;
  int int_in_b_1;
  int int_in_b_2;
  int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_27) {
  char str_format[] = "%hi %7hi %3hi %*hi";
  char str_in[] = "0xfa5 0X2F6 -0171 181";
  short int int_in_a_1;
  short int int_in_a_2;
  short int int_in_a_3;
  short int int_in_b_1;
  short int int_in_b_2;
  short int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_28) {
  char str_format[] = "%li %7li %3li %*li";
  char str_in[] = "0xfa5 0X2F6 -0171 181";
  long int int_in_a_1;
  long int int_in_a_2;
  long int int_in_a_3;
  long int int_in_b_1;
  long int int_in_b_2;
  long int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_29) {
  char str_format[] = "%x %X %o %*x %*o";
  char str_in[] = "0xfa5 -0X2F6 -0171 181 182";
  unsigned int int_in_a_1;
  unsigned int int_in_a_2;
  unsigned int int_in_a_3;
  unsigned int int_in_b_1;
  unsigned int int_in_b_2;
  unsigned int int_in_b_3;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3);
  int res2 =
      s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2, &int_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
}
END_TEST

START_TEST(test_sscanf_30) {
  char str_format[] = "%6s%%%s %n %5s";
  char str_in[] = "String%to store";
  int number1, number2;
  char str_in_a_1[100], str_in_a_2[100], str_in_a_3[100];
  char str_in_b_1[100], str_in_b_2[100], str_in_b_3[100];
  int res1 = sscanf(str_in, str_format, &str_in_a_1, &str_in_a_2, &number1,
                    &str_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &str_in_b_1, &str_in_b_2, &number2,
                        &str_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str_in_a_1, str_in_b_1);
  ck_assert_str_eq(str_in_a_2, str_in_b_2);
  ck_assert_str_eq(str_in_a_3, str_in_b_3);
}
END_TEST

START_TEST(test_sscanf_31) {
  char str_format[] = "%c%";
  char str_in[] = "String%to store";
  char str_in_a_1;
  char str_in_b_1;
  int res1 = sscanf(str_in, str_format, &str_in_a_1);
  int res2 = s21_sscanf(str_in, str_format, &str_in_b_1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(str_in_a_1, str_in_b_1);
}
END_TEST

START_TEST(test_sscanf_32) {
  char str_format[] = "%k";
  char str_in[] = "String%to store";
  char str_in_a_1 = 0;
  char str_in_b_1 = 0;
  int res1 = sscanf(str_in, str_format, &str_in_a_1);
  int res2 = s21_sscanf(str_in, str_format, &str_in_b_1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(str_in_a_1, str_in_b_1);
}
END_TEST

START_TEST(test_sscanf_33) {
  char str_format[] = "%c%*s";
  char str_in[] = "String%to store";
  char str_in_a_1;
  char str_in_b_1;
  int res1 = sscanf(str_in, str_format, &str_in_a_1);
  int res2 = s21_sscanf(str_in, str_format, &str_in_b_1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(str_in_a_1, str_in_b_1);
}
END_TEST

START_TEST(test_sscanf_34) {
  char str_format[] = "%14f %4f %1f";
  char str_in[] = "NaN -Inf INF";
  float float_in_a_1 = 0;
  float float_in_a_2 = 0;
  float float_in_a_3 = 0;
  float float_in_b_1 = 0;
  float float_in_b_2 = 0;
  float float_in_b_3 = 0;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  int res3 = (fabs(float_in_a_3 - float_in_b_3) < 0.000000001);
  ck_assert_float_nan(float_in_b_1);
  ck_assert_float_infinite(float_in_b_2);
  ck_assert_float_nan(float_in_a_1);
  ck_assert_float_infinite(float_in_a_2);
  ck_assert_int_eq(res3, 1);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_35) {
  char str_format[] = "%3e %2E %1e";
  char str_in[] = "123.123e-12 15.9E10 10e15";
  float float_in_a_1;
  float float_in_a_2;
  float float_in_a_3;
  float float_in_b_1;
  float float_in_b_2;
  float float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  int res3 = (fabs(float_in_a_1 - float_in_b_1) < 0.000000001);
  int res4 = (fabs(float_in_a_2 - float_in_b_2) < 0.000000001);
  int res5 = (fabs(float_in_a_3 - float_in_b_3) < 0.000000001);
  ck_assert_int_eq(res3, 1);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_36) {
  char str_format[] = "%14le %3lE %1le";
  char str_in[] = "123.123e-12 15.9E10 10e15";
  double float_in_a_1;
  double float_in_a_2;
  double float_in_a_3;
  double float_in_b_1;
  double float_in_b_2;
  double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_37) {
  char str_format[] = "%14Le %3LE %1Le";
  char str_in[] = "123.123e-12 15.9E10 10e15";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_38) {
  char str_format[] = "%14Le %3Le %1LE";
  char str_in[] = "123.123e-12 15.9E10 10e15";
  long double float_in_a_1;
  long double float_in_a_2;
  long double float_in_a_3;
  long double float_in_b_1;
  long double float_in_b_2;
  long double float_in_b_3;
  int res1 =
      sscanf(str_in, str_format, &float_in_a_1, &float_in_a_2, &float_in_a_3);
  int res2 = s21_sscanf(str_in, str_format, &float_in_b_1, &float_in_b_2,
                        &float_in_b_3);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(float_in_a_1, float_in_b_1);
  ck_assert_float_eq(float_in_a_2, float_in_b_2);
  ck_assert_float_eq(float_in_a_3, float_in_b_3);
}
END_TEST

START_TEST(test_sscanf_39) {
  char str_format[] = "%hx %lX %ho %lo";
  char str_in[] = "0xfa5 -0X2F6 -0171 181";
  short int int_in_a_1;
  long int int_in_a_2;
  short int int_in_a_3;
  long int int_in_a_4;
  short int int_in_b_1;
  long int int_in_b_2;
  short int int_in_b_3;
  long int int_in_b_4;
  int res1 = sscanf(str_in, str_format, &int_in_a_1, &int_in_a_2, &int_in_a_3,
                    &int_in_a_4);
  int res2 = s21_sscanf(str_in, str_format, &int_in_b_1, &int_in_b_2,
                        &int_in_b_3, &int_in_b_4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_in_a_1, int_in_b_1);
  ck_assert_int_eq(int_in_a_2, int_in_b_2);
  ck_assert_int_eq(int_in_a_3, int_in_b_3);
  ck_assert_int_eq(int_in_a_4, int_in_b_4);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("s21_sscanf");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_sscanf_1);
  tcase_add_test(tc, test_sscanf_2);
  tcase_add_test(tc, test_sscanf_3);
  tcase_add_test(tc, test_sscanf_4);
  tcase_add_test(tc, test_sscanf_5);
  tcase_add_test(tc, test_sscanf_6);
  tcase_add_test(tc, test_sscanf_7);
  tcase_add_test(tc, test_sscanf_8);
  tcase_add_test(tc, test_sscanf_9);
  tcase_add_test(tc, test_sscanf_10);
  tcase_add_test(tc, test_sscanf_11);
  tcase_add_test(tc, test_sscanf_12);
  tcase_add_test(tc, test_sscanf_13);
  tcase_add_test(tc, test_sscanf_14);
  tcase_add_test(tc, test_sscanf_15);
  tcase_add_test(tc, test_sscanf_16);
  tcase_add_test(tc, test_sscanf_17);
  tcase_add_test(tc, test_sscanf_18);
  tcase_add_test(tc, test_sscanf_19);
  tcase_add_test(tc, test_sscanf_20);
  tcase_add_test(tc, test_sscanf_21);
  tcase_add_test(tc, test_sscanf_22);
  tcase_add_test(tc, test_sscanf_23);
  tcase_add_test(tc, test_sscanf_24);
  tcase_add_test(tc, test_sscanf_25);
  tcase_add_test(tc, test_sscanf_26);
  tcase_add_test(tc, test_sscanf_27);
  tcase_add_test(tc, test_sscanf_28);
  tcase_add_test(tc, test_sscanf_29);
  tcase_add_test(tc, test_sscanf_30);
  tcase_add_test(tc, test_sscanf_31);
  tcase_add_test(tc, test_sscanf_32);
  tcase_add_test(tc, test_sscanf_33);
  tcase_add_test(tc, test_sscanf_34);
  tcase_add_test(tc, test_sscanf_35);
  tcase_add_test(tc, test_sscanf_36);
  tcase_add_test(tc, test_sscanf_37);
  tcase_add_test(tc, test_sscanf_38);
  tcase_add_test(tc, test_sscanf_39);
  return s;
}
