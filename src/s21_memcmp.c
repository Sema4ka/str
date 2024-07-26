#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *tem1 = str1;
  const char *tem2 = str2;
  int res = 0;
  for (s21_size_t i = 0; res == 0 && i < n; i++) {
    res = tem1[i] - tem2[i];
  }
  return res;
}