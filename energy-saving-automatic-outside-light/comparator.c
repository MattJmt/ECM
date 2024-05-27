#include <xc.h>
#include "comparator.h"


void DAC_init(void)
{
    DAC1CON0bits.PSS=0b00;      //3.3V for positive source (Vdd)
    DAC1CON0bits.NSS=0b0;      //0v for Negative source (Vss))

    DAC1CON1bits.DAC1R=0b10000; // adjust according to ambient light 27~2.87V
    DAC1CON0bits.DAC1EN=1;      //turn on DAC
}


void Comp1_init(void)
{
    TRISFbits.TRISF7=1;		// set pin RF7 as input
    CM1NCHbits.NCH=0b011; 	// pin RF7 as input for comparator
    CM1PCHbits.PCH=0b101;   //use DAC output for positive input
    CM1CON0bits.HYS=1;      //a little bit of hysteresis to stop multiple triggers
    CM1CON0bits.POL=1;      //inverts polarity of comparator needed for intended use
    
    CM1CON1bits.INTP=1; 	//set interrupt flag on positive going edge
    
    DAC_init();				//initialise the DAC
    CM1CON0bits.EN=1;   	//enable comparator 1
    
}


void Comp2_init(void)
{
    TRISFbits.TRISF7=1;		// set pin RF7 as input
    CM2NCHbits.NCH=0b011; 	// pin RF7 as input for comparator
    CM2PCHbits.PCH=0b101;   //use DAC output for positive input
    CM2CON0bits.HYS=1;      //a little bit of hysteresis to stop multiple triggers
    CM2CON0bits.POL=1;      //inverts polarity of comparator needed for intended use
    
    CM2CON1bits.INTN=1;     //set interrupt flag on negative going edge
    
    DAC_init();				//initialise the DAC
    CM2CON0bits.EN=1;   	//enable comparator 1
}
