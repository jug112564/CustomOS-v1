#include "main.h"

void kmain(unsigned long magic, unsigned long addr)
{
	multiboot_info* pBootInfo = (multiboot_info*)addr;

	ConsoleInitialize();

	ConsolePrint("Boot Loader Name : %s\n", pBootInfo->boot_loader_name);

	InitHardware();

	InstallKeyboard();
	ConsolePrint("install keyboard\n");

	ConsolePrint("\n");
    ConsolePrint("------------------------------------\n");
    ConsolePrint("Welcome Custom OS!\n");
	ConsolePrint("os version : 1\n");
    ConsolePrint("------------------------------------\n");
	ConsolePrint("\n");

	MiniConsole();
	for(;;);
}

void InitHardware()
{
	ConsolePrint("<start hardware init...>\n");
    GDTInitialize();
	ConsolePrint("GDT init complete\n");

	IDTInitialize();
	ConsolePrint("IDT init complete\n");

	PICInitialize();
	ConsolePrint("PIC init complete\n");
	
	PITInitialize();
	ConsolePrint("PIT init complete\n");
	StartPITCounter(100); 

	ConsolePrint("hardware init complete\n\n");
}

void MiniConsole()
{
	char input[100];
	while(1)
	{
		ConsolePrint("guest > ");
		memset(input, 0, 100);
		GetInput(input,98);
		ConsolePrint("\n");
	}
}

void GetInput(char* buffer, int size)
{
	char c = 0;
	int BufChar;

	int i = 0;

	while (i < size) 
	{
		BufChar = 1;

		c = KeyboardGetInput();

		if (c == 0x0d)
			break;

		if (c == 0x08) 
		{
			BufChar = 0;

			if (i > 0) 
			{
				i--;
			}
		}

		if (BufChar) 
		{
			if (c != 0) 
			{
				ConsolePrint("%c",c);
				buffer[i++] = c;
			}
		}
	}

	buffer[i] = 0;
}