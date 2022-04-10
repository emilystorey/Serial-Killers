#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "delay_ms.h"
#include "happyBirthday.h"
#include <stdio.h>


void delay_ms(unsigned int time){
int i; 
int z;
    for(i=0; i < time; i++)
      for(z=0; z < 20000; z++);
 }