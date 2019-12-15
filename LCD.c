#include "LCD.h"

void LCD_init(){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //CLOCK
    SYSCTL_RCGCGPIO_R |= LCD_CTRL_CLOCK;
    
    GPIO_PORTB_DEN_R |= (0xFFU);  //ENABLE
    GPIO_PORTA_DEN_R |= (RS | EN);
   
    GPIO_PORTB_DIR_R |= (0xFFU);                  //write to LCD. DIRECTION
    GPIO_PORTA_DIR_R |= (RS | EN);
    
    GPIO_PORTB_DATA_R &= ~(0xFFU);                  //turn off all lights
    GPIO_PORTA_DATA_R &= ~(RS | EN);                 //turn off enable, rs
    
    LCD_start();
}

void LCD_command(unsigned char command){
  GPIO_PORTA_DATA_R &= ~(RS);                           //turn off rs
  GPIO_PORTB_DATA_R = command;
  GPIO_PORTA_DATA_R |= (EN);                            //turn off en
  delay_micro_LCD(1);
  GPIO_PORTA_DATA_R = 0;
  if(command < 4)
    delay_milli_LCD(2);
  else
    delay_micro_LCD(50);
}
void LCD_start(){
  delay_milli_LCD(20);
  LCD_command(0x30);
  delay_milli_LCD(5);
  LCD_command(0x30);		                        // command 0x30 = Wake up #2
  delay_micro_LCD(100);			        // must wait 100us, busy flag not available
  LCD_command(0x30);		                        // command 0x30 = Wake up #3
  delay_micro_LCD(100);			        // must wait 100us, busy flag not available
  // Prepare LCD Operation and Function  
  LCD_command(0x38);                                    /* set 8-bit data, 2-line, 5x7 font */
  LCD_command(0x06);                                    /* move cursor right */
  LCD_command(0x01);                                    /* clear screen, move cursor to home */
  LCD_command(0x0F);                                    /* turn on display, cursor blinking */

}
void LCD_data(unsigned char data){
  GPIO_PORTA_DATA_R |= (RS);
  GPIO_PORTB_DATA_R = data;                             //write data
  GPIO_PORTA_DATA_R |= (EN);                            //turn on enable
  delay_micro_LCD(1);
  GPIO_PORTA_DATA_R &= ~(EN | RS);
  delay_micro_LCD(40);
  LCD_command(6);                                       //increment curser
}

void LCD_writeNumber(int index){
  LCD_command(1);                                       //clear display 
  LCD_command(2);                                       //return curser
  char buffer [20];
  snprintf(buffer,sizeof(buffer),"%d",index);
    for(int j = 0;; j++){
      if(buffer[j] == 0)break;
      LCD_data(buffer[j]);
    }
}

void LCD_writeString(char buffer[]){
  LCD_command(1);                                       //clear display 
  LCD_command(2);                                       //return curser
  
    for(int j = 0;; j++){
      if(buffer[j] == 0)break;
      LCD_data(buffer[j]);
    }
}

void LCD_deleteChar(){
  LCD_command(0x10); //decrement cursor
  LCD_data(' '); //write space char 
  LCD_command(0x10); //decrement again as LCD_data increment implcitly
}

void LCD_clear(){
  LCD_command(1);                                       //clear display 
  LCD_command(2);                                       //return curser
}

void delay_micro_LCD(int dur){                         //in microsecond
  volatile int cnt = 30 * dur;
  while(cnt--);
}
void delay_milli_LCD(int dur){                         //in millisecond       
  delay_micro_LCD(1000 * dur);
}