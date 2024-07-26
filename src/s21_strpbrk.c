#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len = s21_strlen(str1);
  s21_size_t flag = 0;
  char *tmp = S21_NULL;
  s21_size_t i = 0;
  for (i = 0; flag == 0 && i < len; i++) {
    if (s21_strchr(str2, str1[i])) {
      flag = 1;
      tmp = (char *)&str1[i];
    }
  }
  return tmp;
}