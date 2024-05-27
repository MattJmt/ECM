#include <xc.h>
#include "LCD.h"

/************************************
 * Function to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
************************************/
void LCD_E_TOG(void)
{
	//turn the LCD enable bit on
    LATCbits.LATC2=1;   //E
	__delay_us(2); //wait a short delay
	//turn the LCD enable bit off again
    LATCbits.LATC2=0;   //E
	__delay_us(2); //wait a short delay
}

/************************************
 * Function to set the 4-bit data line levels for the LCD
************************************/
void LCD_sendnibble(unsigned char number)
{

	//set the data lines here (think back to LED array output)
    
    LATBbits.LATB3 = (number & 0b00000001)? 1 : 0;
    LATBbits.LATB2 = (number & 0b00000010)? 1 : 0;
    LATEbits.LATE3 = (number & 0b00000100)? 1 : 0;
    LATEbits.LATE1 = (number & 0b00001000)? 1 : 0;
    LCD_E_TOG();			//toggle the enable bit to instruct the LCD to read the data lines
    __delay_us(5);      //Delay 5uS
}


/************************************
 * Function to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
************************************/
void LCD_sendbyte(unsigned char Byte, char type)
{
    // set RS pin whether it is a Command (0) or Data/Char (1) using type argument
    // send high bits of Byte using LCDout function
    // send low bits of Byte using LCDout function
	LATCbits.LATC6 = (type)? 1 : 0;
    
    LCD_sendnibble(Byte>>4);
    LCD_sendnibble(Byte&0b00001111);
    
    
    __delay_us(50);               //delay 50uS (minimum for command to execute)
    LATCbits.LATC6 = 0;
    
}

/************************************
 * Function to initialise the LCD after power on
************************************/
void LCD_Init(void)
{

    //Define LCD Pins as Outputs and
    //set all pins low (might be random values on start up, fixes lots of issues)
    
    LATCbits.LATC6=0;
    LATCbits.LATC2=0;
    LATBbits.LATB3=0;
    LATBbits.LATB2=0;
    LATEbits.LATE3=0;
    LATEbits.LATE1=0;


    TRISCbits.TRISC6=0;
    TRISCbits.TRISC2=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB2=0;
    TRISEbits.TRISE3=0;
    TRISEbits.TRISE1=0;    
    
    //Initialisation sequence code
	// follow the sequence in the GitHub Readme picture for 4-bit interface.
	// first Function set should be sent with LCD_sendnibble (the LCD is in 8 bit mode at start up)
	// after this use LCD_sendbyte to operate in 4 bit mode

    __delay_ms(50);
    
    LCD_sendnibble(0b0011);           //function set
    
    __delay_us(50);
        
    LCD_sendbyte(0b00101000,0);           //function set
    
    __delay_us(50);    
    
    LCD_sendbyte(0b00001110,0);           //display on/off control

    __delay_us(50);    
    
    LCD_sendbyte(0b00000001,0);           //display clear

    __delay_ms(10);    
    
    LCD_sendbyte(0b00000110,0);           //entry mode set

    __delay_ms(10);
    
    LCD_sendbyte(0b00001100,0);
	//remember to turn the LCD display back on at the end of the initialisation (not in the data sheet)
}


/************************************
 * Function to set the cursor to beginning of line 1 or 2
************************************/
void LCD_setline (char line)
{
    if (line){
        LCD_sendbyte(0x80,0);
    }
    else{
        LCD_sendbyte(0xC0,0);
    }
    
    //Send 0x80 to set line to 1 (0x00 ddram address)
    //Send 0xC0 to set line to 2 (0x40 ddram address)
}

/************************************
 * Function to send string to LCD screen
************************************/
void LCD_sendstring(char *string)
{
	//code here to send a string to LCD using pointers and LCD_sendbyte function
    while(*string != 0){  // While the data pointed to isn?t a 0x00 do below (strings in C must end with a NULL byte) 
		LCD_sendbyte(*string++,1); 	//Send out the current byte pointed to and increment the pointer
	}
}

