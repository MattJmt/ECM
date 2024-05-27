#ifndef _interrupts_H
#define _interrupts_H

#include <xc.h>

#define _XTAL_FREQ 64000000

char hour = 0;
char sunUp = 0;
char sunDown = 0;

void Interrupts_init(void);
void __interrupt(high_priority) HighISR();

#endif
