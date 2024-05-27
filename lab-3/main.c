// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) {
	//call your initialisation functions to set up the hardware modules
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    //LATDbits.LATD7=0;   //set initial output state - this is to detect when the chip has entered sleep mode
    //TRISDbits.TRISD7=0; //set TRIS value for pin (output)
    
    Interrupts_init();
    Comp1_init();
    

    LEDarray_init();
    Timer0_init();
    
    while (1) {
        
        LEDarray_disp_bin(get16bitTMR0val()>> 8);
        
        
        /*
        LATDbits.LATD7 = 0; 
        __delay_ms(50);
        
        Sleep(); // if commenting out Sleep, the D7 LED will flash repeatedly
        
        LATDbits.LATD7 = 1;
        __delay_ms(50);
        */
    }
}