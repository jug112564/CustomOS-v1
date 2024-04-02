#include "gdt.h"

extern void InstallGDT(unsigned int);

struct gdt_descriptor gdt[6];
struct gdt_ptr pGdt;

void GDTInitialize()
{
	pGdt.limit = (sizeof(struct gdt_descriptor) * 6) - 1;
	pGdt.base = (unsigned int)&gdt[0];

    //null
	GDTSetDescriptor(0, 0, 0, 0, 0);

    //kernel code
	GDTSetDescriptor(1, 0, 0xffffffff,
		0x0002 | 0x0008 | 0x0010 | 0x0080, 
		0x80 | 0x40 | 0x0f);
    
    //kernel data
	GDTSetDescriptor(2, 0, 0xffffffff,
		0x0002 | 0x0010 | 0x0080,
		0x80 | 0x40 | 0x0f);

    //user code
	GDTSetDescriptor(3, 0, 0xffffffff,
		0x0002 | 0x0008 | 0x0010 | 0x0080 | 0x0060, 
		0x80 | 0x40 | 0x0f);

    //user data
	GDTSetDescriptor(4, 0, 0xffffffff, 
		0x0002 | 0x0010 | 0x0080 | 0x0060,
		0x80 | 0x40 | 0x0f);

	InstallGDT((unsigned int)&pGdt);
}

void GDTSetDescriptor(unsigned int index, unsigned long long base, unsigned long long limit, unsigned char access, unsigned char grand)
{
	gdt[index].baseLow = (base & 0xffff);
	gdt[index].baseMiddle = ((base >> 16) & 0xff);
	gdt[index].baseHigh = ((base >> 24) & 0xff);
	gdt[index].limit = (limit & 0xffff);

	gdt[index].access = access;
	gdt[index].grand = ((limit >> 16) & 0x0f);
	gdt[index].grand |= grand & 0xf0;
}