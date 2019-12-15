#include "keypad.h"

const int keypadRows[4] = {R0,R1,R2,R3};
const int keypadCols[4] = {C0,C1,C2,C3};

const unsigned char keymap[4][4] = {
        { '1', '2', '3', 'A'},
        { '4', '5', '6', 'B'},
        { '7', '8', '9', 'C'},
        { '*', '0', '#', 'D'},
    };


void keypad_init(){
    SYSCTL_RCGCGPIO_R |= keypad_COL_CLOCK; //clock
    SYSCTL_RCGCGPIO_R |= keypad_ROW_CLOCK;
    
     keypad_COL_DEN |= (C0 | C1 | C2 | C3); //enable
     keypad_ROW_DEN |= (R0 | R1 | R2 | R3);
     
     keypad_COL_DIR &=~(C0 | C1 | C2 | C3); //direction
     keypad_ROW_DIR |= (R0 | R1 | R2 | R3);
     
     keypad_ROW_DATA &=~(R0 | R1 | R2 | R3);    //data
        
     keypad_COL_PUR |= (C0 | C1 | C2 | C3);        //pull up resistor
     
     keypad_ROW_ODR |= (R0 | R1 | R2 | R3);          //Open Drain Output
}

char getKeyPressed (){
    for (int i = 0 ; i < 4 ; i++){               
       keypad_ROW_DATA |=(R0 | R1 | R2 | R3);                         
       keypad_ROW_DATA &=~keypadRows[i];                      //ground current row
       
       if ((keypad_COL_DATA & (C0 | C1 | C2 | C3)) != (C0 | C1 | C2 | C3)){  //check if a button is pressed
         for (int j = 0 ; j < 4 ; j++){                           //loop on each col to check which button was pressed
           if ((keypad_COL_DATA & keypadCols[j]) == 0)          
             return keymap[i][j];
         }
       }
    }
  //}
  return 1;
}

int isKeyPressed(){
  keypad_ROW_DATA &=~(R0 | R1 | R2 | R3);
  return ((keypad_COL_DATA & (C0 | C1 | C2 | C3)) != (C0 | C1 | C2 | C3));  //check if a button is pressed
}