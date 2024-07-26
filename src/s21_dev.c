#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *res = (char *)malloc(sizeof(char) * (len + 1));
  if (res != S21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        res[i] = str[i] - 32;
      } else
        res[i] = str[i];
    }
    res[len] = '\0';
  }
  return res;
}

void *s21_to_lower(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *res = (char *)malloc(sizeof(char) * (len + 1));
  if (res != S21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        res[i] = str[i] + 32;
      } else
        res[i] = str[i];
    }
    res[len] = '\0';
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  s21_size_t len_src = (src == S21_NULL) ? 0 : s21_strlen(src);
  s21_size_t len_str = (str == S21_NULL) ? 0 : s21_strlen(str);
  if (start_index <= len_src) {
    res = (char *)calloc((len_src + len_str + 1), sizeof(char));
    if (res != S21_NULL) {
      s21_strncpy(res, src, start_index);
      s21_strncat(res, str, len_str);
      s21_strncat(res, src + start_index, len_src - (start_index));
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  const char *start = S21_NULL;
  const char *end = S21_NULL;
  char *res = S21_NULL;
  if (src && trim_chars) {
    start = src;
    while (*start && s21_strchr(trim_chars, *start)) start++;

    end = start + s21_strlen(start) - 1;
    while (*end && s21_strchr(trim_chars, *end)) end--;

    s21_size_t len = s21_strlen(start) - s21_strlen(end) + 1;
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res != S21_NULL) {
      s21_strncpy(res, start, len);
      res[len] = '\0';
    }
  }
  return res;
}
