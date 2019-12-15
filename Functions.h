#ifndef Functions
#define Functions

#include "Constants.h"

void init(void);
int buttons_pressed(void);

void timer_delay_milli(int);
void timer_delay_micro(int);
void delaySec(void);
void delay_milli(int);

void turnRedLedOn(void);
void turnRedLedOff(void);
int getNum(void);

#endif