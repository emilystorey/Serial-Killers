#include <hidef.h>     
#include "derivative.h"      
#include <stdlib.h>
#include <stdio.h>
#include "print7seg.h"
#include "playSong.h"
#include "printError.h"
#include "delay.h"
#include "checkIfPlaying.h"
#include "serialRegisters.h"
#include "buttonSetup.h"
#include "printthisshit.h"
#include "inputError.h"
#include "musicError.h"
#define toggle 0x04 // value to toggle OC5 pin

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

void musicError(void);
void inputError(void);
void serialRegisters(void);
void buttonSetup(void);
interrupt 21 void serialISR(void);
interrupt 25 void porthISR(void);
void exercise1(void) ;
void exercise2(void); 
void printLED(char);
void print7seg(char);  
void printError(void);
void delay(unsigned int time);
void playSong(unsigned int score[], unsigned int dur[], int x);
void checkIfPlaying(int playing);
void LEDError(void);
void printthisshit(char parameter);

int outputcount, inputcount,playing, stringdone, setting, j;
char inputstring[8];
char outputstring[8];
char end_of_string[3];
char errorstring[100];;
unsigned int i;
int b; 
            
void main() {
// Enter which exercise to demonstrate here:
                                  setting=1; 
//  HPRIO = 0xD4;
  buttonSetup();
  serialRegisters();
  
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
  outputcount=0;
  inputcount=0;
  strcpy(outputstring,"helloMe");
  end_of_string[0]=0x0A;
  end_of_string[1]=0x0d;
  end_of_string[2]=0x00;
  EnableInterrupts;
  
  for(;;);
}



// ENTER EXERCISE TWO DEMONSTRATION 
void exercise2(void){ 

  stringdone=0;
 
  EnableInterrupts;
  inputstring[2] = 0x0B;
  // Continously loop and check the serial until instructed otherwise  
  for(;;) {
    while(stringdone==0){
    
    } 
    
    if (inputstring[2] != 0x0B){
        inputError();
 
    
    }
    // If L is found, call on function PrintLED 
    else if (inputstring[0]=='L'){      
     printthisshit(inputstring[1]); 
     
    } 
  
     // If S is found, call on function print7seg 
    else if (inputstring[0]=='S'){
      print7seg(inputstring[1]);  
    }
    
    // If M is found, call on function playtone    
    else if (inputstring[0]=='M'){ 
    playing = 1;                     
      if(inputstring[1] == '1'){   
          unsigned int score[] = {G,ZZ,G,A,G,C,B,G,ZZ,G,A,G,D,C};
          unsigned int dur[]   = {40,15,25,80,80,80,160,40,15,25,80,80,80,160};
          int x =14;        
            
          checkIfPlaying(playing); 
          playSong(score,dur, x);
          playing = 0;    
          checkIfPlaying(playing);             
      } 
      else if(inputstring[1] == '2'){    
          unsigned int score[] = {GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,ZZ,GS,B,E,FS,GS};
          unsigned int dur[]   = {45,5,45,5,95,5,45,5,45,5,95,5,50,50,50,50,100};
          int x = 17;
          
          checkIfPlaying(playing);
          playSong(score, dur, x);
          playing = 0;    
          checkIfPlaying(playing); 
                    
      } 
      else{
      
        musicError();
      
      }                
   }
   
    // All other inputs are invalid, and function printerror is called 
   else{
   
    printError(); 
       
    }
    stringdone=0;
    inputstring[2] = 0x0B;
  }  
}


 
 

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



//button to print string
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