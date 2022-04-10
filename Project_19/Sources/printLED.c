#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "printLED.h"                   
  
void printLED(char parameter){
  char errorstring[200];
  char end_of_string[3];
  
  char valNum[9] = {'0', '1', '2', '3', '4', '5', '6', '7','8'};
  int  binary[8] = {1, 2, 4, 8, 16, 32, 64, 128}; 
  
  int isValid;
  int l;
  int i;
  int k;
  int paramNum; 
    
  DDRB = 0xFF;
  DDRJ = 0xFF;
  PTJ  = 0x00;    
  
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  EnableInterrupts;
  
  
  for (i = 0; i < 9; i++){
    if (parameter == valNum[i]){
      isValid = 1;  
    } else {
      isValid =0;
    }
  }
  
   
  if (isValid != 1){
    strcpy(errorstring,"Error: Parameter after L must be a number from 0-9");

      for (k = 0; k < 40; k++) {
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
    for (l = 0; l < 3; l++){
          while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
          }
          SCI1DRL = end_of_string[l]    ;
     }
  }

  paramNum = parameter - 48;
  if (paramNum != 0){
    PORTB = binary[paramNum-1];
  }
  
}

