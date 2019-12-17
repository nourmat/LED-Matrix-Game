#include "LEDMATRIX.h"


void LED_init() {
  SYSCTL_RCGCGPIO_R |= LED_COL_CLOCK; //clock
  SYSCTL_RCGCGPIO_R |= LED_ROW_CLOCK;

  LED_COL_DEN |= (DataCol | LatchCol | ShiftCol); //enable
  LED_ROW_DEN |= (DataRow | LatchRow | ShiftRow);

  LED_COL_DIR |= (DataCol | LatchCol | ShiftCol); //direction
  LED_ROW_DIR |= (DataRow | LatchRow | ShiftRow);

  LED_COL_DATA &= ~(DataCol  | LatchCol | ShiftCol);  //data
  LED_ROW_DATA &= ~(DataRow | LatchRow | ShiftRow);  //data
  
  Timer0_init();
}

//resets and then adds one to first one (1 0 0 0 0,0 0 0 0)
void resetRows() {
  for (int i = 0 ; i < ROWSIZE; i++)
    shiftRows(LOW);
}

void fireRows() {
  for (int i = 0 ; i < ROWSIZE; i++)
    shiftRows(HIGH);
}

void resetCols() {
  for (int i = 0 ; i < COLSIZE; i++)
    shiftCols(LOW);
}

void fireCols() {
  for (int i = 0 ; i < COLSIZE; i++)
    shiftCols(HIGH);
}

void shiftRows(int data) {
  digitalWrite(&LED_ROW_DATA, LatchRow, LOW);
  digitalWrite(&LED_ROW_DATA, DataRow, data);
  delayMicroseconds(PULSEDELAY);
  //pulse
  digitalWrite(&LED_ROW_DATA, ShiftRow, HIGH);
  delayMicroseconds(PULSEDELAY);
  digitalWrite(&LED_ROW_DATA, ShiftRow, LOW);
  delayMicroseconds(PULSEDELAY);
}

void shiftCols(int data) {
  digitalWrite(&LED_COL_DATA, LatchCol, LOW);
  //data = data ? 0 : 1;
  digitalWrite(&LED_COL_DATA, DataCol, data);
  delayMicroseconds(PULSEDELAY);
  //pulse
  digitalWrite(&LED_COL_DATA, ShiftCol, HIGH);
  delayMicroseconds(PULSEDELAY);
  digitalWrite(&LED_COL_DATA, ShiftCol, LOW);
  delayMicroseconds(PULSEDELAY);
}

void outputRows() {
  //pusle
  digitalWrite(&LED_ROW_DATA, LatchRow, HIGH);
  delayMicroseconds(LATCHPULSEDELAY );
  digitalWrite(&LED_ROW_DATA, LatchRow, LOW);
  delayMicroseconds(LATCHPULSEDELAY );
}

void outputCols() {
  //pusle
  digitalWrite(&LED_COL_DATA, LatchCol, HIGH);
  delayMicroseconds(LATCHPULSEDELAY);
  digitalWrite(&LED_COL_DATA, LatchCol, LOW);
  delayMicroseconds(LATCHPULSEDELAY);
}

//TAKES MASK
void digitalWrite(volatile unsigned long *reg, int mask, int level) {
  if (level)
    *reg |= mask;
  else
    *reg &= ~ mask;
}


int assignBlockArray(int subarray[subROWSIZE][subCOLSIZE], int bigarray [ROWSIZE][COLSIZE], int x,int y){
  if ((y*subROWSIZE < ROWSIZE) && (x*subCOLSIZE < COLSIZE)){
    for(int i = 0 ; i < subROWSIZE ; i++)
      for (int j = 0; j < subCOLSIZE; j++)
        bigarray[i+(subROWSIZE*y)][j+(subCOLSIZE*x)] = subarray[i][j];
      return 1;
    }
  return 0; //if size is not aprpriate
}

int assignNonBlockArray(int subarray[subROWSIZE][subCOLSIZE], int bigarray [ROWSIZE][COLSIZE], int x,int y){
  if ((y < ROWSIZE) && (x < COLSIZE)){
    for(int i = 0 ; (i < subROWSIZE) && (i+y >= ROWSIZE) ; i++)
      for (int j = 0; (j < subCOLSIZE) && (j+x >= COLSIZE); j++)
        bigarray[i+y][j+x] = subarray[i][j];
      return 1;
    }
  return 0; //if size is not aprpriate
}


void writeAllExceptCol(int n){
  n--; //one based
  resetRows();
  shiftRows(HIGH);
  fireCols();
  shiftCols(LOW);
  for(int i = 0 ; i < n ; i++) shiftCols(HIGH);
  for (int i = 0; i < ROWSIZE; i++) {
    outputCols();
    outputRows();
    delayMicroseconds(DELAYTIME);
    shiftRows(LOW);
  }
}

void playDiagonal(){
  int iter = 0;
  while (iter < COLSIZE){
    for(int k = 0 ;k < 10; k++){
      resetRows();
      shiftRows(HIGH);
      resetCols();
      for (int i = 0; i < ROWSIZE; i++) {
        resetCols();
        for (int j = COLSIZE - 1; j >= 0; j--) {
          if (i < iter && j < iter)
            shiftCols(HIGH);
        }
        outputCols();
        outputRows();
        delayMicroseconds(DELAYTIME);
        shiftRows(LOW);
      }
    }
    iter++;
  }
}

void writeShape(int shape[ROWSIZE][COLSIZE]) {
  resetRows();
  shiftRows(HIGH);
  for (int i = 0; i < ROWSIZE; i++) {
    resetCols();
    for (int j = COLSIZE - 1; j >= 0; j--) {
      shape[i][j] = shape[i][j]? 0 : 1;
      shiftCols(shape[i][j]);
    }
    outputCols();
    outputRows();
    delayMicroseconds(DELAYTIME);
    shiftRows(LOW);
  }
}