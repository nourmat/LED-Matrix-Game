#include "RPS.h"
#include "Animate.h"
#include "IO.h"

int winner = 0;// 0 for tie 1 for player 1 and 2 for player 2
char player1Shape = 'R';// R or P or S
char player2Shape;// R or P or S
enum States State = INIT;      /*-----------------Modified by nour PLEASE CHECK, There was an error, as using state in the functions below and State intialized in void RPC(), if not problem REMOVE ME----------------------*/ 

void RPC(){
  winner = 0;
  player1Shape = 'R';
  player2Shape = 'R';
  State = INIT;
  
  while(1){
    //call randomFlash() from Animate.h
    randomFlash();
    //switch case on input, update playershapes and advance state
    int input = readButtons();
    updatePlayer1((input & 0X7));
    updatePlayer2((input & 0x38));
    if(State==DONE)
      break;
  }
  //reaching here means a player won or a draw occured
  //update winner accordingly 0, 1 or 2
  if(player1Shape == player2Shape)
    winner=0;
  else if (player1Shape == 'R'){
    if (player2Shape=='P')
      winner = 2;
    else
      winner = 1;
  }else if (player1Shape == 'P'){
    if (player2Shape=='S')
      winner = 2;
    else
      winner = 1;
  }else if (player1Shape == 'S'){
    if (player2Shape=='R')
      winner = 2;
    else
      winner = 1;
  }

  //call flash() from animate.h
  flash();
  
}

int getWinner(){return winner;}
char getP1Shape(){return player1Shape;}
char getP2Shape(){return player2Shape;}
void updatePlayer1(int input){
    if(State==INIT | State==P2){
      switch (input){
        case 1:
          player1Shape = 'R';
          break;
        case 2:
          player1Shape = 'P';
          break;
        case 4:
          player1Shape = 'S';
          break;
      }
      if(input!=0)
        updateState(1);
    }
}
void updatePlayer2(int input){
    if(State==INIT | State==P1){
      switch (input){
        case 8:
          player2Shape = 'R';
          break;
        case 16:
          player2Shape = 'P';
          break;
        case 32:
          player2Shape = 'S';
          break;
      }
      if(input!=0)
        updateState(2);
    }
}
void updateState(int p){
  if(State==INIT){
    if(p==1)
      State = P1;
    else
      State = P2;
  }else if(State==P1){
    if(p==2)
      State == DONE;
  }else if(State==P2)
    if(p==1)
      State == DONE;
}