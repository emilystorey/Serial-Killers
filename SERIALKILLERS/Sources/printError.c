// this function prints an error message to the serial port.

#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "printError.h"

void printError(void){

   // allocate space for the following strings     
  char end_of_string[3];
  char errorstring[34];

  int k, l; // declare variables for incrementing
    
  // define values to be used in error handling
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;

  //turn display off
  DDRB = 0x00;  
  DDRP = 0xFF;
  PTP  = 0xFF;
  
  EnableInterrupts;
  
  //print an error message to the serial
  strcpy(errorstring,"Input must start with L, S, or M"); 
   
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
            SCI1DRL = end_of_string[l];
       }
      
      
}