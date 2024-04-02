#include "keyboard.h"

unsigned char normal[] = {					
	0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
	'q','w','e','r','t','y','u','i','o','p','[',']',0x0D,0x80,
	'a','s','d','f','g','h','j','k','l',';',047,0140,0x80,
	0134,'z','x','c','v','b','n','m',',','.','/',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,'0',0177
};

unsigned char shifted[] = {
	0,033,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t',
	'Q','W','E','R','T','Y','U','I','O','P','{','}',015,0x80,
	'A','S','D','F','G','H','J','K','L',':',042,'~',0x80,
	'|','Z','X','C','V','B','N','M','<','>','?',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

unsigned char capsNormal[] = {
	0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
	'Q','W','E','R','T','Y','U','I','O','P','[',']',0x0D,0x80,
	'A','S','D','F','G','H','J','K','L',';',047,0140,0x80,
	'|','Z','X','C','V','B','N','M',',','.','/',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,'0',0177
};

unsigned char capsShifted[] = {
	0,033,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t',
	'q','w','e','r','t','y','u','i','o','p','{','}',015,0x80,
	'a','s','d','f','g','h','j','k','l',':',042,'~',0x80,
	0134,'z','x','c','v','b','n','m','<','>','?',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

char buffer[129];	
int buffend = 0;		

int shift=0;
int caps=0;
int ctrl=0;
int alt=0;
int num = 0;

unsigned char leds = 0; 

unsigned char scanCode;
void InstallKeyboard() 
{
	IrqInstallHandler(1, HandleKeyboard);

	SetLeds(0, 0, 0);
}

void HandleKeyboard(struct InterruptRegisters* regs)
{
	unsigned char asciiCode;

	scanCode = InPortByte(0x60);	

	if (!(SpecialKey(scanCode) | (scanCode >= 0x80))) 
	{
		if (shift)
		{
			if (!caps)
			{
				asciiCode = shifted[scanCode];
			}
			else
			{
				asciiCode = capsShifted[scanCode];
			}
		}
		else
		{
			if (!caps)
			{
				asciiCode = normal[scanCode];
			}
			else
			{
				asciiCode = capsNormal[scanCode];
			}
		}

		if (buffend != 128)
		{
			buffend++;
		}
		buffer[buffend] = asciiCode;
	}
}

void SetLeds(unsigned char num, unsigned char caps, unsigned char scroll) 
{
	unsigned char data = 0;

	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? 3 : 0;
	data = (caps) ? 0b101 : 0;

	SendEncodeCommand(0xED);
	SendEncodeCommand(data);
}

void SendEncodeCommand(unsigned char cmd) 
{
	while (1)
		if ((InPortByte(0x64) & 2) == 0)
			break;

	OutPortByte(0x60, cmd);
}

int SpecialKey(unsigned char key)
{
	unsigned char specKeyUp = 1;	
	switch (key)
	{
	case 0x36: //R-Shift down
	case 0x2A: //L-Shift down
		shift = 1;
		break;
	case 0xB6: //R-Shift up
	case 0xAA: //L-Shift up
		shift = 0;
		break;
	case 0x1D: //Control down
		ctrl = 1;
		break;
	case 0x9D: //Control up
		ctrl = 0;
		break;
	case 0x38: //Alt down
		alt = 1;
		break;
	case 0xB8: //Alt up
		alt = 0;
		break;
	case 0x3A: //Caps down
		if (specKeyUp == 1)
		{
			caps = !caps;
			UpdateLeds(0x04);
			specKeyUp = 0;
		}
		break;
	case 0x45: //Num down
		if (specKeyUp == 1)
		{
			num = !num;
			UpdateLeds(0x02);
			specKeyUp = 0;
		}
		break;
	case 0x46: //Scroll down
		if (specKeyUp == 1)
		{
			num = !num;
			UpdateLeds(0x01);
			specKeyUp = 0;
		}
		break;
	case 0x3B: //F1 Down
	case 0x3C: //F2 Down
	case 0x3D: //F3 Down
	case 0x3E: //F4 Down
	case 0x3F: //F5 Down
	case 0x40: //F6 Down
	case 0x41: //F7 Down
	case 0x42: //F8 Down
	case 0x43: //F9 Down
	case 0x44: //F10 Down
		specKeyUp = 0;
		break;
	case 0xBA: //Caps Up
	case 0xBB: //F1 Up
	case 0xBC: //F2 Up
	case 0xBD: //F3 Up
	case 0xBE: //F4 Up
	case 0xBF: //F5 Up
	case 0xC0: //F6 Up
	case 0xC1: //F7 Up
	case 0xC2: //F8 Up
	case 0xC3: //F9 Up
	case 0xC4: //F10 Up
	case 0xC5: //Num Up
	case 0xC6: //Scroll Up
		specKeyUp = 1;
		break;
	case 0xE0:
		break;
	default:
		return 0;
	}
	return 1;
}

void UpdateLeds(unsigned char led)
{
	if(led == 0)
	{
		leds = 0;
	}
	else
	{
		if (leds == (leds|led))
		{
			leds = leds^led;
		}
		else
		{
			leds = leds | led;	
		}
	}

	OutPortByte(0x64, 0xED);
	while ((InPortByte(0x64) % 2) == 2)
		;

	OutPortByte(0x60, leds);
}

char KeyboardGetInput()
{
	int i = 0;

	while (buffend == 0)
	{ }

	for (; i < buffend; i++)
	{
		buffer[i] = buffer[i + 1];
	}
	buffend--;

	return buffer[0];
}