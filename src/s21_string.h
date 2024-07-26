#ifndef S21_SRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"

#define S21_NULL (void *)0

#define DEFAULT_VALUE -1
#define STAR -2
#define NULL_STRUCT -3

typedef unsigned long long s21_size_t;

s21_size_t s21_strlen(const char *p);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int s);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int s21_strncmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim);
char *s21_strerror(int errnum);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);

char *int_to_str(long int inp);
char *float_to_str(double inp, int size);

int s21_sprintf(char *str, const char *format, ...);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
