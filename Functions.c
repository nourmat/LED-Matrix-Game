#include "Functions.h"
#include "Constants.h"
#include "LCD.h"
#include "keypad.h"
#include <stdio.h>
#include <string.h>


//unsigned char* names[] = {"Sameh","Abdallah","Youssef","Nour","Nagy"};

void init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;        //CLOCK
       
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;              //unlock
	GPIO_PORTF_CR_R |= 0x01f;                       //enable commit on all of f
        
        //GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;              //unlock
	//GPIO_PORTA_CR_R |= 0x01f;                       //enable commit on all of f

        GPIO_PORTF_DEN_R |= (SW1 | SW2 | RED_LED);               //enable
        
        GPIO_PORTF_DIR_R &= ~(SW1 | SW2);               //read switch
        GPIO_PORTF_DIR_R |= RED_LED;
	
        GPIO_PORTF_DATA_R &=~RED_LED;
        
        GPIO_PORTF_PUR_R |= (SW1 | SW2);                //pullup resistor for the switches
        
        NVIC_ST_CTRL_R=0;                               
        NVIC_ST_RELOAD_R = 0xF423FF;                    //reload value starts from 15,999,999
      
        NVIC_ST_CTRL_R=5;                               //SysTick Control: no interupt, internal clock, Enable 
       
        keypad_init();
        LCD_init();
}

int buttons_pressed(void)
{
	int bt1 = (GPIO_PORTF_DATA_R & SW1);            //zero if switch is on
	int bt2 = (GPIO_PORTF_DATA_R & SW2);            //zero if switch is on
	if(bt1 == 0 || bt2 == 0)
	{
          timer_delay_milli(25); 
          if(bt1 == 0 && bt2 == 0){                       //both switches are pressed
                          return 0;
                  }
                  else if(bt2 == 0){                      //button 2 is pressed increment
                          return 1;
                  }
                  else if(bt1 == 0){                      // button 1 is pressed decrement
                          return 2;
                  }
         }      
        return -1;
}

void turnRedLedOn(){
 GPIO_PORTF_DATA_R |= RED_LED;
}

void turnRedLedOff(){
 GPIO_PORTF_DATA_R &=~ RED_LED; 
}

int getNum()
{
    int i = 0;
    unsigned char buffer[20];
    
    while (i < 5){
      //-------------Switch--------------
      int sw = buttons_pressed();
      if (sw == 1 && i > 0){ //start counting only if there is a value
        buffer[i] = 0;
        break;
      }
      else if (sw == 2){ //clear, start lisiting for new input
         i = 0;
         LCD_clear();
      }
      
     //-------------KeyPad--------------
      if (isKeyPressed()){
          buffer[i] = getKeyPressed();
          delay_milli(200);
          if (buffer[i] != 1 && buffer[i] != 'A' && buffer[i] != 'B' && buffer[i] != 'C' && buffer[i] != 'D'){
            if (buffer[i] == '*'){ //start timer
              buffer[i] = 0;
              break;
            }else if (buffer[i] == '#' && i > 0){ //delete char
                i--;
                LCD_deleteChar();
            }else if (i < 4 && buffer[i] != '#' && buffer[i] != '*'){ //add number to buffer
                if (i == 0) LCD_clear(); //clear when start entering number 
                LCD_data(buffer[i]);
                i++;
            }
        }
      }
    }
  int  num;
  sscanf(buffer, "%d", &num);            //turn char* to decimal 
  return num;
}

//-----------------DELAYS--------------------
void timer_delay_micro(int dur)                         //in microsecond
{       
  volatile int cnt = 30 * dur;
  while(cnt--);
}
void timer_delay_milli(int dur)                         //in millisecond
{       
  timer_delay_micro(1000 * dur);
}

void delaySec()
{
  NVIC_ST_RELOAD_R = 0xF423FF;                    //reload value starts from 15,999,999
  NVIC_ST_CURRENT_R=0;
  while ((NVIC_ST_CTRL_R & 0x10000) == 0);
}


void delay_milli(int dur){
  NVIC_ST_RELOAD_R = 0x3E7F;                  //reload value starts from 15,999
  for (int i = 0; i < dur ;i ++){
    //NVIC_ST_CURRENT_R=0;
    while ((NVIC_ST_CTRL_R & 0x10000) == 0);
  }
}