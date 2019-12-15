#ifndef keypad
#define keypad

#include "tm4c123gh6pm.h"

//Keypad Rows conncected PORT A pins (4,5,6,7)
//Keypad Cols conncected PORT C pins (4,5,6,7)

#define keypad_ROW_CLOCK SYSCTL_RCGCGPIO_R0;
#define keypad_ROW_DATA GPIO_PORTA_DATA_R
#define keypad_ROW_DIR  GPIO_PORTA_DIR_R
#define keypad_ROW_DEN  GPIO_PORTA_DEN_R
#define keypad_ROW_ODR  GPIO_PORTA_ODR_R
#define R0 (1U << 4)
#define R1 (1U << 5)
#define R2 (1U << 6)
#define R3 (1U << 7)

#define keypad_COL_CLOCK SYSCTL_RCGCGPIO_R2
#define keypad_COL_DATA GPIO_PORTC_DATA_R
#define keypad_COL_DIR  GPIO_PORTC_DIR_R
#define keypad_COL_DEN  GPIO_PORTC_DEN_R
#define keypad_COL_PUR  GPIO_PORTC_PUR_R
#define C0 (1U << 4)
#define C1 (1U << 5)
#define C2 (1U << 6)
#define C3 (1U << 7)

void keypad_init(void);
char getKeyPressed (void);
int isKeyPressed(void);

#endif