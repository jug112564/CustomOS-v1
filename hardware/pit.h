#ifndef _PIT_H
#define _PIT_H

#include "interrupt.h"
#include "../util/console.h"

void PITInitialize();
void StartPITCounter(unsigned int freq);
void HandlePIT(struct InterruptRegisters *regs);
unsigned int GetTickCount();

#endif