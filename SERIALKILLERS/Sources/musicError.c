// This function is used to display an error message when the parameter
// for the music command is incorrect.When called, it will display a
// message to the serial port.

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "musicError.h"

void musicError(void){
  
  // allocate space for the following strings    
  char end_of_string[3];
  char errorstring[34];

  int k, l;// declare variables for incrementing
  
  // turn off the display  
  DDRB = 0x00;  
  DDRP = 0xFF;
  PTP  = 0xFF;
  
   // define values to be used in error handling
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  EnableInterrupts;
  
    //copy a message to the predefined string
  strcpy(errorstring,"Parameter after M must be 1 or 2"); 
   
  for (k = 0; k < 32; k++) {  //cycle through each element of the string
       while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){  // Wait for data to be ready
       }  
       if (errorstring[k] != 0x5A){  // capital Z stops sending
              
       SCI1DRL = errorstring[k]; // Write the string to serial
       }  
       else {
          break;
       }
  } 
      
   // bit 0 of PIFH will be set to 1 when interrupt happens
   PIFH = 0x01; // clears flag of bit 0 

   for (l=0;l<3;l++) { //move down a line and to left in the terminal
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }
        SCI1DRL = end_of_string[l]    ;
   }
  
}