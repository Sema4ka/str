#include "s21_string.h"

s21_size_t s21_strlen(const char *p) {
  s21_size_t len = 0;
  while (p && *(p + len)) len++;
  return len;
}