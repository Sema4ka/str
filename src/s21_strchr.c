#include "s21_string.h"

char *s21_strchr(const char *str, int s) {
  char *rtn = S21_NULL;
  for (s21_size_t i = 0; (rtn == S21_NULL) && i <= s21_strlen(str); ++i) {
    if (str[i] == s) rtn = (char *)str + i;
  }
  return rtn;
}
