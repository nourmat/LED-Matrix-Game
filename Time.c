#include "Time.h"

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
/*void systickInit(void(*fun)(void)){
  SysTickPeriodSet(480000);
  SysTickIntRegister(fun);
  SysTickIntEnable();
  SysTickEnable();
}*/