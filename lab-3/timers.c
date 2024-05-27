#include <xc.h>
#include "timers.h"


/************************************
 * Function to set up timer 0
 * Timers are hardware modules that count the number of edges from a clock source input signal and are independent from the processing of machine instructions.
************************************/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Clock source settings = Fosc/4 - The clicker 2 board uses a 16MHz crystal oscillator, we have configured our chip for 64MHz (4x Phase Locked Loop (PLL)). This is the base oscillation frequency (Fosc)
    T0CON1bits.T0ASYNC=1; // see datasheet errata: Asynchronous to system clock - needed to ensure correct operation when Fosc/4 used as clock source. 
    T0CON1bits.T0CKPS=0b1000; // 1:256 or 1:355768 since 16bits = 2^16 = 65536 values - Prescaler value bits. The interval, Tint, between the timer incrementing to the next value is set by the oscillator source and the prescaler, PS. If we were to use a 1:1 prescaler with an Fosc of 64MHz (as it is on our board) the timer would increment every 62.5 ns. Adjusting the prescaler allows us to slow this down and time longer periods.
    T0CON0bits.T016BIT=1;	//16bit mode. 
    
    // enable interrupt
    PIE0bits.TMR0IE = 1; //enable interrupt source for TMR0
    INTCONbits.PEIE = 1; // turns on peripherial interrupts
    INTCONbits.GIE = 1; //turn on interrupts globally 


    INTCONbits.IPEN = 1; // enable interrupt priority
    IPR0bits.TMR0IP = 0; // set as low priority interrupt
    PIR0bits.TMR0IF = 0; // clear the TMR0 interrupt FLag
    
    
    // it's a good idea to initialise the timer registers so we know we are at 0
    TMR0H=0b00011011;            //Current timer value. write High reg first, update happens when low reg is written to
    TMR0L=0b11011011;            //Current timer value. (only L register used in 8 bit mode). If TMROL = 27 for 8bit mode, timer will take 256-27 * time interval until next interrupt -> setting the TMR0H/L higher reduces steps to reach 'overflow' (256 for 8bits, 65536 for 16bit).
    T0CON0bits.T0EN=1;	//start the timer, turn it on. for off = 0
}
// time interval = 4*PS/F_osc = 4*256/64*10^6 = 1.6*10^-5s. ie. 62500 time intervals in 1 second. 
// Our 16bit mode has max value 65535, at which it resets. For it to reset after 1 second, we need max(overflow) value to be 62500.
// 65535 - 62500 = 3035. Hence start from states 3035 = 00001011 11011011 in binary. Hence TMR0H = 00001011 (MSB), TMR0L = 11011011 (LSB). 

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int get16bitTMR0val(void)
{
	//add your code to get the full 16 bit timer value here
    return TMR0L | (TMR0H << 8); // TRM0L inclusive OR 8bit shift left for TMROH. TMR0H only contains a copy of Most Sig Bit. 
    
}

void __interrupt(low_priority) LowISR() //keep this function as short as possible- HighISR is arbitrary name for comprehension.
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if(PIR0bits.TMR0IF == 1){ //TMR0 Flag Register
	
    LATHbits.LATH3 = !LATHbits.LATH3; // do something after interrupt source was triggered eg. Switch LED H3 on/off
	
    TMR0H = 0b00001011; // improve accuracy by resetting everytime it overflows
    TMR0L = 0b11011011;
    
    PIR0bits.TMR0IF = 0; 						//clear (reset) the interrupt flag (=notification)! So it can be triggered once more. Prevent endless loop
	}
}