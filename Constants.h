#ifndef Constants
#define Constants

#include "tm4c123gh6pm.h"

//LCD Data connected to PORT B
//LCD RS & EN connected to PORT A pins(3,2)

//Keypad Rows conncected PORT A pins (4,5,6,7)
//Keypad Cols conncected PORT C pins (4,5,6,7)

#define SW2 (1U)
#define SW1 (1U << 4)
#define RED_LED (1U << 1)

#endif