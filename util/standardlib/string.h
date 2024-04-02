#ifndef _STRING_H
#define _STRING_H

#include "ctype.h"

void memset(void* dest, char val, unsigned int count);
void *memcpy(void *dest, const void *src, unsigned int count);
unsigned int strlen (const char* str);
char *strcpy(char *s1, const char *s2);
char *strncpy(char *string1, const char *string2, unsigned int count);
const char *strrchr(const char * String, char const Character);
int strnicmp(const char * String1, const char * String2, unsigned int Len);
void itoa_s(unsigned int i, unsigned base, char* buf);
int strcmp (const char* str1, const char* str2);
char* strchr(const char* str, int character);
char *strcat(char *dest, const char *src);
int memcmp(const void *s1, const void *s2, unsigned int n);

#endif