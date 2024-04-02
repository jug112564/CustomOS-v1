#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "standardlib/stdarg.h"
#include "standardlib/string.h"
//스크린 크기 지정
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

//색상지정
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	LightBrown = 14,
	White = 15
};

void ConsoleInitialize();                   //콘솔초기화
void ConsolePrint(const char* s, ...);      //문자 콘솔에 출력

void ConsolePrintString(const char* s);		//문자열 출력
void ConsolePrintChar(char c);				//문자 1개 출력

void ConsoleClear();                        //콘솔 지우기
void ConsoleScrollup();                     //스크롤

#endif