#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "serialRegisters.h"                   


void serialRegisters(void){
  // Set baud rate to 9600
  SCI1BDL = 0x9C;
  SCI1BDH = 0;
  
  SCI1CR1 = 0;
  
  // 2C = 0010110, Enable receive interrupt, transmit, receive
  SCI1CR2 = SCI1CR2_RE_MASK | SCI1CR2_TE_MASK |SCI1CR2_RIE_MASK;
}
