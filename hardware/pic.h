#ifndef _PIC_H
#define _PIC_H

#include "../util/util.h"

void PICInitialize();
void SendCommandToPIC(unsigned char cmd, unsigned char picNum);
void SendDataToPIC(unsigned char data, unsigned char picNum);
#endif