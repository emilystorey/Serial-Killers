#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h" /* derivative-specific definitions */
#include "playSong.h" 
#include "delay.h"

  
#define toggle 0x04   /* global definitions for note frequency */
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

interrupt 13 void speakerISR(void); //declare interrupt function 
unsigned int period;  //declare interrupt function 

//enter function definition
void playSong(unsigned int score[], unsigned int dur[], int x){
  
  //define varibales and ports to turn off the display 
  int j;
  DDRB = 0x00;
  DDRJ = 0x00;
  PTJ  = 0x00; 
           
  asm("sei");   // Disable all interrupts
  TSCR1 = 0x90; // Enable timer and fast flag clear	
  TSCR2 = 0x07; // Set prescaler to 64
  TIOS = 0x20;	
  TCTL1 = 0x04; 
  period = score[0];
	TIE = 0x20;	
  TC5 = TCNT + period;  	
 	EnableInterrupts;	
      			
      for(j = 0; j < x; j++){	  	  	 		  
       	    period = (score[j]);
       	    delay(dur[j]);	     	      	  		    	  		  			
      }
      	  
     TCTL1 = 0; 
  }


  interrupt 13 void speakerISR(){
          	TC5 = TC5 + period;
  }