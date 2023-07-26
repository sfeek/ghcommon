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
int truncate_string (char **, int);
int replace_string (char **, const char *, const char *);
int wrap_string (char **, int);
int get_string (char**, const char *);
int len_string(char **);
int string_todouble (const char *, double *);
int string_toint (const char *, int *);

int csv_parse(char ***,char *, int *);
void cleanup_csv_strings(char **,int);

void pause_for_enter (const char *);

int float_less_than (double, double, double);
double get_double (const char *);
int get_int (const char *);
double deg_to_rad(double);
double rad_to_deg(double);
void array_sort_int(int *, int);
void array_sort_double(double *, int);
