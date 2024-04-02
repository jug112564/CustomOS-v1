#include "util/console.h"
#include "hardware/gdt.h"
#include "hardware/idt.h"
#include "hardware/interrupt.h"
#include "hardware/pic.h"
#include "hardware/pit.h"
#include "hardware/keyboard.h"

#include "multiboot.h"

void kmain(unsigned long magic, unsigned long addr);
void InitHardware();
void InitMemory(multiboot_info* pBootInfo);

void MiniConsole();
void GetInput(char* buffer, int size);