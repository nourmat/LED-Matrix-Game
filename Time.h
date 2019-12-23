#ifndef Time
#define Time

#include "tm4c123gh6pm.h"

void timeinit(void);

void delaySec(void);
void delay_milli(int);
void delayMicroseconds(int); 
void Timer0_Init(void);

void systickInit(int);

#endif