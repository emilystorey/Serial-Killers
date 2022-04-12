//  The input of this function is a parameter that is used to turn on an 
//  LED. The function checks if the input is a valid digit using a flag, and 
//  uses the results to either turn on the corresponding LED or produce an 
//  error message on the serial
    
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "PrintLED.h"

// declare error function
void ErrorLED(void);

void PrintLED (char parameter){
  
  int i, paramNum; //declare variables
  int isValid = 0; //assume input is incorrect 
  
  //declare and define arrays to compare to the input
  char valNum[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
  int binary[8] = {1, 2, 4, 8, 16, 32, 64, 128};
  
  //turn on the LEDS, and turn off the 7 Segs
  DDRB = 0xFF;
  DDRP = 0xFF;
  PTP  = 0xFF;

  //loop through valid inputs, which are single digits
  for (i = 0; i < 9; i++){
    //if the parameter is within these bounds, it is valid
    if (parameter == valNum[i]){
      isValid = 1;  
    }
  }  
  // print an error message if the input is invalid
  if (isValid == 0){
    ErrorLED();
   }
  
  
   paramNum = parameter - 48; //convert the parameter from ascii to integer
   
   if (paramNum != 0){
    PORTB = binary[paramNum-1]; //display the integer on the corresponding LED
   }
}


//this function displays an error if the parameter is invalid
void ErrorLED(void){

  // allocate space for the following strings    
  char end_of_string[3];
  char errorstring[42];

  int k, l;// declare variables for incrementing
  
  // turn off the display  
  DDRB = 0x00;  
  DDRP = 0xFF;
  PTP  = 0xFF;
  
   // define values to be used in error handling
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  
  strcpy(errorstring,"Parameter after L must be a single digit");
   
  for (k = 0; k < 40; k++) {
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

   