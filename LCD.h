#ifndef LCD
#define LCD

#include "tm4c123gh6pm.h"
#include <stdio.h>

//LCD Data connected to PORT B
//LCD RS & EN connected to PORT A pins(3,2)

#define LCD_CTRL_CLOCK SYSCTL_RCGCGPIO_R0
#define LCD_CTRL_DATA GPIO_PORTA_DATA_R
#define LCD_CTRL_DIR GPIO_PORTA_DIR_R
#define LCD_CTRL_DEN GPIO_PORTA_DEN_R
#define RS (1U << 3)
#define EN (1U << 2)

void LCD_init();
void LCD_data(unsigned char);
void LCD_start();
void LCD_command(unsigned char);
void LCD_writeNumber(int);
void LCD_writeString(char []);
void LCD_deleteChar(void);
void LCD_clear();

void delay_micro_LCD(int);
void delay_milli_LCD(int); 
#endif