#include <xc.h>
#include "LEDarray.h"
/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG0=0; 
    TRISGbits.TRISG1=0;
    TRISAbits.TRISA2=0;
    TRISFbits.TRISF6=0;
    TRISAbits.TRISA4=0;
    TRISAbits.TRISA5=0;
    TRISFbits.TRISF0=0;
    TRISBbits.TRISB0=0;
    
    
    //set initial output LAT values (they may have random values when powered on)
    LATGbits.LATG0=0;
    LATGbits.LATG1=0;
    LATAbits.LATA2=0;
    LATFbits.LATF6=0;
    LATAbits.LATA4=0;
    LATAbits.LATA5=0;
    LATFbits.LATF0=0;
    LATBbits.LATB0=0;
   
	

}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(char number)
{
    
    //if statements to turn on/off the pins connected to the LED array
    
    //if (number & 0b00000001) {LATGbits.LATG0=1;} else {LATGbits.LATG0=0;}
    LATGbits.LATG0 = (number & 0b00000001)? 1 : 0;   //alternate way to do the if statement using tenary operator
    
    if (number & 0b00000010) {LATGbits.LATG1=1;} else {LATGbits.LATG1=0;}
    if (number & 0b00000100) {LATAbits.LATA2=1;} else {LATAbits.LATA2=0;}
    if (number & 0b00001000) {LATFbits.LATF6=1;} else {LATFbits.LATF6=0;}
    if (number & 0b00010000) {LATAbits.LATA4=1;} else {LATAbits.LATA4=0;}
    if (number & 0b00100000) {LATAbits.LATA5=1;} else {LATAbits.LATA5=0;}
    if (number & 0b01000000) {LATFbits.LATF0=1;} else {LATFbits.LATF0=0;}
    if (number & 0b10000000) {LATBbits.LATB0=1;} else {LATBbits.LATB0=0;}
}

