#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  s21_size_t i = 0;
  while (src[i]) {
    dest[i] = src[i];
    i++;
  }
  return ptr;
}