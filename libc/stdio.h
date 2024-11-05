#ifndef __STDIO_H__
#define __STDIO_H__ 1

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#define INFINITY -1
#define DBL_MAX 0.0
#define DBL_MIN 0.0

#define ERANGE 1

#define CLOCKS_PER_SEC 10

double strtod(const char *s, char **end);
long long strtoll(const char *nptr, char **endptr, int base);

int isspace(int c);

void *realloc(void *p, size_t n);
void free(void *p);

void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memcpy(void *s1, const void *s2, unsigned long n);
int memcmp(const void *s1, const void *s2, size_t n);

int printf(const char *fmt, ...);
int sprintf(char *s, const char *fmt, ...);
int vsprintf(char *s, const char *format, va_list *arg);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);

int clock();

double fmax(double x, double y);
double fmin(double x, double y);
float trunc(float x);
int isnan(double x);
int isinf(double x);
double modf(double x, double *iptr);
double atan2(double x, double y);
double pow(double x, double y);
double fmod(double x, double y);
double exp(double x);
double log(double x);
double log2(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double sin(double x);
double cos(double x);
double tan(double x);
double sqrt(double x);
double ceil(double x);
double floor(double x);
double abs(double x);
double fabs(double x);
double round(double x);
double cbrt(double x);

extern int errno;

#endif
