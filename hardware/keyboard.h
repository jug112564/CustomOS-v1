#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "interrupt.h"
#include "../util/console.h"

void InstallKeyboard();
void HandleKeyboard(struct InterruptRegisters* regs);

void SetLeds(unsigned char num, unsigned char caps, unsigned char scroll);
void SendEncodeCommand(unsigned char cmd);
int SpecialKey(unsigned char key);
void UpdateLeds(unsigned char led);
char KeyboardGetInput();

#endif