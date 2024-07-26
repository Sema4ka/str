#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *tmp = str;
  s21_size_t flag = 0;
  for (s21_size_t i = 0; flag == 0 && tmp && i < n; i++) {
    if (tmp[i] == c) {
      tmp += i;
      flag = 1;
    }
  }
  return flag ? ((void *)tmp) : S21_NULL;
}