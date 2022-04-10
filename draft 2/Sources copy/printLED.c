#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "printLED.h"                   
#include "LEDError.h"

  
void printLED(char parameter){

  char valNum[9] = {'0', '1', '2', '3', '4', '5', '6', '7','8'};
  int  binary[8] = {1, 2, 4, 8, 16, 32, 64, 128}; 
  
  int isValid = 0;
  int i;
  int paramNum; 
    
  DDRB = 0xFF;  
  DDRP = 0xFF;
  PTP = 0xFF;
  
  for (i = 0; i < 9; i++){
    if (parameter == valNum[i]){
      isValid = 1;  
     } 
  }
  
   
  if (isValid == 0){
  
  //DDRB = 0x00;  
  //DDRP = 0xFF;
  //PTP  = 0xFF;
   LEDError() ;
  }

  paramNum = parameter - 48;
  if (paramNum != 0){
    PORTB = binary[paramNum-1];
  }
  
}