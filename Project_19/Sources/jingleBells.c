
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "jingleBells.h"
#include "delay_ms.h"
#include <stdio.h>
     
#define toggle 0x04 // value to toggle OC5 pin

#define E 246.244
#define F 232.4231
#define FS 232.4231
#define G 207.0659
#define GS 195.4439
#define A 184.4746
#define B 164.348
#define C 155.124
#define CS 146.4176
#define D 138.1997
#define DS 130.4171
#define ZZ 20 

interrupt 13 void speakerISR(void);

void jingleBells(void){

     unsigned int period2;
     unsigned int score[] = {GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,B,E,FS,GS};
     unsigned int dur[]   = {45,5,45,5,95,5,45,5,45,5,95,5,50,50,50,50,100};
		
		 int j;
		 
    asm("sei");
    TSCR1 = 0x90; 	
    TSCR2 = 0x07;
    TIOS = 0x20;	
   	TCTL1 = 0x04; 
   	period2 = score[0];
   	TIE = 0x20;	
    TC5 = TCNT + period2;  	
   	EnableInterrupts;	
    			
    for(j = 0; j < 18; j++){	  	  	 		  
     	    period2 = (score[j]);
     	    delay_ms(dur[j]);	     	      	  		    	  		  			
    }
    	  
   TCTL1 = 0; 
}


interrupt 13 void speakerISR2(){
     unsigned int period2;
        	TC5 = TC5 + period2;
}
  
 