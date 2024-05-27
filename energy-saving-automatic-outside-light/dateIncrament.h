#pragma once
#include "syncro.h"
#include "interrupts.h"
#include "LCD.h"


void dateIncrement(char* daylightSavings, char* dayOfWeekP, char* dayOfMonthP, char* monthP, unsigned int* yearP);