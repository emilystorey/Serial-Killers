//This function takes an input 'time', which is cycled through and multiplied by 
//20000 to alter the duration of the frequency being played and create rhythm.

#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"
#include "playSong.h"



void delay(unsigned int time){

int i, z; //define variables for incrementing 

    for(i=0; i < time; i++)  //loop through the time given
    
      for(z=0; z < 20000; z++); //5 ms
 }