#include "LEDMATRIX.h"
#include "IO.h"
#include "Time.h"
#include "Animate.h"
#include "RPS.h"

void init(){
  LED_init();
  systickInit(360000);
  init_port_e();
  Timer0_init();
}
int main()
{
  
  //https://youtu.be/saoIozMwMbc
  init();
   while(1){
      RPC();
      //delay_milli(3000);
   }
}


void SysTick_Handler(){
  refresh();
}
