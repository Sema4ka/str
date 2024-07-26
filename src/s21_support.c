#include <math.h>

#include "s21_string.h"

char* int_to_str(long int inp) {
  long int del = 1;
  int i = 0;
  while (inp / del != 0) {
    i++;
    del *= 10;
  }
  del /= 10;
  int mul = 10;
  int minus = 0;
  if (inp < 0) minus = 1;
  char* rez = malloc((i + 1 + minus) * sizeof(char));
  if (inp < 0) rez[0] = '-';
  for (int j = minus; j < i + minus; j++) {
    long int tmp = inp / del % mul;
    del /= 10;
    rez[j] = fabs((double)tmp) + 48;
  }
  rez[i + minus] = '\0';
  return rez;
}

char* float_to_str(double inp, int size) {
  long long int del = 1;
  long long int tm = (int)inp;
  int i = 0;
  int j = 0;
  int sum = 0;
  int f = 0;
  while (tm / del != 0) {
    i++;
    del *= 10;
  }
  del /= 10;
  int mul = 10;
  char* res = malloc((i + size + 2) * sizeof(char));
  if (inp < 0) {
    res[0] = 45;
    f = 1;
    tm *= -1;
    inp *= -1;
  }
  for (j = 0 + f; j < i + f; j++) {
    int tmp = tm / del % mul;
    del /= 10;
    res[j] = tmp + 48;
  }
  if (size != 0) res[i + f] = '.';
  j++;
  del = pow(10, size + 1);
  sum = inp;
  inp = inp * del;
  tm = inp;
  tm = tm - (sum * del);
  del = del / 10;
  int tmp = 0;
  for (int n = j; n < j + size; n++) {
    tmp = tm / del % mul;
    del /= 10;
    res[n] = tmp + 48;
  }
  tmp = tm / del % mul;
  printf("*%d*\n", tmp);
  if (tmp >= 5) {
    for (int n = j + size - 1; n >= j; n--) {
      if (res[n] >= 53) res[n] = res[n] + 1;
      if (res[n] == 58) res[n] -= 10;
    }
  }
  res[j + size] = '\0';
  return res;
}
