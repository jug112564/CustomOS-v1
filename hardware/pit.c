#include "pit.h"

unsigned int tick;

void PITInitialize()
{
    IrqInstallHandler(0,&HandlePIT);
	tick=0;
}

void StartPITCounter(unsigned int freq) 
{
    //119318.16666 Mhz
    unsigned int divisor = 1193180/freq;

    //0011 0110   
    OutPortByte(0x43,0x36);
    OutPortByte(0x40,(unsigned char)(divisor & 0xFF));
    OutPortByte(0x40,(unsigned char)((divisor >> 8) & 0xFF));

	tick = 0;

}

void HandlePIT(struct InterruptRegisters *regs)
{    
	tick++;
	//ConsolePrint("Timer ticked. %d \n", tick);
}

unsigned int GetTickCount()
{	
	return tick;
}