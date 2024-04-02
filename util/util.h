#ifndef _UTIL_H
#define _UTIL_H

void OutPortByte(unsigned short port, unsigned char value);
char InPortByte(unsigned short port);
void OutPortWord(unsigned short port, unsigned short value);
unsigned short InPortWord(unsigned short port);

#endif