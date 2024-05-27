/*
 * File:   newmain.c
 * Author: matja
 *
 * Created on 16 November 2022, 22:17
 */
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep

#include <xc.h>
#include "serial.h"
#include "LCD.h"
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    initUSART4();
    LCD_Init();
    ADC_init();
    Interrupts_init();
    
    
    /*************Exercise 1***********************************/
    /*
    //Send value inputted on PC
    getCharSerial4();   //wait for a byte to arrive on serial port and read it once it does 
    char buf2[16];
    //sendCharSerial4(getCharSerial4());     //send char to serial interface
    sprintf(buf2, "%d",getCharSerial4());   // convert value inputted on PC to a string
    
    //Send to LCD
    LCD_setline(1);
    LCD_sendstring(buf2);       //display hour, day of the week and midday on LCD
    
    //Send to Interface
    sendStringSerial4(buf2);
    sendStringSerial4(" \r\n");         //new line on interface
    
    /***********************************/
    
            
            
    /****Exercise 2********/
    /*
     
    char voltage[16];
    
    while (1) { 
        
    ADC2String(voltage, ADC_getval());
    sprintf(voltage, "Voltage = %d.%02d V");
    
    sendStringSerial4(voltage);     //send a string to the serial interface
    __delay_ms(100);
    sendStringSerial4(" \r");  // clear the line and start new line or use \n
    __delay_ms(900);           // 1 sec delay
     }
    
    */
    
    
    /***********Exercise 3************/
    
    char voltage[16];
    
    while (1) {
        while (isDataInRxBuf == 1){LCD_sendbyte(getCharFromRxBuf(),1);} //check if our buffer contains data and send to LCD
    
        ADC2String(voltage, ADC_getval());      //receive LDR reading of light intensity
        sprintf(voltage, "Voltage = %d.%02d V");        //convert value into 2 decimal place string
    
        TxBufferedString(voltage);
        sendTxBuf();
        
        TxBufferedString("\r");     // set voltage to new line in interface

        sendTxBuf();
        
        LCD_setline(1);         //send to LCD line 1
        LCD_sendstring(voltage);        //send to LCD
        __delay_ms(200);
    
    }
}
