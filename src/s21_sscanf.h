#ifndef S21_SSCANF
#define S21_SSCANF

#include <ctype.h>

typedef struct {
  bool no_assignment;
  unsigned long width;
  char length;
  char specifier;
} Argument;

Argument argument_initialize(Argument token);

int s21_sscanf(const char* str, const char* format, ...);
int parse_format(const char* format, const char* str, Argument* token,
                 unsigned long* i, unsigned long* j);
int get_width(const char* format, unsigned long position, Argument* token);
bool check_token(Argument token);
void write_argument(Argument token, const char* str, unsigned long* position,
                    void* address, int* count, int* error);

void write_char(Argument token, const char* str, unsigned long* position,
                void* address, int* count);
void write_string(Argument token, const char* str, unsigned long* position,
                  void* address, int* count);
void write_digit(Argument token, const char* str, unsigned long* position,
                 void* address, int* count);
void write_integer(Argument token, const char* str, unsigned long* position,
                   void* address, int* count);
void write_float(Argument token, const char* str, unsigned long* position,
                 void* address, int* count);
void write_e_num(Argument token, const char* str, unsigned long* position,
                 void* address, int* count, int sign, unsigned long* i);
void write_hexadecimal(Argument token, const char* str, unsigned long* position,
                       void* address, int* count);
void write_octal(Argument token, const char* str, unsigned long* position,
                 void* address, int* count);
void write_number(Argument token, unsigned long* position, void* address);
void check_percent(const char* str, unsigned long* position, int* error);

long double count_float(long long integer, long long fraction, long accuracy,
                        long long exp_power, char exp_sign, int sign,
                        int error);
unsigned long hex_to_decimal(Argument token, const char* str,
                             unsigned long* position, unsigned long, int* sign);
unsigned long oct_to_decimal(Argument token, const char* str,
                             unsigned long* position, unsigned long i);

int nothing_was_read(unsigned long i, unsigned long check, int* count);

#endif  //  S21_SSCANF
