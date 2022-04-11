#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "delay.h"
#include "playSong.h"



void delay(unsigned int time){
int i, z;
    for(i=0; i < time; i++)
      for(z=0; z < 20000; z++);
 }