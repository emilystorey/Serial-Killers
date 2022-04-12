 /* common defines and macros */ 
#include <hidef.h>       
#include <stdlib.h>
#include <stdio.h>

/* include all definitions */
#include "derivative.h"   
#include "PrintLED.h"
#include "print7seg.h"
#include "playSong.h"
#include "checkIfPlaying.h"
#include "serialRegisters.h"
#include "buttonSetup.h"
#include "musicError.h"
#include "inputError.h"
#include "printError.h"

/* define global variables for note frequencies */
#define E 246.244   
#define F 232.4231
#define FS 219.3781
#define G 207.0659
#define GS 195.4439
#define A 184.4746
#define B 164.348
#define C 155.124
#define CS 146.4176
#define D 138.1997
#define DS 130.4171
#define ZZ 20 

 /* declare all functions and interrupts */
interrupt 21 void serialISR(void);
interrupt 25 void porthISR(void);
void exercise1(void) ;
void exercise2(void);  
void serialRegisters(void);
void buttonSetup(void);
void PrintLED(char);
void print7seg(char); 
void playSong(unsigned int score[], unsigned int dur[], int x);
void checkIfPlaying(int playing); 
void printError(void);
void inputError(void);
void musicError(void);

/* declare key variables and arrays */
int outputcount, inputcount,playing, stringdone, setting, j;
char inputstring[8];
char outputstring[8];
char end_of_string[3];
char errorstring[100];;
unsigned int i;




// ! ENTER MAIN ! //           
void main() {

  // Enter which exercise to demonstrate here (1 or 2):
                                    setting=2; 
  //  HPRIO = 0xD4;

    buttonSetup(); //call function to set up button on dragon board
    serialRegisters(); //call function to initialise the serial
    
    // Demonstrate exercise 1
    if (setting==1){
      exercise1();
    }
    
    // Demonstrate exercise 2
    if (setting==2){  
      exercise2();
    }
}


// ENTER EXERCISE ONE DEMONSTRATION 
void exercise1(void){

  //define variables
  outputcount=0;
  inputcount=0;
  
  // write a string to outputstring
  strcpy(outputstring,"helloMe");
  
  // define values to be used in messaging the serial port
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  EnableInterrupts;
  
  //continuously loop
  for(;;);
}



// ENTER EXERCISE TWO DEMONSTRATION 
void exercise2(void){ 

  stringdone=0; //define a flag to end or continue the loop
  
  inputstring[2] = 0x0B; //define the 3rd value of the input string for error handling 
 
  EnableInterrupts;
 
 
  // Continously loop and check the serial until instructed otherwise  
  for(;;) {
  
    while(stringdone==0){
    } 
    
    //if the 3rd value has changed, too many values have been entered  
    if (inputstring[2] != 0x0B){ 
        inputError(); //call function to display error
    }
    
    // If L is found, call on function PrintLED 
    else if (inputstring[0]=='L'){      
     PrintLED(inputstring[1]); 
     
    } 
  
     // If S is found, call on function print7seg 
    else if (inputstring[0]=='S'){
      print7seg(inputstring[1]);  
    }
    
    // If M is found
    else if (inputstring[0]=='M'){ 
    
       playing = 1; //define a flag to decipher the status of the song
      
      // define values to play Happy Birthday if parameter 1 is selected                   
      if(inputstring[1] == '1'){   
          unsigned int score[] = {G,ZZ,G,A,G,C,B,G,ZZ,G,A,G,D,C};
          unsigned int dur[]   = {40,15,25,80,80,80,160,40,15,25,80,80,80,160};
          int x =14;               //the length of the arrays is 14       
            
          checkIfPlaying(playing); //check status and message the serial port
          playSong(score,dur, x);  //call function to play the chosen song
          playing = 0;             //song has finished playing 
          checkIfPlaying(playing); //check status and message the serial port            
      } 
      // define values to play Jingle Bells if parameter 2 is selected
      else if(inputstring[1] == '2'){    
          unsigned int score[] = {GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,B,E,FS,GS};
          unsigned int dur[]   = {45,5,45,5,95,5,45,5,45,5,95,5,50,50,50,50,100};
          int x = 17;              //the length of the arrays is 17   
          
          checkIfPlaying(playing); //check status and message the serial port
          playSong(score, dur, x); //call function to play the chosen song
          playing = 0;             //song has finished playing   
          checkIfPlaying(playing); //check status and message the serial port
                    
      }
      // any other parameter is invalid 
      else{    
         musicError(); //display error message to the serial 
      }                
   }
   
    // All other inputs are invalid, display error message to the serial 
   else{
   
    printError();
    
    }
    
    stringdone=0;           //continue looping
    inputstring[2] = 0x0B;  //reset 3rd value of input for error testing
  }  
}


 
 

// SERIAL INTERUP //
interrupt 21 void serialISR(void) {
  
  while((SCI1SR1 & SCI1SR1_RDRF_MASK) == 0){
  }
  //press enter to stop recieving 
  if (SCI1DRL != 0x0D) {
    
    //saves the input to current string counter
    inputstring[outputcount] = SCI1DRL;
    outputcount=outputcount+1;
  } 
  
  //if enter is pressed, dont allow the string to recieve anymore info put disabling terminal recieving
  else {
    if(setting==1){
      
      SCI1CR2 =  SCI1CR2_RE_MASK | SCI1CR2_TE_MASK; //disable recieving 
    }
   stringdone=1;
   outputcount=0;
  }
  
}



// PORT H INTERRUPT //
interrupt 25 void porthISR(void) {
  int k;
  int l; 
  for (k = 0; k < 8; k++) {
        // Wait for data to be ready
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }  
        
        //capital Z stops sending, can change
        if (errorstring[k] != 0x5A){
          
          
        // Write to serial
        SCI1DRL = outputstring[k];
        } 
        
        //exit if end b=variable is present
        else {
        break;
        }
  } 
    
 
  // bit 0 of PIFH will be set to 1 when interrupt happens
  PIFH = 0x01; // clears flag of bit 0 (activated because of the falling edge)


//move down a line and to left
  for (l=0;l<3;l++){
        while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){
        }
        SCI1DRL = end_of_string[l]    ;
  }
}