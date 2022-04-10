#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "printError.h"


void printError(void){

char end_of_string[3];
char errorstring[200];

  int k;
  int l;
  
  DDRJ = 0x00;
  PTJ =  0x00;
  DDRB = 0x00;
  DDRJ = 0x00;
  DDRP = 0x00;
  
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  EnableInterrupts;
  
  strcpy(errorstring,"Error:input must start with L,S, or M"); 
   
  for (k = 0; k < 36; k++) {
        // Wait for data to be ready
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }  
        //capital Z stops sending, can change
        if (errorstring[k] != 0x5A){
                   
        // Write to serial
        SCI1DRL = errorstring[k];
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
