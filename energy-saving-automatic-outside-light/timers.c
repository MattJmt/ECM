#include <xc.h>
#include "timers.h"


void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b0110; // to find the delay between incraments, multiply the 2^prescale by 4/clock speed * 2^16 bits
    T0CON0bits.T016BIT=1;	// set the bit mode (0 for 8 bit and 1 for 16 bit)	
	
    //initialise the timer registers so we know we are at 0
    TMR0H=0;
    TMR0L=0;
    T0CON0bits.T0EN=1;	//start the timer
    
}
