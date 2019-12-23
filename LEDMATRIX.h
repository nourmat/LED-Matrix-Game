#ifndef LEDMATRIX
#define LEDMATRIX

#include "tm4c123gh6pm.h"

#define subCOLSIZE 8
#define subROWSIZE 8
#define COLSIZE 16
#define ROWSIZE 8

#define DELAYTIME 10 //MICROSECONDS
#define LATCHPULSEDELAY 1 //MICROSECONDS FOR LATCH ONLY REFRESH 
#define PULSEDELAY 20 //FOR DATA AND SHIFT

#define LOW 0
#define HIGH 1

//Keypad Rows conncected PORT A pins (4,5,6)
//Keypad Cols conncected PORT C pins (4,5,6)

#define LED_ROW_CLOCK SYSCTL_RCGCGPIO_R0
#define LED_ROW_DATA GPIO_PORTA_DATA_R
#define LED_ROW_DIR GPIO_PORTA_DIR_R
#define LED_ROW_DEN GPIO_PORTA_DEN_R
#define LED_ROW_ODR GPIO_PORTA_ODR_R
#define LED_ROW_PUR GPIO_PORTA_PUR_R
#define LED_ROW_PDR GPIO_PORTA_PDR_R
#define DataRow (1U << 4)
#define LatchRow (1U << 3)
#define ShiftRow (1U << 2)

#define LED_COL_CLOCK SYSCTL_RCGCGPIO_R2
#define LED_COL_DATA GPIO_PORTC_DATA_R
#define LED_COL_DIR  GPIO_PORTC_DIR_R
#define LED_COL_DEN  GPIO_PORTC_DEN_R
#define LED_COL_ODR  GPIO_PORTC_ODR_R
#define LED_COL_PUR  GPIO_PORTC_PUR_R
#define LED_COL_PDR  GPIO_PORTC_PDR_R
#define DataCol (1U << 4)
#define LatchCol (1U << 5)
#define ShiftCol (1U << 6)

void LED_init(void);
void digitalWrite(volatile unsigned long*,int,int);
void writeShape(int[ROWSIZE][COLSIZE]);
void refresh(void);
int assignNonBlockArray(int [subROWSIZE][subCOLSIZE], int [ROWSIZE][COLSIZE],int,int);
int assignBlockArray(int [subROWSIZE][subCOLSIZE], int [ROWSIZE][COLSIZE],int,int);
void playDiagonal(void);
void writeAllExceptCol(int);

void resetRows(void);
void resetCols(void);
void fireRows(void);
void fireCols(void);

void shiftRows(int);
void shiftCols(int);

void outputRows(void);
void outputCols(void);

int** getLED();
void cpyArrToScreen(int [ROWSIZE][COLSIZE]);

#endif