#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1
#define FAIL_MEMORY 2
#define FAIL_NUMBER 3

#define PI 3.14159265358979323846
#define E 2.71828182845904523536


int append_string (char **, char *);
int copy_string (char **, char *);
int sprintf_string (char **, char *fmt, ... );
int truncate_string (char **, size_t);
int replace_string (char **, const char *, const char *);
int wrap_string (char **, size_t);
size_t get_string (char**, const char *);
size_t len_string(char **);
int string_to_double (const char *, double *);
int string_to_int (const char *, int *);
size_t int_to_string (char**, int);
size_t double_to_string (char**, double, int);
int sub_string(char**, size_t, size_t);
int left_string(char** str, size_t s);
int right_string(char** str, size_t s);

int csv_parse(char ***,char *, size_t *);
void cleanup_csv_strings(char **,size_t);

void pause_for_enter (const char *);

int float_less_than (double, double, double);
double get_double (const char *);
int get_int (const char *);
double deg_to_rad(double);
double rad_to_deg(double);
void array_sort_int(int *, size_t);
void array_sort_double(double *, size_t);
