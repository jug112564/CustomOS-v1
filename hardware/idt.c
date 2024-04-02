#include "idt.h"

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void InstallIDT(unsigned int);

void IDTInitialize()
{
    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (unsigned int) &idt_entries[0];

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    InstallInterruptHandler(0, (unsigned int)isr0,0x08, 0x8E);
    InstallInterruptHandler(1, (unsigned int)isr1,0x08, 0x8E);
    InstallInterruptHandler(2, (unsigned int)isr2,0x08, 0x8E);
    InstallInterruptHandler(3, (unsigned int)isr3,0x08, 0x8E);
    InstallInterruptHandler(4, (unsigned int)isr4, 0x08, 0x8E);
    InstallInterruptHandler(5, (unsigned int)isr5, 0x08, 0x8E);
    InstallInterruptHandler(6, (unsigned int)isr6, 0x08, 0x8E);
    InstallInterruptHandler(7, (unsigned int)isr7, 0x08, 0x8E);
    InstallInterruptHandler(8, (unsigned int)isr8, 0x08, 0x8E);
    InstallInterruptHandler(9, (unsigned int)isr9, 0x08, 0x8E);
    InstallInterruptHandler(10, (unsigned int)isr10, 0x08, 0x8E);
    InstallInterruptHandler(11, (unsigned int)isr11, 0x08, 0x8E);
    InstallInterruptHandler(12, (unsigned int)isr12, 0x08, 0x8E);
    InstallInterruptHandler(13, (unsigned int)isr13, 0x08, 0x8E);
    InstallInterruptHandler(14, (unsigned int)isr14, 0x08, 0x8E);
    InstallInterruptHandler(15, (unsigned int)isr15, 0x08, 0x8E);
    InstallInterruptHandler(16, (unsigned int)isr16, 0x08, 0x8E);
    InstallInterruptHandler(17, (unsigned int)isr17, 0x08, 0x8E);
    InstallInterruptHandler(18, (unsigned int)isr18, 0x08, 0x8E);
    InstallInterruptHandler(19, (unsigned int)isr19, 0x08, 0x8E);
    InstallInterruptHandler(20, (unsigned int)isr20, 0x08, 0x8E);
    InstallInterruptHandler(21, (unsigned int)isr21, 0x08, 0x8E);
    InstallInterruptHandler(22, (unsigned int)isr22, 0x08, 0x8E);
    InstallInterruptHandler(23, (unsigned int)isr23, 0x08, 0x8E);
    InstallInterruptHandler(24, (unsigned int)isr24, 0x08, 0x8E);
    InstallInterruptHandler(25, (unsigned int)isr25, 0x08, 0x8E);
    InstallInterruptHandler(26, (unsigned int)isr26, 0x08, 0x8E);
    InstallInterruptHandler(27, (unsigned int)isr27, 0x08, 0x8E);
    InstallInterruptHandler(28, (unsigned int)isr28, 0x08, 0x8E);
    InstallInterruptHandler(29, (unsigned int)isr29, 0x08, 0x8E);
    InstallInterruptHandler(30, (unsigned int)isr30, 0x08, 0x8E);
    InstallInterruptHandler(31, (unsigned int)isr31, 0x08, 0x8E);

    InstallInterruptHandler(32, (unsigned int)irq0, 0x08, 0x8E);
    InstallInterruptHandler(33, (unsigned int)irq1, 0x08, 0x8E);
    InstallInterruptHandler(34, (unsigned int)irq2, 0x08, 0x8E);
    InstallInterruptHandler(35, (unsigned int)irq3, 0x08, 0x8E);
    InstallInterruptHandler(36, (unsigned int)irq4, 0x08, 0x8E);
    InstallInterruptHandler(37, (unsigned int)irq5, 0x08, 0x8E);
    InstallInterruptHandler(38, (unsigned int)irq6, 0x08, 0x8E);
    InstallInterruptHandler(39, (unsigned int)irq7, 0x08, 0x8E);
    InstallInterruptHandler(40, (unsigned int)irq8, 0x08, 0x8E);
    InstallInterruptHandler(41, (unsigned int)irq9, 0x08, 0x8E);
    InstallInterruptHandler(42, (unsigned int)irq10, 0x08, 0x8E);
    InstallInterruptHandler(43, (unsigned int)irq11, 0x08, 0x8E);
    InstallInterruptHandler(44, (unsigned int)irq12, 0x08, 0x8E);
    InstallInterruptHandler(45, (unsigned int)irq13, 0x08, 0x8E);
    InstallInterruptHandler(46, (unsigned int)irq14, 0x08, 0x8E);
    InstallInterruptHandler(47, (unsigned int)irq15, 0x08, 0x8E);


    InstallInterruptHandler(128, (unsigned int)isr128, 0x08, 0x8E); //System calls
    InstallInterruptHandler(177, (unsigned int)isr177, 0x08, 0x8E); //System calls

    InstallIDT((unsigned int)&idt_ptr);

}

void InstallInterruptHandler(unsigned int index, unsigned int base, unsigned short sel, unsigned char flags)
{
    idt_entries[index].base_low = base & 0xFFFF;
    idt_entries[index].base_high = (base >> 16) & 0xFFFF;
    idt_entries[index].sel = sel;
    idt_entries[index].always0 = 0;
    idt_entries[index].flags = flags | 0x60;
}
