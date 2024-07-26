#include "s21_string.h"

t_parsed_printf parsed_printf_null() {
  t_parsed_printf rez = {0};
  rez.flags = calloc(1, sizeof(char));
  rez.width = -3;
  rez.accuracy = -1;
  rez.length = '\0';
  rez.spec = '\0';
  return rez;
}

t_parsed_printf parsed_printf_init(char* str) {
  if (str == S21_NULL) {
    return parsed_printf_null();
  }
  if (str[0] != '%' || is_spec(str[s21_strlen(str)]) ||
      (s21_strlen(str) == 1 && str[0] == '%')) {
    perror("parsed_printf_init: wrong input:");
  }
  int i = 1;
  t_parsed_printf rez = parsed_printf_null();
  int iflags = 0;
  while (is_flag(str[i])) {
    iflags++;
    rez.flags = realloc(rez.flags, sizeof(char) * (iflags + 1));
    rez.flags[iflags - 1] = str[i];
    i++;
  }
  rez.flags[iflags] = '\0';

  rez.width = -1;
  cut_to_parse(str, &i, &(rez.width));

  rez.accuracy = -1;
  if (str[i] == '.') {
    i++;
    cut_to_parse(str, &i, &(rez.accuracy));
    if (rez.accuracy == -1) rez.accuracy = 0;
  }

  if (is_length(str[i])) {
    rez.length = str[i];
    i++;
  } else
    rez.length = '\0';

  if (is_spec(str[i])) {
    rez.spec = str[i];
  } else
    rez.spec = '\0';
  return rez;
}

void cut_to_parse(char* str, int* i, int* to) {
  if (str[*i] != '*') {
    int start = *i;
    while (is_decimal(str[*i])) {
      (*i)++;
    }
    if ((*i) != start) {
      char* dec = cut_str(str, start, (*i));
      (*to) = str_to_int(dec, s21_strlen(dec) - 1);
      free(dec);
    }
  } else {
    (*to) = -2;
    (*i)++;
  }
}

char* cut_str(const char* format, int start, int end) {
  if (start < 0 || (s21_size_t)end >= s21_strlen(format)) {
    perror("cut_str: bad end or start");
    return S21_NULL;
  }
  int length = end - start + 1;
  char* cpy = calloc(length + 5, sizeof(char));
  for (int i = 0; i < length; i++) {
    cpy[i] = format[i + start];
  }
  cpy[length] = '\0';
  return cpy;
}

t_cut_of_rez* parse_format_parts(const char* format, int* n) {
  t_cut_of_rez* rez = calloc(1, sizeof(t_cut_of_rez));
  s21_size_t leftp = 0;
  int badformat = 0;
  char* str;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    if (format[i] == '%') {
      str = S21_NULL;
      int startf = i;
      if (i > 0) {
        str = cut_str(format, leftp, i - 1);
      }
      i++;
      while (!is_spec(format[i])) {
        if (i == s21_strlen(format) - 1) {
          badformat = 1;
          break;
        }
        i++;
      }
      if (i != s21_strlen(format)) leftp = i + 1;
      t_parsed_printf parsed = {0};
      if (!badformat) {
        char* cuted = cut_str(format, startf, i);
        parsed = parsed_printf_init(cuted);
        free(cuted);
      }
      (*n)++;
      rez = realloc(rez, (*n) * sizeof(t_cut_of_rez));
      rez[(*n) - 1].format = parsed;
      if (!str) {
        str = calloc(1, sizeof(char));
        str[0] = '\0';
      }
      rez[(*n) - 1].str = str;
    }
    if (leftp != s21_strlen(format) &&
        i == s21_strlen(format) -
                 1) {  // если в формате последними является прсто букавы(не
                       // форматируемое значение)
      str = cut_str(format, leftp, i);
      (*n)++;
      rez = realloc(rez, (*n) * sizeof(t_cut_of_rez));
      rez[(*n) - 1].str = str;
      rez[(*n) - 1].format = parsed_printf_null();
    }
  }
  return rez;
}

void parse_s(va_list* args, char** rez, int accuracy, char* flag, int width) {
  char* s = va_arg(*args, char*);
  if (s) {
    *rez = calloc(s21_strlen(s) + 5, sizeof(char));
    s21_strcpy(*rez, s);
    (*rez)[s21_strlen(s)] = '\0';
    parse_accuracy_str(rez, accuracy);
    parse_width_str(rez, flag, width);
  }
}

void parse_c(va_list* args, char** rez, int* index, char* flag, int width) {
  char c = va_arg(*args, int);
  *rez = calloc(2, sizeof(char));
  (*rez)[0] = c;
  (*rez)[1] = '\0';
  if (c == 0) (*index)++;
  parse_width_str(rez, flag, width);
}

void parse_d(va_list* args, char** rez, char len, char* flag, int width,
             int accuracy) {
  int long d = 0;
  if (len == 'l') {
    d = va_arg(*args, long int);
  } else {
    d = va_arg(*args, int);
  }
  if (len == 'h') {
    short int shortd = d;
    d = shortd;
  }
  char* drez = int_to_str(d);

  parse_width(&drez, flag, width);
  parse_accuracy_decimal(&drez, accuracy);

  if (is_in_arr(flag, '+')) parse_plus(&drez);

  if (is_in_arr(flag, ' ')) parse_space(&drez);
  *rez = drez;
}

void parse_f(va_list* args, char** rez, char* flag, int width, int* accuracy) {
  double f = 0;
  f = va_arg(*args, double);
  if (*accuracy == -1) *accuracy = 6;
  char* frez = float_to_str(f, *accuracy);
  if (is_in_arr(flag, '+')) parse_plus(&frez);
  if (is_in_arr(flag, ' ')) parse_space(&frez);
  parse_width(&frez, flag, width);
  *rez = frez;
}

void parse_u(va_list* args, char** rez, char len, char* flag, int width,
             int accuracy) {
  unsigned long int u = 0;
  if (len == 'l')
    u = va_arg(*args, unsigned long int);
  else
    u = va_arg(*args, unsigned int);

  if (len == 'h') {
    short unsigned int shortu = u;
    u = shortu;
  }
  char* urez = unsigned_int_to_str(u);
  parse_accuracy_unsigned_decimal(&urez, accuracy);
  *rez = urez;
  if (is_in_arr(flag, ' ')) width++;
  parse_width(rez, flag, width);
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int n = 0;
  t_cut_of_rez* parsed = parse_format_parts(format, &n);
  int i = 0;
  int index = 0;
  for (; i < n; i++) {
    put_str_to_end(str, parsed[i].str, &index);
    int width = parsed[i].format.width;
    char spec = parsed[i].format.spec;
    int accuracy = parsed[i].format.accuracy;
    char* flag = parsed[i].format.flags;
    char len = parsed[i].format.length;
    if (width == STAR) width = va_arg(args, int);
    if (accuracy == STAR) accuracy = va_arg(args, int);
    char* rez = S21_NULL;
    switch (spec) {
      case 's':
        parse_s(&args, &rez, accuracy, flag, width);
        break;
      case 'c':
        parse_c(&args, &rez, &index, flag, width);
        break;
      case 'd':
        parse_d(&args, &rez, len, flag, width, accuracy);
        break;
      case 'f':
        parse_f(&args, &rez, flag, width, &accuracy);
        break;
      case 'u':
        parse_u(&args, &rez, len, flag, width, accuracy);
        break;
      case '%':
        rez = calloc(2, sizeof(char));
        rez[0] = '%';
        rez[1] = '\0';
        break;
    }
    put_str_to_end(str, rez, &index);
    free(rez);
  }
  free_cut_of_rez(parsed, n);
  va_end(args);
  return index;
}

void parse_accuracy_str(char** str, int accuracy) {
  if ((s21_size_t)accuracy < s21_strlen(*str) && accuracy > -1) {
    (*str)[accuracy] = '\0';
  }
}

char* unsigned_int_to_str(long unsigned int inp) {
  if (inp == 0) {
    char* rez = calloc(2, sizeof(char));
    rez[0] = '0';
    rez[1] = '\0';
    return rez;
  }
  long unsigned int del = 1;
  int i = 0;
  while (inp / del != 0) {
    i++;
    del *= 10;
  }
  del /= 10;
  int mul = 10;
  char* rez = calloc((i + 1), sizeof(char));
  for (int j = 0; j < i; j++) {
    long unsigned int tmp = inp / del % mul;
    del /= 10;
    rez[j] = fabs((double)tmp) + 48;
  }
  rez[i] = '\0';
  return rez;
}

void parse_accuracy_unsigned_decimal(char** val, int accuracy) {
  if (accuracy == -1) return;
  if (accuracy == 0 && (*val)[0] == '0') (*val)[0] = '\0';
  if (s21_strlen(*val) < (s21_size_t)accuracy) {
    int len = accuracy - (s21_strlen(*val));
    int size = len + s21_strlen(*val) + 1;

    char* cp = calloc(s21_strlen(*val) + 1, sizeof(char));
    s21_strcpy(cp, *val);

    *val = realloc(*val, size);

    for (int i = len; i < size - 1; i++) {
      (*val)[i] = cp[i - len];
    }

    for (int i = 0; i < len; i++) (*val)[i] = '0';

    (*val)[size - 1] = '\0';

    free(cp);
  }
}

void parse_accuracy_decimal(char** val, long int accuracy) {
  if (accuracy == -1) return;

  int sign = 0;
  if ((*val)[0] == '+' || (*val)[0] == '-') sign = 1;

  if (accuracy == 0 && (*val)[sign] == '0') (*val)[sign] = '\0';
  if (s21_strlen(*val) < (s21_size_t)accuracy) {
    int len = accuracy - (s21_strlen(*val) - sign);
    int size = len + s21_strlen(*val) + 1;

    char* cp = calloc(s21_strlen(*val) + 1, sizeof(char));
    s21_strcpy(cp, *val);

    *val = realloc(*val, size);

    for (int i = len + sign; i < size - 1; i++) {
      (*val)[i] = cp[i - len];
    }

    for (int i = sign; i < len + sign; i++) (*val)[i] = '0';

    (*val)[size - 1] = '\0';

    free(cp);
  }
}
void parse_space(char** str) {
  if (!((*str)[0] == '+' || (*str)[0] == '-')) {
    int sn = s21_strlen(*str);
    char* cp = calloc(sn, sizeof(char));
    *str = realloc(*str, sn + 2);
    for (int i = 0; i < sn; i++) {
      cp[i] = (*str)[i];
    }
    for (int i = 0; i < sn; i++) {
      (*str)[i + 1] = cp[i];
    }
    free(cp);
    (*str)[0] = ' ';
    (*str)[sn + 1] = '\0';
  }
}

void parse_width(char** str, char* flags, int width) {
  if (is_in_arr(flags, ' ')) width--;
  int spaces = width - s21_strlen(*str);
  int len = spaces + s21_strlen(*str);
  char symb = ' ';

  if (is_in_arr(flags, '0')) symb = '0';
  if (width != -1 && spaces > 0) {
    *str = realloc(*str, len + 1);
    if (is_in_arr(flags, '-')) {
      for (int i = s21_strlen(*str); i < len; i++) {
        (*str)[i] = ' ';
      }
    } else {
      int plus = 0;
      char* cp = calloc(s21_strlen(*str), sizeof(char));
      if (((*str)[0] == '+' || (*str)[0] == '-') && symb == '0') plus++;
      for (s21_size_t i = plus; i < s21_strlen(*str); i++) {
        cp[i] = (*str)[i];
      }
      int sn = s21_strlen(*str);
      for (int i = plus; i < sn; i++) {
        (*str)[i + spaces] = cp[i];
      }

      for (int i = plus; i < spaces + plus; i++) {
        (*str)[i] = symb;
      }
      free(cp);
    }
    (*str)[len] = '\0';
  }
}

void parse_width_str(char** str, char* flags, int width) {
  int spaces = width - (int)s21_strlen(*str);
  int len = spaces + (int)s21_strlen(*str);
  if (width != -1 && spaces > 0) {
    *str = realloc(*str, len * 2);
    if (is_in_arr(flags, '-')) {
      for (int i = s21_strlen(*str); i < len; i++) {
        (*str)[i] = ' ';
      }
    } else {
      char* cp = calloc(s21_strlen(*str), sizeof(char));
      for (s21_size_t i = 0; i < s21_strlen(*str); i++) {
        cp[i] = (*str)[i];
      }
      int sn = s21_strlen(*str);
      for (int i = 0; i < sn; i++) {
        (*str)[i + spaces] = cp[i];
      }
      for (int i = 0; i < spaces; i++) {
        (*str)[i] = ' ';
      }
      free(cp);
    }
    (*str)[len] = '\0';
  }
}

int is_in_arr(char* str, char ch) {
  int rez = 0;
  if (s21_strlen(str) > 0) {
    for (int i = 0; (s21_size_t)i < s21_strlen(str); i++) {
      if (str[i] == ch) {
        rez = 1;
      }
    }
  }
  return rez;
}

void parse_plus(char** str) {
  if ((*str)[0] != '-') {
    int size = s21_strlen(*str) + 2;  //\0 + 1
    *str = realloc(*str, size * 2);
    for (int i = s21_strlen(*str); i > 0; i--) {
      (*str)[i] = (*str)[i - 1];
    }
    (*str)[0] = '+';
    (*str)[size - 1] = '\0';
  }
}

void put_str_by_index(char* dest, char* str, int index) {
  if (str[0] == 0) dest[index] = str[0];
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    dest[i + index] = str[i];
  }
}

void put_str_to_end(char* dest, char* str, int* index) {
  if (str != S21_NULL) {
    put_str_by_index(dest, str, *index);
    (*index) += s21_strlen(str);  //-1?
    dest[*index] = '\0';
  }
}

void free_cut_of_rez(t_cut_of_rez* cut, int n) {
  for (int i = 0; i < n; i++) {
    free(cut[i].format.flags);
    free(cut[i].str);
  }
  free(cut);
}

int is_something(char* str, char ch) {
  int rez = 0;
  for (s21_size_t i = 0; i < s21_strlen(str); i++)
    if (ch == str[i]) rez = 1;
  return rez;
}

int is_spec(char ch) {
  char* specs = "cdieEfgGosuxXpn%";
  return is_something(specs, ch);
}

int is_flag(char ch) {
  char* flags = "-+ #0";
  return is_something(flags, ch);
}

int is_decimal(char ch) { return (ch >= '0' && ch <= '9'); }

int is_length(char ch) {
  char* lengths = "hlL";
  return is_something(lengths, ch);
}

int ch_to_int(char ch) {
  if (!is_decimal(ch)) {
    perror("ch_to_int: wrong input");
    return 0;
  }
  return ch - 48;
}

int str_to_int(char* str, int len) {
  int rez = 0;
  int mul = 1;
  for (int i = len - 1; i >= 0; i--) {
    if (!is_decimal(str[i]) && (str[i] != '-' && i == 0)) {
      perror("str_to_int: wrong input");
      return 0;
    }
    if (str[i] != '-') {
      rez += mul * ch_to_int(str[i]);
      mul *= 10;
    } else
      rez *= -1;
  }
  return rez;
}

char* int_to_str(long int inp) {
  if (inp == 0) {
    char* rez = calloc(2, sizeof(char));
    rez[0] = '0';
    rez[1] = '\0';
    return rez;
  }
  long int del = 1;
  int i = 0;
  while ((inp / (long int)pow(10, del)) != 0) {
    i++;
    del++;
  }
  del--;
  int mul = 10;
  int minus = 0;
  if (inp < 0) minus = 1;
  char* rez = calloc(i + 2 + minus, sizeof(char));
  if (inp < 0) rez[0] = '-';

  for (int j = minus; j < i + minus + 1; j++) {
    long int tmp = inp / (long int)(pow(10, del)) % mul;
    del--;
    rez[j] = (char)((int)fabs((double)tmp) + 48);
  }
  rez[i + minus + 1] = '\0';
  return rez;
}

char* float_to_str(double inp, int size) {
  long long int del = 1;
  long long int tm = (long long int)inp;
  int i = 0;
  int j = 0;
  int f = 0;
  while (tm / del != 0) {
    i++;
    del *= 10;
  }
  del /= 10;
  int mul = 10;
  char* res = calloc(i + size + 3, sizeof(char));
  if (inp < 0) {
    res[0] = '-';
    f = 1;
    tm = -tm;
    inp = -inp;
  }
  for (j = 0 + f; j < i + f; j++) {
    int tmp = tm / del % mul;
    del /= 10;
    res[j] = tmp + 48;
  }
  if (i == 0) {
    res[i + f] = 48;
    i++;
    j++;
  }
  if (size != 0) res[i + f] = '.';
  j++;
  tm = inp;
  inp = inp - tm;
  for (int n = j; n <= j + size; n++) {
    inp *= 10;
    int tmp = inp;
    inp = inp - tmp;
    res[n] = tmp + '0';
  }
  if (res[j + size] >= 53) {
    res[j + size - 1] = res[j + size - 1] + 1;
    for (int n = j + size - 1; n > j; n--) {
      if (res[n] > 57) res[n - 1] = res[n - 1] + 1;
      if (res[n] == 58) res[n] -= 10;
    }
  }

  res[j + size] = '\0';
  return res;
}
