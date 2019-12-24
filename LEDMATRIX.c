#include "LEDMATRIX.h"
#include "Time.h"
int screen[ROWSIZE][COLSIZE] =
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*-------------------Timer1 for Delays-------------------------------*/

void Timer1_init(){
    SYSCTL_RCGCTIMER_R |= 0x02;
    TIMER1_CTL_R = 0x0;                         /* STEP 1: disable Timer before initialization */
    TIMER1_CFG_R = 0x0;                         /* STEP 2: 32-bit individual Timer only works with prescaler*/
    TIMER1_TAMR_R = 0x01;                       /* STEP 3: Periodic down-counter only works in simulation */
                                                /* STEP 4: Optional configuration  is not needed */
}

void delayMicroseconds1(int dur){
    TIMER1_TAILR_R = 16 * dur - 1;       /* STEP 5: Timer A interval load value register */
                                                /* STEP 6: Interrupt is not needed in this example */
    TIMER1_CTL_R |= 0x01;                       /* STEP 7: enable Timer A after initialization*/  
    
    while ((TIMER1_RIS_R & 0x1) == 0) ;  /* STEP 8: wait for TimerA timeout flag to set*/
          TIMER1_ICR_R = 0x1;    /*         clear the TimerA timeout flag*/
}

void delay1(int dur){ // delay milli
    TIMER1_TAILR_R = 16000 * dur - 1;       /* STEP 5: Timer A interval load value register */
                                                /* STEP 6: Interrupt is not needed in this example */
    TIMER1_CTL_R |= 0x01;                       /* STEP 7: enable Timer A after initialization*/  
    
    while ((TIMER1_RIS_R & 0x1) == 0) ;  /* STEP 8: wait for TimerA timeout flag to set*/
          TIMER1_ICR_R = 0x1;    /*         clear the TimerA timeout flag*/
}

/*-------------------Intitaliztion of ports-------------------------------*/

//int getLED(){return screen;}
void LED_init() {
  SYSCTL_RCGCGPIO_R |= LED_COL_CLOCK; //clock
  SYSCTL_RCGCGPIO_R |= LED_ROW_CLOCK;

  LED_COL_DEN |= (DataCol | LatchCol | ShiftCol); //enable
  LED_ROW_DEN |= (DataRow | LatchRow | ShiftRow);

  LED_COL_DIR |= (DataCol | LatchCol | ShiftCol); //direction
  LED_ROW_DIR |= (DataRow | LatchRow | ShiftRow);

  LED_COL_DATA &= ~(DataCol  | LatchCol | ShiftCol);  //data
  LED_ROW_DATA &= ~(DataRow | LatchRow | ShiftRow);  //data
  
  Timer1_init();
}

/*--------------------------------Functions To control the LED----------------------------*/

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
  delayMicroseconds1(PULSEDELAY);
  //pulse
  digitalWrite(&LED_ROW_DATA, ShiftRow, HIGH);
  delayMicroseconds1(PULSEDELAY);
  digitalWrite(&LED_ROW_DATA, ShiftRow, LOW);
  delayMicroseconds1(PULSEDELAY);
}

void shiftCols(int data) {
  digitalWrite(&LED_COL_DATA, LatchCol, LOW);
  //data = data ? 0 : 1;
  digitalWrite(&LED_COL_DATA, DataCol, data);
  delayMicroseconds1(PULSEDELAY);
  //pulse
  digitalWrite(&LED_COL_DATA, ShiftCol, HIGH);
  delayMicroseconds1(PULSEDELAY);
  digitalWrite(&LED_COL_DATA, ShiftCol, LOW);
  delayMicroseconds1(PULSEDELAY);
}

void outputRows() {
  //pusle
  digitalWrite(&LED_ROW_DATA, LatchRow, HIGH);
  delayMicroseconds1(LATCHPULSEDELAY );
  digitalWrite(&LED_ROW_DATA, LatchRow, LOW);
  delayMicroseconds1(LATCHPULSEDELAY );
}

void outputCols() {
  //pusle
  digitalWrite(&LED_COL_DATA, LatchCol, HIGH);
  delayMicroseconds1(LATCHPULSEDELAY);
  digitalWrite(&LED_COL_DATA, LatchCol, LOW);
  delayMicroseconds1(LATCHPULSEDELAY);
}

//TAKES MASK
void digitalWrite(volatile unsigned long *reg, int mask, int level) {
  if (level)
    *reg |= mask;
  else
    *reg &= ~ mask;
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
    delayMicroseconds1(DELAYTIME);
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
        delayMicroseconds1(DELAYTIME);
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
      //shape[i][j] = shape[i][j]? 0 : 1;
      shiftCols(shape[i][j] ^ 1);
    }
    outputCols();
    outputRows();
    delayMicroseconds1(DELAYTIME);
    shiftRows(LOW);
  }
}

/*--------------------------------Functions To control the Screen Array----------------------------*/

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

void cpyArrToScreen(int src[ROWSIZE][COLSIZE])
{
	for(int i = 0 ; i < ROWSIZE ; i++)
		for(int j = 0 ; j < COLSIZE; j++)
			screen[i][j] = src[i][j];
}
/*--------------------------------Refresh Function to be used in the main--------------------*/
void refresh(){
  writeShape(screen);
}
