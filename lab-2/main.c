#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include <math.h>
#include "LEDarray.h"
#include "ADC.h"


#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) 
{
    ADC_init(); // initialise the ADC
    ADC_getval(); // return a binary value for the intensity measured by the LDR
    unsigned int max; // create a maximum value
    char timer_count = 0; //variable to keep count intervals before max value has to drop
    
    LEDarray_init();
    Button_init();
    
    
    
    while (1) {
        if (ADC_getval()> max) {max = ADC_getval();} //assign the maximum value
        if (max > 90) {max = 90;} // prevent max from increasing above LED bit range
        // offset of -32 to calibrate the range (ie. for LED 1 to be off when finger is over the LED)
        
        LEDarray_disp_PPM(ADC_getval(),max); //display the current and max value
        
        __delay_ms(20); //incremental change between current values
        
        // for the max value to decrease, it needs to 'fall' by 10 (to change LED) every 5*200ms (1 sec)
        timer_count++;
        
        if (timer_count == 50) { // 5 * 200ms = 1 sec 
            
            if (max <= 10) {max = 0;}
            else{max = max - 10;} // reduce max by 10 to change LED}
            timer_count = 0; //reset the counter for next drop
            
        }
        
        /*
        if (!PORTFbits.RF2) {
            count = count + 1;

            __delay_ms(200);
        } //increasing bit number for the Knight Rider pattern
        if (count > 90) count = 0; // reset the counter to 0 once it reaches 90
        LEDarray_disp_dec(count); //output a on the LED array in decimal
        
        //__delay_ms(40);// Delay so human eye can see change
 */
     
    }
}