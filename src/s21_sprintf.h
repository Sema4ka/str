#ifndef S21_SPRINTF
#define S21_SPRINTF

typedef struct {
  char spec;
  char* flags;
  int width;
  int accuracy;
  char length;
} t_parsed_printf;

typedef struct {
  char* str;
  t_parsed_printf format;
} t_cut_of_rez;

char* cut_format(const char*, int, int);
int is_spec(char);
t_parsed_printf parsed_printf_init(char*);
t_parsed_printf parsed_printf_null();
int str_to_int(char*, int);
int ch_to_int(char);
int is_flag(char);
int is_decimal(char);
int is_length(char);
char* cut_str(const char*, int, int);
void cut_to_parse(char*, int*, int*);
void free_cut_of_rez(t_cut_of_rez*, int);
void put_str_by_index(char*, char*, int);
void put_str_to_end(char*, char*, int*);
char* float_to_str(double, int);
int is_in_arr(char*, char);
void parse_plus(char**);
void parse_width(char**, char*, int);
void parse_width_str(char**, char*, int);
void parse_space(char**);
void parse_accuracy_str(char**, int);
void parse_accuracy_decimal(char**, long int);
char* unsigned_int_to_str(long unsigned int);
void parse_accuracy_unsigned_decimal(char**, int);
t_cut_of_rez* parse_format_parts(const char*, int*);
void parse_s(va_list*, char**, int, char*, int);
void parse_c(va_list*, char**, int*, char*, int);
void parse_f(va_list*, char**, char*, int, int*);
void parse_u(va_list*, char**, char, char*, int, int);
void parse_d(va_list*, char**, char, char*, int, int);

#endif  // S21_SPRINTF