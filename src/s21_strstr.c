#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *str1 = S21_NULL;
  int len = s21_strlen(needle);
  for (int i = 0; str1 == S21_NULL && haystack[i] != '\0'; i++) {
    if (s21_strncmp(haystack + i, needle, len) == 0) {
      str1 = haystack + i;
    }
  }

  return (char *)str1;
}