#ifndef _GDT_H
#define _GDT_H

struct gdt_descriptor 
{
	unsigned short limit;
	unsigned short baseLow;
	unsigned char baseMiddle;
	unsigned char access;
	unsigned char grand;
	unsigned char baseHigh;
}__attribute__((packed));

struct gdt_ptr 
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

void GDTInitialize();
void GDTSetDescriptor(unsigned int index, unsigned long long base, unsigned long long limit, unsigned char access, unsigned char grand);

#endif