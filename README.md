
# Tron 2 Assignment 2
## About our code
This assignment involved the development of individual modules in C code to program the HCS12 microcontroller. Each module was developed with the intention of integration to perform several key functions. These key concepts include:
- Storing serial inputs and Sending output buffer
- Parsing serial commands
- Playing a song on the speaker

Our group decided we would create each module with a specific set of inputs and outputs in order to increase functionality and usage. We have also thoroughly commented on our code to ensure readability and understanding of the code between ourselves.


## Testing Procedures 
Most of our testing procedures were performed using the inbuilt debugging features in CodeWarrior. These testing methods include:

- Single Line Stepping: Using the single line stepping feature allows for clear inspection of memory and the functionality of each line of code
- Breakpoints: Using breakpoints throughout the code allowed us to see the functionality of each module of code


## Group Contributions
Majority of our code and debugging was worked on together during labs and zoom sessions. 

**Luke**: 
Luke worked on the first section, creating an interface with the serial ports and creating integral modules to be used in the later parts. He also worked on the second section and README file.

 **Emily**: 
 Emily worked on the third section, creating songs to be played, as well as, working on some functions for the second section. Emily also modularised our code, creating individual files and functions for each section.
 
 **Tara**: 
 Tara worked on the second section, working with sections from the rest of the program to create new functions. Tara also worked on the README file.


## Exercise 1 

### High level information
This exercise uses the serial interface to be able to store and send an array of 8bit characters to and from the HCS12. It uses a serial interrupt to receive data from the terminal and port H interrupt to communicate that the device needs to output an array to the terminal. The end of the string can be communicated by a changing variable.

### Instructions
The user must first change the setting in the main to equal 1 to enable the first exercise. The user can then enter a string of characters and press enter to signify the end of the string, and this will be saved in the input string. The user can also press the last button on the HCS dragon board to send a pre saved string to the terminal. The user can change the test variable which will end the string if present in interrupt 25.

### Discussion 
How can you buffer the data (for receive and transmit)?
At the current setting, we can buffer 8 characters to suit the requirements of task 2, however, this can be easily extended or shortened by changing the input and output string array length, and then changing the loop within the output interrupt function porthISR to match the length of the arrays.

How long (roughly) does the interrupt handler take to service the interrupt.
The time to enter the interrupt  is approximately 3.75 us and to exit is 2.8us. Given an approximate 50 cycles for each serial function, the expected time to service the interrupt is approximately 10us.


## Exercise 2 

### High level information
This function repeatedly takes input commands and enacts functions based on the input. The Serial Command Parser takes an input via a serial command. The input must consist of a letter 'L', 'S' or 'M', in the first element followed by a specified parameter.

If the first element of the input string is L, it completes the LED on function.
LED On: The printLED function accepts a parameter consisting of a number between 0-8. The function will then turn on that specified LED (e.g. number 6 will turn on only the sixth LED). If the character is not an integer between 0-8, it sends an error message.
 
If the first element of the input string is S, it completes the Sevenseg on function.

SevenSeg On: The print7seg function accepts a single digit hexadecimal number (between 0-F). The function will then display the given number on the seven segment displays. If it is not a hex character, it displays an error message.

If the first element of the input string is M, it completes the music function.

Music on: This function accepts a single integer, and plays Happy birthday through the speaker if the input is 1 and jingle bells if the input is 2. If the integer is not a 1 or 2, it prints an error message.

If the first element of the input string is not one of the above characters, it prints an error message.
 
### Instructions
The user must  first let setting=2 to begin this function. The user must then input a character and then a corresponding parameter into the terminal, followed by an enter to signify the end of the string. This will then activate the corresponding function. The user can enter repeated inputs.
The user can enter L followed by a number between 1-8, then an enter to turn on that corresponding LED.
The user can enter S, followed by a hex character and then enter to display that character on the 7 segment display.
The user can enter M1 to play happy birthday, then M2 to play jingle bells on the speaker.
 
### Discussion 
How easy would it be to extend this to different types of messages? 
This would not be difficult to extend this to different types of messages if it follows the same structure. By adding a new parameter, we could modularly add a corresponding function to perform the new operation.

What ways could the parser fail? 
This parser could fail if an incorrect first element which does not correspond to any function is entered. Then if the parameter is an invalid input, it could also fail. If the input is longer than 2 characters, it will also fail.
 
## Exercise 3 
### High level information
This function plays either of two songs, jingle bells and happy birthday through the speaker. It receives an input 1 or 2 from the user within exercise 2, and plays the corresponding song. The song is played via a PWM wave, where the period is determined by inversing the frequency of the clock, to find the time length of each cycle. Then by calculating the period of each key by inversing its frequency, we divide the period of the key frequency by the period of the clock and halving it to find the desired corresponding period for each note. 
With the notes stores and the time period to play it for, it cycles through the array and plays each note for the corresponding period, forming a tune.
 
### Instructions
The user must input M1 into serial followed by an enter to play happy birthday and M2 to play jingle bells. They must wait until each song is finished to play the next song.

### Discussion 
What happens if a new tune is requested before the previous one finishes? 

If a new tune is requested before the previous tune is complete, the program will not play the new tune, and when the current tune is finished, it will register that a new song is ready to be played.

What happens if there are unexpected characters or parsing errors from the tune string?

If there is an unexpected character in the parameter section, the function will output an error message to the user telling them that the parameter must be 1 or 2 following the M.
 
 
 
 
 
 
 
 


