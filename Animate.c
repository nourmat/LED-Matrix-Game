#include "Animate.h"
#include "IO.h"
#include "LEDMATRIX.h"
#include "Time.h"
#include "stdbool.h"
#include "stdio.h"

//IMPORTANT: all drawing should occur by changing the value of the int screen[8][16] matrix in main which will be moved into LEDMATRIX after debugging


void flash(){
    int *shape = getLED(); //TODO A function that returns the pointer to the 2D array
	int win = getWinner(); //TODO A function that returns the number of the winning player
	bool player1 = false, player2 = false; 
	char player1Shape = getP1Shape(), player2Shape = getP2Shape(); //TODO A function that returns the shape chosen by each player 
	if(win == 1)
	{
		player1 = true;
	}
	else if (win == 2){
		player2 = true;
	}
	int cnt = 0;
	while(1){
		if(player1)
		{
			if(player1Shape == 'R')
			{
				if(cnt == 0)
					shape = P1Rwin1;
				else
					shape = P1Rwin2;
			}
			else if(player1Shape == 'P')
			{
				if(cnt==0)
					shape = P1Pwin1;
				else
					shape = P1Pwin2;
			}
			else if(player1Shape == 'S')
			{
				if(cnt==0)
					shape = P1Swin1;
				else
					shape = P1Swin2;
			}
		}
		else if(player2)
		{	
			if(player2Shape == 'R')
			{
				if(cnt == 0)
					shape = P2RWin1;
				else
					shape = P2RWin2;
			}
			else if(player2Shape == 'P')
			{
				if(cnt==0)
					shape = P2PWin1;
				else
					shape = P2PWin2;
			}
			else if(player2Shape == 'S')
			{
				if(cnt==0)
					shape = P2SWin1;
				else
					shape = P2SWin2;
			}
		}
		else
		{
			if(player1Shape == 'R')
			{
				if(cnt == 0)
					shape = RTie1;
				else
					shape = RTie2;
			}
			else if(player1Shape == 'P')
			{
				if(cnt==0)
					shape = PTie1;
				else
					shape = PTie2;
			}
			else if(player1Shape == 'S')
			{
				if(cnt==0)
					shape = STie1;
				else
					shape = STie2;
			}
		}
		delay_milli(500);
		if(readButtons())
			break;
		cnt^1;
	}
}

void randomFlash(){
  srand(NVIC_ST_CURRENT_R);
  int c;
  while(1)
  {
    int *shape = getLED(); //TODO A function that returns the pointer to the 2D array
	c = rand() % 9;
	switch(c)
	{
		case 0:
		 shape = RandomShape1;
		break;
		case 1:
		 shape = RandomShape2;
		break;
		case 2:
		 shape = RandomShape3;
		break;
		case 3:
		 shape = RandomShape4;
		break;
		case 4:
		 shape = RandomShape5;
		break;
		case 5:
		 shape = RandomShape6;
		break;
		case 6:
		 shape = RandomShape7;
		break;
		case 7:
		 shape = RandomShape8;
		break;
		case 8:
		 shape = RandomShape9;
	}
	delay_milli(500);
    //draw any 2 random shapes
    //wait 0.5 seconds
    if(readButtons()){
      break;
    }
  
  }
}