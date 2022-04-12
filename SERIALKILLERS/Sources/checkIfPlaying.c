//The input of this function is a flag which represents the status of a song 
//being played. This function will output a message to the serial port depending
//on this flag.

#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "checkIfPlaying.h"

void checkIfPlaying(int playing){

 // allocate space for the following strings    
  char end_of_string[3];
  char errorstring[45];

  int k, l, x; // declare variables for incrementing
  
  // turn off the display  
  DDRB = 0x00;  
  DDRP = 0xFF;
  PTP  = 0xFF;
  
   // define values to be used in error handling
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  EnableInterrupts;
  
  //if flag is zero, the song has just ended
  if (playing == 0){ 
   strcpy(errorstring,"I'm ready to recieve a new song or command!"); 
   x = 43;
  }
  
  //if the flag is 1, the song has just started
  if (playing == 1){
    strcpy(errorstring,"I hope you like the song i'm playing!");
    x = 37; 
  }
   
  for (k = 0; k < x; k++) { //cycle through each element of the string
   
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