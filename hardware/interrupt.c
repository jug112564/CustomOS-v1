#include "interrupt.h"

char* exceptionMessages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void IsrHandler(struct InterruptRegisters* regs)
{
    if (regs->int_no < 32)
    {
        ConsolePrint("\n");
        ConsolePrint("------------------------------------\n");
        ConsolePrint("--------------OS Error--------------\n");
        ConsolePrint("------------------------------------\n");
        ConsolePrint("Error number : %d\n",regs->int_no);
	    ConsolePrint("Error cause : %s\n",exceptionMessages[regs->int_no]);
        ConsolePrint("system halted.\n");
        for (;;);
    }
}

void *irqRoutines[16] = 
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void IrqInstallHandler (int irq, void (*handler)(struct InterruptRegisters *r))
{
    irqRoutines[irq] = handler;
}


void IrqHandler(struct InterruptRegisters* regs)
{
    void (*handler)(struct InterruptRegisters *regs);

    handler = irqRoutines[regs->int_no - 32];

    if (handler){
        handler(regs);
    }

    if (regs->int_no >= 40){
        OutPortByte(0xA0, 0x20);
    }

    OutPortByte(0x20,0x20);
}