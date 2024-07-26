#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  s21_size_t len = s21_strlen(str);
  char *rtn = S21_NULL;
  for (int i = len; i >= 0 && rtn == S21_NULL; i--) {
    if (str[i] == c) rtn = (char *)&str[i];
  }
  return rtn;
}