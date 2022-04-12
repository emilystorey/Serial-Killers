#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>
#include "buttonSetup.h"



void buttonSetup(void) {
  DDRH = 0x00; // Port H as input
  PIEH = 0x01; // Enable interrupts for PTH0
	PPSH = 0x00; // Interrupt happens on falling edge  
}
