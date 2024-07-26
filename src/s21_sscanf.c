#include "s21_string.h"

int s21_sscanf(const char* str, const char* format, ...) {
  Argument token = {0};
  token = argument_initialize(token);
  va_list args;
  va_start(args, format);
  unsigned long i = 0, j = 0;
  void* address;
  int count = 0, error = 1;

  while (parse_format(format, str, &token, &i, &j) && error) {
    if (check_token(token)) {
      if (!token.no_assignment && token.specifier != '%') {
        address = va_arg(args, void*);
      } else {
        address = S21_NULL;
      }
      write_argument(token, str, &j, address, &count, &error);
      token = argument_initialize(token);
    } else
      error = 0;
  }

  va_end(args);
  return count;
}

int parse_format(const char* format, const char* str, Argument* token,
                 unsigned long* i, unsigned long* j) {
  unsigned long str_length = s21_strlen(str);
  unsigned long format_length = s21_strlen(format);
  bool read = false;
  int error = 1;
  for (; *i < format_length && *j < str_length && !read; ++(*i)) {
    if (isspace(format[*i])) {
      while (isspace(str[*j])) ++(*j);
    } else if (isprint(format[*i]) && format[*i] != '%') {
      if (format[(*i)++] != str[(*j)++]) {
        error = 0;
        read = true;
      }
    } else if (format[*i] == '%') {
      ++(*i);
      if (format[*i] == '*') {
        ++(*i);
        token->no_assignment = true;
      }
      if (isdigit(format[*i])) {
        *i = get_width(format, *i, token);
      }
      if (s21_strchr("hlL", format[*i])) {
        token->length = format[(*i)++];
      }
      if (s21_strchr("cdieEfgGosuxXpn%", format[*i])) {
        token->specifier = format[(*i)];
        read = true;
      } else {
        error = 0;
        read = true;
      }
    } else {
      error = 0;
      read = true;
    }
  }
  return error && read;
}

bool check_token(Argument token) {
  return (
      (token.length == ' ' &&
       s21_strchr("cdieEfgGosuxXpn%", token.specifier)) ||
      (token.length == 'h' && s21_strchr("diuoxXn", token.specifier)) ||
      (token.length == 'l' && s21_strchr("csdiuoxXneEfgG", token.specifier)) ||
      (token.length == 'L' && s21_strchr("eEfgG", token.specifier)));
}

int get_width(const char* format, unsigned long position, Argument* token) {
  unsigned long res = 0;
  while (isdigit(format[position])) {
    res = (res * 10) + format[position++] - 48;
  }
  token->width = res;
  return position;
}

void write_argument(Argument token, const char* str, unsigned long* position,
                    void* address, int* count, int* error) {
  char s = token.specifier;
  if (s == 'c') write_char(token, str, position, address, count);
  if (s == 'd' || s == 'u') write_digit(token, str, position, address, count);
  if (s == 'i' || s == 'p') write_integer(token, str, position, address, count);
  if (s == 'g' || s == 'G' || s == 'f' || s == 'e' || s == 'E')
    write_float(token, str, position, address, count);
  if (s == 's') write_string(token, str, position, address, count);
  if (s == 'x' || s == 'X')
    write_hexadecimal(token, str, position, address, count);
  if (s == 'o') write_octal(token, str, position, address, count);
  if (s == 'n') write_number(token, position, address);
  if (s == '%') check_percent(str, position, error);
}

void write_char(Argument token, const char* str, unsigned long* position,
                void* address, int* count) {
  for (unsigned long i = 0;
       str[*position] && (token.width == 0 ? (i == 0) : (i < token.width));
       ++i) {
    if (token.no_assignment) {
      ++(*position);
    } else if (token.length == 'l') {
      ((wchar_t*)address)[i] = (wchar_t)str[(*position)++];
    } else {
      ((char*)address)[i] = (char)str[(*position)++];
    }
  }

  if (!token.no_assignment) ++(*count);
}

void write_digit(Argument token, const char* str, unsigned long* position,
                 void* address, int* count) {
  while (isspace(str[*position])) ++(*position);

  int sign = 0;
  long long res = 0;
  unsigned long i = 0;

  if (str[*position] == '-' || str[*position] == '+') {
    if (str[*position] == '-')
      sign = 2;
    else
      sign = 1;

    ++(*position);
    ++i;
  } else if (token.specifier == 'u')
    sign = 1;

  while (isdigit(str[*position]) &&
         (token.width == 0 ? true : (i < token.width))) {
    res = (res * 10) + (int)(str[(*position)++] - '0');
    ++i;
  }

  if (sign && !token.no_assignment) {
    if (sign == 2) res = -res;
    if (token.length == 'h')
      (*(short int*)address) = (short int)res;
    else if (token.length == 'l')
      (*(long int*)address) = (long int)res;
    else
      (*(int*)address) = (int)res;
  } else if (!token.no_assignment) {
    if (token.length == 'h')
      (*(unsigned short int*)address) = (unsigned short int)res;
    else if (token.length == 'l')
      (*(unsigned long int*)address) = (unsigned long int)res;
    else
      (*(unsigned int*)address) = (unsigned int)res;
  }

  if (!token.no_assignment) ++(*count);
}

void write_string(Argument token, const char* str, unsigned long* position,
                  void* address, int* count) {
  while (isspace(str[*position])) ++(*position);
  unsigned long i = 0;
  for (; (str[*position] != '\0') && !isspace(str[*position]) &&
         (token.width == 0 || (i < token.width));
       ++i) {
    if (token.no_assignment) {
      ++(*position);
    } else if (token.length == 'l') {
      ((wchar_t*)address)[i] = (wchar_t)str[(*position)++];
    } else {
      ((char*)address)[i] = (char)str[(*position)++];
    }
  }
  if (!token.no_assignment) {
    if (token.length == 'l') {
      ((wchar_t*)address)[i] = (wchar_t)'\0';
    } else {
      ((char*)address)[i] = (char)'\0';
    }
    ++(*count);
  }
}

void write_integer(Argument token, const char* str, unsigned long* position,
                   void* address, int* count) {
  while (isspace(str[*position])) ++(*position);
  int sign = 0;
  unsigned long res = 0;
  unsigned long i = 0;
  if (str[*position] == '-' || str[*position] == '+') {
    if (str[*position] == '-')
      sign = 2;
    else
      sign = 1;
    ++(*position);
    ++i;
  }
  if ((str[*position] == '0' &&
       (str[(*position) + 1] == 'x' || str[(*position) + 1] == 'X')) ||
      token.specifier == 'p') {
    res = hex_to_decimal(token, str, position, i, &sign);
  } else if (str[*position] == '0' &&
             s21_strchr("01234567", str[(*position) + 1])) {
    res = oct_to_decimal(token, str, position, i);
  } else {
    while (isdigit(str[*position]) &&
           (token.width == 0 ? true : (i < token.width))) {
      res = (res * 10) + (int)(str[(*position)++] - '0');
      ++i;
    }
  }
  if (sign && !token.no_assignment) {
    if (sign == 2) res = -res;
    if (token.length == 'h')
      (*(short int*)address) = (short int)res;
    else if (token.length == 'l')
      (*(long int*)address) = (long int)res;
    else if (token.specifier == 'p')
      (*(long long*)address) = (long long)res;
    else
      (*(int*)address) = (int)res;
  } else if (!token.no_assignment) {
    if (token.length == 'h')
      (*(unsigned short int*)address) = (unsigned short int)res;
    else if (token.length == 'l')
      (*(unsigned long int*)address) = (unsigned long int)res;
    else if (token.specifier == 'p')
      (*(long long*)address) = (long long)res;
    else
      (*(unsigned int*)address) = (unsigned int)res;
  }
  if (!token.no_assignment) ++(*count);
}

unsigned long hex_to_decimal(Argument token, const char* str,
                             unsigned long* position, unsigned long i,
                             int* sign) {
  unsigned long res = 0;
  if ((str[*position] == '0' &&
       (str[(*position) + 1] == 'x' || str[(*position) + 1] == 'X')) &&
      (token.width == 0 || (i + 1 < token.width))) {
    i += 2;
    (*position) += 2;
  }

  while (
      (isdigit(str[*position]) || s21_strchr("abcdefABCDEF", str[*position])) &&
      (token.width == 0 || (i < token.width))) {
    unsigned long res_copy = res;

    if (isdigit(str[*position])) {
      res = (res * 16) + (int)(str[(*position)++] - '0');
      ++i;
    } else if (s21_strchr("abcdefABCDEF", str[*position])) {
      if (str[*position] >= 'a' && str[*position] <= 'f')
        res = (res * 16) + (int)(str[(*position)++] - 'a' + 10);
      else if (str[*position] >= 'A' && str[*position] <= 'F')
        res = (res * 16) + (int)(str[(*position)++] - 'A' + 10);
      ++i;
    }
    if (res_copy > res) {
      res = 18446744073709551615UL;
      if (*sign == 2) (*sign) = 1;
    }
  }
  return res;
}

unsigned long oct_to_decimal(Argument token, const char* str,
                             unsigned long* position, unsigned long i) {
  unsigned long res = 0;
  if ((str[*position] == '0') && (token.width == 0 || (i + 1 < token.width))) {
    ++i;
    ++(*position);
  }
  while (s21_strchr("01234567", str[*position]) &&
         (token.width == 0 ? true : (i < token.width))) {
    res = (res * 8) + (int)(str[(*position)++] - '0');
    ++i;
  }
  return res;
}

void write_float(Argument token, const char* str, unsigned long* position,
                 void* address, int* count) {
  while (isspace(str[*position])) ++(*position);
  int sign = 0;
  unsigned long i = 0;
  if (str[*position] == '-' || str[*position] == '+') {
    if (str[*position] == '-')
      sign = 2;
    else
      sign = 1;
    ++(*position);
    ++i;
  }
  if ((token.width >= 3 || token.width == 0) && isprint(str[*position]) &&
      isprint(str[(*position) + 1]) && isprint(str[(*position) + 2]) &&
      (s21_strchr("iI", str[*position]) &&
       s21_strchr("nN", str[(*position) + 1]) &&
       s21_strchr("fF", str[(*position) + 2]))) {
    (*position) += 3;
    if (!token.no_assignment) {
      if (token.length == 'L')
        (*(long double*)address) =
            (long double)INFINITY * ((sign == 2) ? -1.0 : 1.0);
      else if (token.length == 'l')
        (*(double*)address) = (double)INFINITY * ((sign == 2) ? -1.0 : 1.0);
      else
        (*(float*)address) = (float)INFINITY * ((sign == 2) ? -1.0 : 1.0);
      ++(*count);
    }
  } else if ((token.width >= 3 || token.width == 0) &&
             (str[*position] != '\0') && (str[(*position) + 1] != '\0') &&
             (str[(*position) + 2] != '\0') &&
             (s21_strchr("nN", str[*position]) &&
              s21_strchr("aA", str[(*position) + 1]) &&
              s21_strchr("nN", str[(*position) + 2]))) {
    (*position) += 3;
    if (!token.no_assignment) {
      if (token.length == 'L')
        *((long double*)address) = (long double)nan("");
      else if (token.length == 'l')
        *((double*)address) = (double)nan("");
      else
        *((float*)address) = (float)nan("");
      ++(*count);
    }
  } else {
    write_e_num(token, str, position, address, count, sign, &i);
  }
}

void write_e_num(Argument token, const char* str, unsigned long* position,
                 void* address, int* count, int sign, unsigned long* i) {
  long long integer = 0;
  long long fraction = 0;
  long accuracy = 0;
  unsigned long check = *i;
  while (isdigit(str[*position]) &&
         ((token.width == 0) || ((*i) < token.width))) {
    integer = (integer * 10) + (int)(str[(*position)++] - '0');
    ++(*i);
  }
  if ((token.width == 0 || ((*i) < token.width)) && str[*position] == '.') {
    ++(*position);
    ++(*i);
    while (isdigit(str[*position]) &&
           ((token.width == 0) || ((*i) < token.width))) {
      fraction = (fraction * 10) + (int)(str[(*position)++] - '0');
      ++(*i);
      ++accuracy;
    }
  }
  char exp_sign = ' ';
  long long exp_power = 0;
  if ((token.width == 0 || ((*i) < token.width)) &&
      s21_strchr("eE", str[*position])) {
    ++(*position);
    ++(*i);
    if (str[*position] == '-' || str[*position] == '+') {
      exp_sign = str[(*position)++];
      ++(*i);
    }
    while (isdigit(str[*position]) &&
           ((token.width == 0) || ((*i) < token.width))) {
      exp_power = (exp_power * 10) + (int)(str[(*position)++] - '0');
      ++(*i);
    }
  }
  int error = nothing_was_read(*i, check, count);
  if (!token.no_assignment) {
    if (token.length == 'L')
      *((long double*)address) = (long double)count_float(
          integer, fraction, accuracy, exp_power, exp_sign, sign, error);
    else if (token.length == 'l')
      *((double*)address) = (double)count_float(
          integer, fraction, accuracy, exp_power, exp_sign, sign, error);
    else
      *((float*)address) = (float)count_float(integer, fraction, accuracy,
                                              exp_power, exp_sign, sign, error);
  }
}

int nothing_was_read(unsigned long i, unsigned long check, int* count) {
  int error = 1;
  if (i != check)
    ++(*count);
  else
    error = 0;
  return error;
}

long double count_float(long long integer, long long fraction, long accuracy,
                        long long exp_power, char exp_sign, int sign,
                        int error) {
  return ((long double)integer +
          ((long double)fraction / (pow(10.0, accuracy)))) *
         (pow(10.0, (long double)exp_power * (exp_sign == '-' ? -1 : 1))) *
         ((sign == 2 && error) ? -1 : 1);
}

void write_hexadecimal(Argument token, const char* str, unsigned long* position,
                       void* address, int* count) {
  while (isspace(str[*position])) ++(*position);
  int sign = 0;
  unsigned long res = 0;
  unsigned long i = 0;
  if ((str[*position] == '-' || str[*position] == '+') &&
      ((token.width == 0) || (i < token.width))) {
    if (str[*position] == '-')
      sign = 2;
    else
      sign = 1;
    ++(*position);
    ++i;
  }
  res = hex_to_decimal(token, str, position, i, &sign);
  if (sign && !token.no_assignment) {
    if (sign == 2) res = -res;
    if (token.length == 'h')
      (*(short int*)address) = (short int)res;
    else if (token.length == 'l')
      (*(long int*)address) = (long int)res;
    else
      (*(int*)address) = (int)res;
  } else if (!token.no_assignment) {
    if (token.length == 'h')
      (*(unsigned short int*)address) = (unsigned short int)res;
    else if (token.length == 'l')
      (*(unsigned long int*)address) = (unsigned long int)res;
    else
      (*(unsigned int*)address) = (unsigned int)res;
  }
  if (!token.no_assignment) ++(*count);
}

void write_octal(Argument token, const char* str, unsigned long* position,
                 void* address, int* count) {
  while (isspace(str[*position])) ++(*position);
  int sign = 0;
  unsigned long res = 0;
  unsigned long i = 0;
  if (str[*position] == '-' || str[*position] == '+') {
    if (str[*position] == '-')
      sign = 2;
    else
      sign = 1;
    ++(*position);
    ++i;
  }
  res = oct_to_decimal(token, str, position, i);
  if (sign && !token.no_assignment) {
    if (sign == 2) res = -res;
    if (token.length == 'h')
      (*(short int*)address) = (short int)res;
    else if (token.length == 'l')
      (*(long int*)address) = (long int)res;
    else
      (*(int*)address) = (int)res;
  } else if (!token.no_assignment) {
    if (token.length == 'h')
      (*(unsigned short int*)address) = (unsigned short int)res;
    else if (token.length == 'l')
      (*(unsigned long int*)address) = (unsigned long int)res;
    else
      (*(unsigned int*)address) = (unsigned int)res;
  }
  if (!token.no_assignment) ++(*count);
}

void write_number(Argument token, unsigned long* position, void* address) {
  if (!token.no_assignment) {
    if (token.length == 'h')
      (*(short int*)address) = (short int)(*position);
    else if (token.length == 'l')
      (*(long int*)address) = (long int)(*position);
    else {
      (*(int*)address) = (int)(*position);
    }
  }
}

void check_percent(const char* str, unsigned long* position, int* error) {
  while (isspace(str[*position])) ++(*position);
  if (str[(*position)++] != '%') (*error) = 0;
}

Argument argument_initialize(Argument token) {
  token.no_assignment = false;
  token.width = 0;
  token.length = ' ';
  token.specifier = ' ';
  return token;
}
