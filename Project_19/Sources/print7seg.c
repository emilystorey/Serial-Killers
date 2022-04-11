#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "print7seg.h"

void print7seg(char parameter){

char end_of_string[3];
char errorstring[100];
end_of_string[0]=0x0A;
end_of_string[1]=0x0d;
end_of_string[2]=0x00;

   DDRB = 0xFF  ;
   DDRJ = 0xFF  ;
   DDRP = 0xFF  ;
   PTJ  = 0xFF  ;
   PTP  = 0x00  ;
   
EnableInterrupts;
     
   //if it's equal to null, or it;s above ort below 
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
          
     else{
     
     int k, l;
     DDRB = 0x00  ;
     DDRJ = 0x00  ;
     DDRP = 0x00  ;
           
     strcpy(errorstring,"Parameter after S must be a hexidecimal character");
       
      for (k = 0; k < 49; k++) {
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
              SCI1DRL = end_of_string[l]    ;
         }
    }

}