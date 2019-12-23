#include "Time.h"
//#include "driverlib/systick.h"

void timeinit(void){         
       NVIC_ST_CTRL_R=0;                               
       NVIC_ST_RELOAD_R = 0xF423FF;                    //reload value starts from 15,999,999
      
       NVIC_ST_CTRL_R=5;                               //SysTick Control: no interupt, internal clock, Enable 
}

//-----------------DELAYS--------------------
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


/*void delayMicroseconds(int dur){
  NVIC_ST_RELOAD_R = 0xF;                  //reload value starts from 15
  NVIC_ST_CURRENT_R=0;
  for (int i = 0; i < dur ;i++){
    while ((NVIC_ST_CTRL_R & 0x10000) == 0);
  }
}*/

void Timer0_init(){
    SYSCTL_RCGCTIMER_R |= 0x01;
    TIMER0_CTL_R = 0x0;                         /* STEP 1: disable Timer before initialization */
    TIMER0_CFG_R = 0x0;                         /* STEP 2: 32-bit individual Timer only works with prescaler*/
    TIMER0_TAMR_R = 0x01;                       /* STEP 3: Periodic down-counter only works in simulation */
                                                /* STEP 4: Optional configuration  is not needed */
}


void delayMicroseconds(int dur){
    TIMER0_TAILR_R = 16 * dur - 1;       /* STEP 5: Timer A interval load value register */
                                                /* STEP 6: Interrupt is not needed in this example */
    TIMER0_CTL_R |= 0x01;                       /* STEP 7: enable Timer A after initialization*/  
    
    while ((TIMER0_RIS_R & 0x1) == 0) ;  /* STEP 8: wait for TimerA timeout flag to set*/
          TIMER0_ICR_R = 0x1;    /*         clear the TimerA timeout flag*/
}

void delay(int dur){ // delay milli
    TIMER0_TAILR_R = 16000 * dur - 1;       /* STEP 5: Timer A interval load value register */
                                                /* STEP 6: Interrupt is not needed in this example */
    TIMER0_CTL_R |= 0x01;                       /* STEP 7: enable Timer A after initialization*/  
    
    while ((TIMER0_RIS_R & 0x1) == 0) ;  /* STEP 8: wait for TimerA timeout flag to set*/
          TIMER0_ICR_R = 0x1;    /*         clear the TimerA timeout flag*/
}

//sets upsystick for interrupts
void systickInit(int period){
  //NVIC_EN0_R |= ;
  /*SysTickPeriodSet(480000);
  SysTickIntRegister(fun);
  SysTickIntEnable();
  SysTickEnable();*/
  //long sr = StartCritical();
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = 0x07;
  __asm("CPSIE  I");           // Enable Interrupts Globally - Clears the I bit
  //EndCritical(sr);
}