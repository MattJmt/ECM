#include <xc.h>
#include "interrupts.h"

//char hour = 0;  // decalre outside of function to make vaiable global


void Interrupts_init(void)
{
    
PIE2bits.C1IE=1; 	//enable interrupt source COMP 1 
PIE2bits.C2IE=1;    //enable interrupt source COMP 2
PIE0bits.TMR0IE = 1; //enable interrupt source timer


INTCONbits.IPEN=1; // enables multiple priority levels
INTCONbits.GIEL=1; // turn on low priority interupts 

IPR2bits.C1IP=1;   // set the COMP1 interuprt to high priority 
IPR2bits.C2IP=1;  // set the COMP2 interupt to high priority 
IPR0bits.TMR0IP =1; // set the timer interupt to high priority 

INTCONbits.PEIE = 1; //turns on peripheral interupts 
INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)

}



void __interrupt(high_priority) HighISR()
{
    if(PIR2bits.C2IF){              // check the interrupt source
        
    sunDown = hour;             // set the time for the sun going down 
	PIR2bits.C2IF=0; 				// clear the interrupt flag!
    }
    
    
    if(PIR2bits.C1IF){ 				// check the interrupt source
        
    sunUp = hour;             // set the time for the sun coming up   
	PIR2bits.C1IF=0; 				//clear the interrupt flag!
	}
    
    
    if(PIR0bits.TMR0IF){ 					//check the timer interrupt source
        
    hour++;                                //if timer overflows, add an hour
        
	PIR0bits.TMR0IF=0; 						//clear the interrupt flag!
	

    TMR0H= 00001011;        // this sets the 8 bit counter to start at 3036 to eliminate the slight offset you get from setting the prescaler to 256
    TMR0L= 11011011;
      
    } 
}


