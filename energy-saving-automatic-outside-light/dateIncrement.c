#include "dateIncrament.h"

/*******************************************
 Function that increments the date when the hour overflows 24, incrementing a day, a month, a year 
 *****************************************/
void dateIncrement(char* daylightSavingsP, char* dayOfWeekP, char* dayOfMonthP, char* monthP, unsigned int* yearP) {

    //char daylightSavings = 0;             // ensure this value is correct depending on when you start the light.
    char runSyncro = 1;            //enable function to keep synchronised with the sun (it can be turned off it not wanted ie. manual input)
    
    
        
    if (hour >= 24){        // increment the days and reset hours
        hour = 0;           //reset hour once it is past midnight
        *dayOfWeekP +=1;    // increment one day (of week)
        *dayOfMonthP += 1;      //increment one day (of month)
        if (runSyncro){syncro(*daylightSavingsP);}      //check if synchronised has been enable, run synchronised function
    }
    
    if (*dayOfWeekP > 7){*dayOfWeekP = 1; }  // reset day of the week 
    
    // some if statements to increment the months 
    if (*dayOfMonthP > 30 & (*monthP == 4 | *monthP == 6 | *monthP == 9 | *monthP == 11)){*dayOfMonthP = 1; *monthP +=1;}   //increment 30-day months 
    if (*dayOfMonthP > 31 & (*monthP == 1 | *monthP == 3 | *monthP == 5 | *monthP == 7 | *monthP == 8 | *monthP == 10)){*dayOfMonthP = 1; *monthP +=1;} //increment 31-day months
    if (*dayOfMonthP > 27 & *monthP == 2){          // increment month variable for February
        if (*yearP%4 == 0){                         // check for leap years
            if (*dayOfMonthP > 29){*dayOfMonthP = 1; *monthP +=1;}      //increment month variable on 29th day
        }
        else{
            if (*dayOfMonthP > 28){*dayOfMonthP = 1; *monthP +=1;}      //increment month variable on 28th day
        }
    }  
    //reset the months at the end of the year and increment year
    if (*dayOfMonthP > 31 & *monthP == 12){*dayOfMonthP = 1; *monthP = 1; *yearP+=1;}      //increment a new year 
    
     //adjust time for daylight savings  
    if (*monthP == 3 & *dayOfMonthP > 24 & *dayOfWeekP == 7 & !*daylightSavingsP & hour == 1){hour -= 1; *daylightSavingsP = 1;} // subtract an hour in March  
    if (*monthP ==8 & *dayOfMonthP > 24 & *dayOfWeekP == 7 & *daylightSavingsP) {hour += 1; *daylightSavingsP = 0;}  // add an hour in October
    
}