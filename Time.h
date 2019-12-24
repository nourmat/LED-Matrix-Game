#ifndef Time
#define Time

#include "tm4c123gh6pm.h"

void Timer0_Init(void);
void delayMicroseconds(int);
void delay_milli(int);

void systickInit(int);

#endif