// this function is used to contril the 7 segs, and takes an input 'parameter' 
// which dictates what to display. If the parameter is a hexidecimal then it 
// will be displayed, otherwise an error message will be sent to the serial. 

#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "print7seg.h" /* derivative-specific definitions */
#include "derivative.h"
     

void print7seg(char parameter){

 // allocate space for the following strings    
  char end_of_string[3];
  char errorstring[51];

  int k, l; // declare variables for incrementing
  
  // define values to be used in error handling
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;

  // turn on 7 SEGS and LEDs
  DDRB = 0xFF  ;
  DDRJ = 0xFF  ;
  DDRP = 0xFF  ;
  PTJ  = 0xFF  ;
  PTP  = 0x00  ;
   
  EnableInterrupts;
   
   //if parameter is a hexideximal character, display said character on the 7segs  
   if (parameter =='0') {  
        PORTB = 0xBF ;
         }
   else if (parameter=='1') {
         PORTB = 0x86 ;
          }
   else if (parameter=='2') {
         PORTB = 0xDB ;  
          }
    else if (parameter=='3') {
         PORTB = 0xCF ; 
          }
    else if (parameter=='4') {
         PORTB = 0xE6 ; 
          }
    else if (parameter=='5') {
         PORTB = 0xED ; 
          }
    else if (parameter=='6') {
         PORTB = 0xFD ; 
          }
    else if (parameter=='7') {
         PORTB = 0x87 ; 
          }
    else if (parameter=='8') {
         PORTB = 0xFF ; 
          }
    else if (parameter=='9') {
         PORTB = 0xEF ; 
          }
    else if (parameter=='A') {
         PORTB = 0xF7 ; 
          }
    else if (parameter=='B') {
         PORTB = 0xFC ; 
          }
    else if (parameter=='C') {
         PORTB = 0xB9 ; 
          }
    else if (parameter=='D') {
         PORTB = 0xDE ; 
          }
    else if (parameter=='E') {
         PORTB = 0xF9 ; 
          }
     else if (parameter=='F') {
         PORTB = 0xF1 ; 
          }
          
  else{  //the parameter is not a hexidecimal character
 
         //turn off the display
         DDRB = 0x00  ;
         DDRJ = 0x00  ;
         DDRP = 0x00  ;
     
         //print an error message to the serial
               
         strcpy(errorstring,"Parameter after S must be a hexidecimal character");
           
          for (k = 0; k < 49; k++) {   //cycle through each element of the string
      
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
}