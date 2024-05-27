#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
    // pin G0
    LATGbits.LATG0=0;   //set initial output state
    TRISGbits.TRISG0=0; //set TRIS value for pin (output)
    //pin G1
    LATGbits.LATG1=0;   //set initial output state
    TRISGbits.TRISG1=0; //set TRIS value for pin (output)
    //pin A2
    LATAbits.LATA2=0;   //set initial output state
    TRISAbits.TRISA2=0; //set TRIS value for pin (output)
    //pin F6
    LATFbits.LATF6=0;   //set initial output state
    TRISFbits.TRISF6=0; //set TRIS value for pin (output)
    //pin A4
    LATAbits.LATA4=0;   //set initial output state
    TRISAbits.TRISA4=0; //set TRIS value for pin (output)
    //pin A5
    LATAbits.LATA5=0;   //set initial output state
    TRISAbits.TRISA5=0; //set TRIS value for pin (output)
    //pin F0
    LATFbits.LATF0=0;   //set initial output state
    TRISFbits.TRISF0=0; //set TRIS value for pin (output)
    //pin B0
    LATBbits.LATB0=0;   //set initial output state
    TRISBbits.TRISB0=0; //set TRIS value for pin (output)
    //pin B1
    LATBbits.LATB1=0;   //set initial output state
    TRISBbits.TRISB1=0; //set TRIS value for pin (output)
    
}

void Button_init(void)
{
    // setup pin for input (connected to button) right button RF3
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
	if (number & 0b000000001) {LATGbits.LATG0 = 1;} else {LATGbits.LATG0 = 0;} // number & 1
    if (number & 0b000000010) {LATGbits.LATG1 = 1;} else {LATGbits.LATG1 = 0;}
    if (number & 0b000000100) {LATAbits.LATA2 = 1;} else {LATAbits.LATA2 = 0;}
    if (number & 0b000001000) {LATFbits.LATF6 = 1;} else {LATFbits.LATF6 = 0;}
    if (number & 0b000010000) {LATAbits.LATA4 = 1;} else {LATAbits.LATA4 = 0;}
    if (number & 0b000100000) {LATAbits.LATA5 = 1;} else {LATAbits.LATA5 = 0;}
    if (number & 0b001000000) {LATFbits.LATF0 = 1;} else {LATFbits.LATF0 = 0;}
    if (number & 0b010000000) {LATBbits.LATB0 = 1;} else {LATBbits.LATB0 = 0;}
    if (number & 0b100000000) {LATBbits.LATB1 = 1;} else {LATBbits.LATB1 = 0;} // number & 9
    
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{

    unsigned int disp_val = 0;
    int i; // instantiate iterator variable
    
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
    for (i=0; i < 10; i ++){ 
        if (number >= i*10){ //check if the next factor of 10 is reached
            disp_val += 1 << i; // update the relevant bit corresponding to the LED that should be lit
        }
    }

	LEDarray_disp_bin(disp_val); 	//display value on LED array

}


/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/

void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val; 
    unsigned int cur_val_bin; // binary variable for cur_val
    unsigned int max_bin; // binary variable for max
    
    if (cur_val > 90) {cur_val_bin = 0b111111111;} //limit the max value for the current value (ie. 9)
    if (90>=cur_val && cur_val>80) {cur_val_bin = 0b011111111;} // LED 9-1
    if (80>=cur_val && cur_val>70) {cur_val_bin = 0b001111111;} // LED 8-1
    if (70>=cur_val && cur_val>60) {cur_val_bin = 0b000111111;} // LED 7-1
    if (60>=cur_val && cur_val>50) {cur_val_bin = 0b000011111;} // LED 6-1
    if (50>=cur_val && cur_val>40) {cur_val_bin = 0b000001111;} // LED 5-1
    if (40>=cur_val && cur_val>30) {cur_val_bin = 0b000000111;} // LED 4-1
    if (30>=cur_val && cur_val>20) {cur_val_bin = 0b000000011;} // LED 3-1
    if (20>=cur_val && cur_val>10) {cur_val_bin = 0b000000001;} // LED 2-1
    if (10>=cur_val && cur_val>0) {cur_val_bin = 0b000000000;} // LED 1-1
	
    
    //conversion from decimal to binary 
    
    if (max > 90) {max_bin = 0b100000000;} // limit max bit for the max value
    if (90>=max && max>80) {max_bin = 0b100000000;} // LED 9
    if (80>=max && max>70) {max_bin = 0b010000000;} // LED 8
    if (70>=max && max>60) {max_bin = 0b001000000;} // LED 7
    if (60>=max && max>50) {max_bin = 0b000100000;} // LED 6
    if (50>=max && max>40) {max_bin = 0b000010000;} // LED 5
    if (40>=max && max>30) {max_bin = 0b000001000;} // LED 4
    if (30>=max && max>20) {max_bin = 0b000000100;} // LED 3
    if (20>=max && max>10) {max_bin = 0b000000010;} // LED 2
    if (10>=max && max>0) {max_bin = 0b000000001;} // LED 1
    
    disp_val = cur_val_bin | max_bin; // merge both binary values

	LEDarray_disp_bin(disp_val);	//display value on LED array
}


