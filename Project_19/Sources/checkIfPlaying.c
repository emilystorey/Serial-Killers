#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "checkIfPlaying.h"
#include <stdio.h>


void checkIfPlaying(int playing){

char end_of_string[3];
char errorstring[100];

  int k;
  int l;
  int x;
  DDRJ = 0xFF;
  PTJ = 0xFF;
  
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  EnableInterrupts;
  
  if (playing == 0){ 
   strcpy(errorstring,"I'm ready to recieve a new song or command!"); 
   x = 43;
  }
  
  if (playing == 1){
    strcpy(errorstring,"I hope you like the song i'm playing!");
    x = 37; 
  }
   
  for (k = 0; k < x; k++) {
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
        for (l=0;l<3;l++) {
              while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
              }
              SCI1DRL = end_of_string[l]  ;
         }
}