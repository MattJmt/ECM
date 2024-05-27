// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#pragma once  // should only inclue the files once
#include <stdio.h>
#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "LCD.h"
//#include "syncro.h"
#include "dateIncrament.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
	//call your initialisation functions to set up the hardware modules
    
    LATHbits.LATH3=0;   //set initial output state for right LED
    TRISHbits.TRISH3=0; //set TRIS value for pin (output) for the right LED
    
    
    //run all of the initialisations
    Interrupts_init(); 
    Comp1_init();   // Rising edge flag
    Comp2_init();   // Falling edge flag
    Timer0_init();
    LEDarray_init();
    LCD_Init();
    
    
    // initialise all of the variables we need
    char dayOfWeek = 1;
    char dayOfMonth = 25;
    char month = 3;
    unsigned int year = 2022;
    char daylightSavings = 0;             // ensure this value is correct depending on when you start the light.
    char deadTime = 0;
    
    while (1) {     //start loop
   
    if (hour >= 1  && hour <=5){        //set the energy saving dead-zone between 1 and 5
        deadTime = 1;                   //Deadtime variable to indicate whether to turn light on/off
    }   
    else{deadTime = 0;}
    
    
    if (CM1CON0bits.OUT & !deadTime){LATHbits.LATH3=1;}     //control if the led is on or off depending on comparator output and deadTime
    else{LATHbits.LATH3=0;}                                 //turn off if deadTime = 1
       
    dateIncrement(&daylightSavings, &dayOfWeek, &dayOfMonth, &month, &year);    // date incrementation function
      
    //display the current hour in binary
    LEDarray_disp_bin(hour);
    
    //display hour and date on LCD
    char buf1[40];      // 40 character array
    char buf2[40];      // 40 character array
    sprintf(buf1, "H:%d DoW:%d MD:%d  ",hour,dayOfWeek,midDay);     //store hour, day of week, midday in memory buffer 1
    sprintf(buf2,"Date: %d/%d/%d  ",dayOfMonth,month,year);         //store date in memory buffer 1
    LCD_setline(1);
    LCD_sendstring(buf1);       //display hour, day of the week and midday on LCD
    LCD_setline(0);
    LCD_sendstring(buf2);       //display date on the LCD
    } 
}