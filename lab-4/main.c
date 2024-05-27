// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    LCD_Init();     
    ADC_init();
    
//    LCD_setline(1);
//    LCD_sendstring("This is an overflow test");
//    LCD_setline(0);
//    LCD_sendstring("Antonin sucks");
    
 
    
    char buf[16];
    //LEDarray_init();
    
            
    while (1) {
        
        ADC2String(buf, ADC_getval());
        LCD_setline(1);
        LCD_sendstring(buf);
        //LEDarray_disp_bin(ADC_getval());
        //LCD_scroll();
        __delay_ms(100);
        
    }
}


