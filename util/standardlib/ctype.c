#include "ctype.h"

int	toupper(int c) 
{
	if (c >= 97 && c <= 122)
		 return c-32;
	else
        return c;
}

int isalpha(int c) 
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}