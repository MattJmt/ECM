#include "syncro.h"

void syncro(char daylightSavings) {
    char trueMid = 12;              // theoretical Midday time
    if (daylightSavings){char trueMid = 13;}            //add an hour if in daylight savings mode
    if ( ((sunUp - sunDown) > 7) & (sunUp - sunDown < 16) ){       // check difference between SunUp & Sundown is within appropriate range 
    midDay = ((sunUp + sunDown)/2);         //find midday time by taking the average of the light setting up and setting down. 
        if (midDay != trueMid){             
            
            if ((midDay - trueMid) > 0){hour += (midDay - trueMid);}        //check if difference between sun's time and true time is positive, increment difference to 'hour'
            
            else{
                while (hour < (trueMid - midDay)){__delay_ms(1);}           //if difference between sun's time and true time is negative, 'hold hour' for difference
                hour = 0;                                                   //set hour to 0
                
            }
        }
    }
    else{midDay = 0;}                   //reset variables to prevent explosion and end of world xD
    sunUp = sunDown = 0;
}
