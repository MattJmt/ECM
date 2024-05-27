#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/

void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE=1; 	//enable interrupt source INT0
    
    INTCONbits.PEIE=1; // turns on peripherial interrupts (taken from data sheet)
    
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/

void __interrupt(high_priority) HighISR() //keep this function as short as possible- HighISR is arbitrary name for comprehension.
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if(PIR2bits.C1IF){ 					//check the to see if interrupt source was triggered for Peripheral Input Register (PIR)
	
    LATHbits.LATH3 = !LATHbits.LATH3; // do something after interrupt source was triggered eg. Switch LED H3 on/off
	
    PIR2bits.C1IF=0; 						//clear (reset) the interrupt flag (=notification)! So it can be triggered once more. Prevent endless loop
	}
}

