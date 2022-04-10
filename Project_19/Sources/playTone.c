#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "playTone.h"
#include "delay_ms.h"
#include <stdio.h>


void playTone(char parameter){
int delay = 500;
int HIFREQ = 1250 ;
int LOWFREQ = 5000;  
int period;

  // Disable all interrupts
	asm("sei");
	// Enable timer and fast flag clear
	TSCR1 = 0x90; 
	// Set prescaler to 8
	TSCR2 = 0x03;	
	// Choose output compare for channel 5
	TIOS = 0x20;	
	// Toggle upon successful output compare 
	TCTL1 = 0x04; 
	// Start with high frequency
	period = HIFREQ;
	// Enable interrupts for timer 5
	TIE = 0x20;	
	// Set first output compare to happen
	TC5 = TCNT + period;
	EnableInterrupts;	
	// Don't leave this loop
	for(;;)	{
	  delay_ms(delay);     // Wait half a second
	  period = LOWFREQ;    // Switch to low frequency
	  delay_ms(delay);     // Wait half a second
	  period = HIFREQ;     // Switch to high frequency
	}
}

