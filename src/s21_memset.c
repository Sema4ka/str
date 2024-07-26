#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *tem_str = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    tem_str[i] = c;
  }
  return str;
}