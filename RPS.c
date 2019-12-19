#include "RPS.h"
#include "Animate.h"
#include "IO.h"
int winner = 0;// 0 for tie 1 for player 1 and 2 for player 2
char player1Shape = 'R';// R or P or S
char player2Shape;// R or P or S
void RPC(){
  winner = 0;
  player1Shape = 'R';
  player1Shape = 'R';
  enum States state = INIT;
  while(1){
    //call randomFlash() from Animate.h
    //switch case on input, update playershapes and advance state
    
  }
  //reaching here means a player won or a draw occured
  //update winner accordingly 0, 1 or 2
  //call flash() from animate.h
  
}


int getWinner(){return winner;}
char getP1Shape(){return player1Shape;}
char getP2Shape(){return player2Shape;}