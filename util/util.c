#include "util.h"

void OutPortByte(unsigned short port, unsigned char value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

char InPortByte(unsigned short port)
{
    char rv;
    asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
    return rv;
}

void OutPortWord(unsigned short port, unsigned short value)
{
    asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

unsigned short InPortWord(unsigned short port)
{
    unsigned short rv;
    asm volatile("inw %1, %0": "=a"(rv):"dN"(port));
    return rv;
}
