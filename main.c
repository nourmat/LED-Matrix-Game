#include "LEDMATRIX.h"
//int** screen;//screen is the new name for shape2

// int shape2[8][16] =
// {
//   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
//   {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
//   {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
//   {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//   {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
// };

// int subshape1[8][8] = 
// { {1, 0, 0, 0, 0, 0, 0, 1},
//   {0, 1, 0, 0, 0, 0, 1, 0},
//   {0, 0, 1, 0, 0, 1, 0, 0},
//   {0, 0, 0, 1, 1, 0, 0, 0},
//   {0, 0, 0, 1, 1, 0, 0, 0},
//   {0, 0, 1, 0, 0, 1, 0, 0},
//   {0, 1, 0, 0, 0, 0, 1, 0},
//   {1, 0, 0, 0, 0, 0, 0, 1}};

// int subshape2[8][8] = 
// { {1, 0, 0, 0, 0, 0, 0, 1},
//   {0, 1, 0, 0, 0, 0, 1, 0},
//   {0, 0, 1, 0, 0, 1, 0, 0},
//   {0, 0, 0, 1, 1, 0, 0, 0},
//   {0, 0, 0, 1, 1, 0, 0, 0},
//   {0, 0, 1, 0, 0, 1, 0, 0},
//   {0, 1, 0, 0, 0, 0, 1, 0},
//   {1, 0, 0, 0, 0, 0, 0, 1}};

void SysTick_Handler();

int main()
{
  LED_init();
  systickInit(SysTick_Handler);
   
   while(1){
     //resetRows();
     //resetCols();
     //assignBlockArray(subshape1,shape2,0,0);
    //writeShape(shape2);
     //writeAllExceptCol(2);
     
     //RPC() this should be the only function written here
     //TODO FOR testing purposes, remove to integrate project
     break;
     //RPC()
   }
  return 0;
}


void SysTick_Handler(){
  refresh();
}
