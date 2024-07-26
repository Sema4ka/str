#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *tem_dest = (unsigned char *)dest;
  unsigned char *tem_src = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    tem_dest[i] = tem_src[i];
  }
  return dest;
}