#include "Animate.h"
#include "IO.h"
#include "LEDMATRIX.h"
#include "Time.h"
#include "stdbool.h"
#include "stdio.h"
#include <stdlib.h>

//IMPORTANT: all drawing should occur by changing the value of the int screen[8][16] matrix in main which will be moved into LEDMATRIX after debugging

void cpyArr(int src[8][16], int dst[8][16])
{
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 16 ; j++)
			dst[i][j] = src[i][j];
}

void flash(){
    int **shape = getLED(); //TODO A function that returns the pointer to the 2D array
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
					cpyArr(P1Rwin1,shape);
				else
					cpyArr(P1Rwin2,shape);
			}
			else if(player1Shape == 'P')
			{
				if(cnt==0)
					cpyArr(P1Pwin1,shape);
				else
					cpyArr(P1Pwin2,shape);
			}
			else if(player1Shape == 'S')
			{
				if(cnt==0)
					cpyArr(P1Swin1,shape);
				else
					cpyArr(P1Swin2,shape);
			}
		}
		else if(player2)
		{	
			if(player2Shape == 'R')
			{
				if(cnt == 0)
					cpyArr(P2RWin1,shape);
				else
					cpyArr(P2RWin2,shape);
			}
			else if(player2Shape == 'P')
			{
				if(cnt==0)
					cpyArr(P2PWin1,shape);
				else
					cpyArr(P2PWin2,shape);
			}
			else if(player2Shape == 'S')
			{
				if(cnt==0)
					cpyArr(P2SWin1,shape);
				else
					cpyArr(P2SWin2,shape);
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
		cnt^=1;
	}
}

void randomFlash(){
  srand(NVIC_ST_CURRENT_R);
  int c;
  while(1)
  {
    int **shape = getLED(); //TODO A function that returns the pointer to the 2D array
	c = rand() % 9;
	switch(c)
	{
		case 0:
		 cpyArr(RandomShape1,shape);
		break;
		case 1:
		 cpyArr(RandomShape2,shape);
		break;
		case 2:
		 cpyArr(RandomShape3,shape);
		break;
		case 3:
		 cpyArr(RandomShape4,shape);
		break;
		case 4:
		 cpyArr(RandomShape5,shape);
		break;
		case 5:
		 cpyArr(RandomShape6,shape);
		break;
		case 6:
		 cpyArr(RandomShape7,shape);
		break;
		case 7:
		 cpyArr(RandomShape8,shape);
		break;
		case 8:
		 cpyArr(RandomShape9,shape);
	}
	delay_milli(500);
    //draw any 2 random shapes
    //wait 0.5 seconds
    if(readButtons()){
      break;
    }
  
  }
}