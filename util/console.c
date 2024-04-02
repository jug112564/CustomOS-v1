#include "console.h"

//색상영역
int color;
int textColor;
int backGroundColor;

//위치 영역
unsigned int xPos;
unsigned int yPos;

//비디오 메모리
unsigned short* pVideoMemory  = (unsigned short*)0xb8000;

//콘솔초기화
void ConsoleInitialize()
{
    textColor = Green;
    backGroundColor = Black;
    color = (backGroundColor << 4) | textColor;

    xPos = 0;
    yPos = 0;
}

void ConsolePrint(const char* s, ...)
{
	if (!s)
		return;

	va_list args;
	va_start(args, s);
	unsigned int i;

	for (i = 0; i < strlen(s); i++) {

		switch (s[i]) {
		case '%':
			switch (s[i + 1]) {
			case 'c': {
				char c = va_arg(args, char);
				ConsolePrintChar(c);
				i++;		
				break;
			}
			case 's': {
				const char* c = va_arg(args, const char*);
				char str[256];
				strcpy(str, c);
				ConsolePrintString(str);
				i++;
				break;
			}
			case 'd':
			case 'i': {
				int c = va_arg(args, int);
				char str[32] = { 0 };
				itoa_s(c, 10, str);
				ConsolePrintString(str);
				i++;	
				break;
			}
			case 'X': {
				int c = va_arg(args, int);
				char str[32] = { 0 };
				itoa_s(c, 16, str);
				ConsolePrintString(str);
				i++;		
				break;
			}
			case 'x': {
				unsigned int c = va_arg(args, unsigned int);
				char str[32] = { 0 };
				itoa_s(c, 16, str);
				ConsolePrintString(str);
				i++;	
				break;
			}

			default:
				va_end(args);
				return;
			}

			break;

		default:
			ConsolePrintChar(s[i]);
			break;
		}

	}

	va_end(args);	
}

//문자 콘솔에 출력
void ConsolePrintString(const char* s)
{
	while(*s)
	{
		ConsolePrintChar(*s);
		s++;
	}
}


void ConsolePrintChar(char c)
{
    int t;
    switch (c)
    {
	case '\r':                         
    	xPos = 0;
		break;

    case '\n':                         
    	xPos = 0;
		yPos++;
	    break;

    case 8:                            
	    t = xPos + yPos* SCREEN_WIDTH;  
	    if (t > 0) t--;

    	if (xPos > 0)
		{
		    xPos--;
    	}
		else if (yPos > 0)
	    {
    		yPos--;
	    	xPos = SCREEN_WIDTH - 1;
	    }

    	*(pVideoMemory + t) = ' ' | ((unsigned char)color << 8);
		break;

    default:
    	if (c < ' ') break;			

    	unsigned short* VideoMemory = pVideoMemory + SCREEN_WIDTH *yPos + xPos;
	    unsigned char attribute = (unsigned char)((backGroundColor << 4) | (textColor & 0xF));

    	*VideoMemory = (c | (unsigned short)(attribute << 8));
	    xPos++;
		break;
	}

	if (xPos >= SCREEN_WIDTH)
	    yPos++;

	if (yPos == SCREEN_HEIGHT)			
	{
		ConsoleScrollup();	
		yPos--;			
	}    
}

//콘솔 지우기
void ConsoleClear()
{
	for (unsigned int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		pVideoMemory[i] = (unsigned short)(0x20 | (color << 8));
	}
	xPos = 0;
	yPos = 0;
}

//스크롤
void ConsoleScrollup()
{
    unsigned int t = 0;

	for (t = 0; t < SCREEN_WIDTH * (SCREEN_HEIGHT - 1); t++)		
		*(pVideoMemory + t) = *(pVideoMemory + t + SCREEN_WIDTH);
	for (; t < SCREEN_WIDTH * SCREEN_HEIGHT; t++)		
		*(pVideoMemory + t) = ' ' | ((unsigned char)color << 8);
}