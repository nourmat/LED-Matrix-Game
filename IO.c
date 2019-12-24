#include "IO.h"
#include "tm4c123gh6pm.h"

void init_port_e(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    GPIO_PORTE_DEN_R |= 0x3fU;      
    GPIO_PORTE_DIR_R &= ~(0x3fU);
    GPIO_PORTE_PDR_R |= (0x3fU);
}

/*
returns a binary mask of all the pressed buttons by the user
through all 6 pins of port e
*/
int readButtons(){
  return GPIO_PORTE_DATA_R & (0x3fU);
}