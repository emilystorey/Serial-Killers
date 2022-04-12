//this function takes 3 inputs: an array of frequencies, an array of durations, and 
//and length x. The function initialises the speaker of the dragon board, and uses 
//these input values to produce a song. Other functions inclduing delay and speakerISR are 
// called in this function to creat rhythm and sound respectively.  


#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "playSong.h" 
#include "delay.h"
  
#define toggle 0x04 /* define global variables for note frequencies */
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


interrupt 13 void speakerISR(void);  //declare speaker interrupt 
unsigned int period; //declare variable for the function and interupt 

void playSong(unsigned int score[], unsigned int dur[], int x){
  //declare varibles and turn off display 
      int j; 
      DDRB = 0x00;
      DDRJ = 0x00;
      PTJ  = 0x00; 
       
      asm("sei");         // Enable timer and fast flag clear
      TSCR1 = 0x90;       // Enable timer and fast flag clear	
      TSCR2 = 0x07;       // Set prescaler to 64
      TIOS = 0x20;	      // Choose output compare for channel 5	
     	TCTL1 = toggle;     // Toggle upon successful output compare 
     	period = score[0];  // Start with first note in the song
     	TIE = 0x20;	        // Enable interrupts for timer 5
      TC5 = TCNT + period;// Set first output compare to happen 	
     	EnableInterrupts;	
      
      //cycle through each char in the score and duration arrays 	  	 		  			
      for(j = 0; j < x; j++){	 
       	    period = (score[j]); //the period is the curent frequency value
       	    delay(dur[j]);	     //call delay function for current duration	      	  		    	  		  			
      }
      	  
     TCTL1 = 0;  //turn off speaker once song is done
  }


  interrupt 13 void speakerISR(){
          	TC5 = TC5 + period; // add the current period  
  }