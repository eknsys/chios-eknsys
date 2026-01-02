#ifndef UTIL_H
#define UTIL_H

int strlen(const char *s);
int strcmp(const char *a, const char *b);
int str_contains(const char *str, const char *substr);
int str_starts_with(const char *str, const char *prefix);
int str_ends_with(const char *str, const char *suffix);
void str_split_at(const char *str, char delimiter, char *left, char *right);

void *memset(void *ptr, int value, int num);
void *memcpy(void *dest, const void *src, int num);

void str_concat(char *dest, const char *a, const char *b);
void str_concat3(char *dest, const char *a, const char *b, const char *c);

#include <stdint.h>

uint8_t to_uint8_t(const char *str);


#endif

