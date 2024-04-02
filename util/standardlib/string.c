#include "string.h"

void memset(void* dest, char val, unsigned int count)
{
    char* temp = (char*) dest;
    while(count != 0)
    {
        *temp++ = val;
        count--;
    }
}

void *memcpy(void *dest, const void *src, unsigned int count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}

unsigned int strlen (const char* str)
{
	unsigned int len=0;
	while (str[len])
	{
		len++;
	}
	return len;
}

char *strcpy(char *s1, const char *s2)
{
    char *s1_p = s1;
    while (*s1++ = *s2++);
    return s1_p;
}

char *strncpy(char *string1, const char *string2, unsigned int count)
{
	char *p = string1;
	while (count)
	{
		*p = *string2;
		if (*string2)
		{
			string2++;
		}
		p++;
		count--;
	}
	return(string1);
}

const char *strrchr(const char * String, char const Character)
{
	unsigned int Len = strlen(String), i;
	for (i = Len; i>0; i--)
		if (String[i] == Character)
			return &String[i];
	return 0;
}

int strnicmp(const char * String1, const char * String2, unsigned int Len)
{
	unsigned int i;
	for (i = 0; i<Len; i++)
		if (toupper(String1[i]) != toupper(String2[i]))
			return String1[i] - String2[i];
	return 0;
}

char tbuf[32];
char bchars[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

void itoa_s(unsigned int i, unsigned base, char* buf) 
{
	if (base > 16) return;

	if (i < 0) {
		*buf++ = '-';
		i *= -1;
	}

	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}


	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top = pos--;
	for (opos = 0; opos < top; pos--, opos++) {
		buf[opos] = tbuf[pos];
	}
	buf[opos] = 0;
}

int strcmp (const char* str1, const char* str2) 
{
	int res=0;
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		++str1, ++str2;

	if (res < 0)
		res = -1;
	if (res > 0)
		res = 1;

	return res;
}

char* strchr(const char* str, int character) 
{
	do {
		if ( *str == character )
			return (char*)str;
	}
	while (*str++);

	return 0;
}

char *strcat(char *dest, const char *src)
{
	unsigned int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];

	dest[i + j] = '\0';

	return dest;
}

int memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned char u1, u2;
	unsigned char* _s1 = (unsigned char*)s1;
	unsigned char* _s2 = (unsigned char*)s2;

	for (; n--; _s1++, _s2++) {
		u1 = *_s1;
		u2 = *_s2;
		if (u1 != u2) {
			return (u1 - u2);
		}
	}
	return 0;
}