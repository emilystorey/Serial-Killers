
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "printMessage.h"


void printMessage(char array[], char memory[]){
  
  char end_of_string[3];

  int k, l;
  
  DDRB = 0x00;  
  DDRP = 0xFF;
  PTP  = 0xFF;
    
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  EnableInterrupts;
  
  strcpy(memory, array); 
   
  for (k = 0; k < strlen(array); k++) {
        // Wait for data to be ready
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }  
        //capital Z stops sending, can change
        if (memory[k] != 0x5A){
                   
        // Write to serial
        SCI1DRL = memory[k];
        } 
        
        //exit if end b=variable is present
        else {
        break;
        }
  } 
  
  // bit 0 of PIFH will be set to 1 when interrupt happens
  PIFH = 0x01; // clears flag of bit 0 (activated because of the falling edge)


//move down a line and to left
  for (l=0;l<3;l++){
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }
        SCI1DRL = end_of_string[l]    ;
  }
     
}

