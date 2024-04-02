#include "pic.h"

void PICInitialize() 
{
	unsigned char icw = 0;

	icw = (icw & ~0x10) | 0x10;
	icw = (icw & ~0x1) | 1;

	SendCommandToPIC(icw, 0);
	SendCommandToPIC(icw, 1);

	SendDataToPIC(0x20, 0);
	SendDataToPIC(0x28, 1);
	
	SendDataToPIC(0x04, 0);
	SendDataToPIC(0x02, 1);

	icw = (icw & ~0x1) | 1;

	SendDataToPIC(icw, 0);
	SendDataToPIC(icw, 1);
}

void SendCommandToPIC(unsigned char cmd, unsigned char picNum) 
{
	if (picNum > 1)
		return;

	unsigned char reg = (picNum==1) ? 0xA0 : 0x20;
	OutPortByte(reg, cmd);
}


void SendDataToPIC(unsigned char data, unsigned char picNum) 
{
	if (picNum > 1)
		return;

	unsigned char reg = (picNum==1) ? 0xA1 : 0x21;
	OutPortByte(reg, data);
}