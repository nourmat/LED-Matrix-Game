#include "Animate.h"
#include "IO.h"
#include "LEDMATRIX.h"
//IMPORTANT: all drawing should occur by changing the value of the shape2 matrix in main which will be moved into LEDMATRIX after debugging

void flash(){
  while(1){
    
    //draw black
    //wait 0.5 seconds
    //draw real shape
    //wait 0.5 seconds
    
    if(readButtons()){
      break;
    }
  }
}

void randomFlash(){
  while(1){
    //draw any 2 random shapes
    //wait 0.5 seconds
    if(readButtons()){
      break;
    }
  
  }
}