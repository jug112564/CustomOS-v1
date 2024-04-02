#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "idt.h"
#include "../util/console.h"
#include "../util/util.h"

void IsrHandler(struct InterruptRegisters* regs);
void IrqInstallHandler(int irq, void (*handler)(struct InterruptRegisters *r));
void IrqHandler(struct InterruptRegisters* regs);
#endif