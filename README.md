# Tron 2 Assignment 2
## About our code
This assignment involved the development of individual modules in C code to program the HCS12 microcontroller. Each module was developed with the intention of integration to perform several key functions. These key concepts include:
1. Storing serial inputs and Sending output buffer
2. Parsing serial commands
3. Playing a song
Our group decided we would create each module with a specific set of inputs and outputs in order to increase functionality and usage. We have also thouroughly commented our code to ensure readability and unserstaning of the code between ourselves.


## Testing Procedures
Most of our testing procedures were performed using the inbuilt debugging features in CodeWarrior. These testing methods include:
- **Single Line Stepping**: Using the single line stepping feature allows for clear inspection of memory and the functionality of each line of code
- **Breakpoints**: Using breakpoints throughout the code allowed us to see the functionality of each module of code


## Group Contributions
Majority of our code and debugging was worked on together during labs and zoom sessions. 
**Luke**: Luke worked on the first section, creating an interface with the serial ports and creating integral modules to be used in the later parts.

**Emily**: Emily worked on the third section, creating songs to be played, as well as, working on some functions for the second section. Emily also modularising our code, creating individual files and functions for each section.

**Tara**: Tara worked on the second section, working with sections from the rest of the program to create new functions. Tara also worked on the README file.


## User Instructions
**1.0 Serial With Interupts**: 

**2.0 Serial Command Parser**: The Serial Command Parser takes an input via a serial command. The input must consist of a letter 'L', 'S' or 'M', followed by a specified paramtere.

***2.1 LED On***: The printLED function accepts a parameter consisting of a number between 0-8. The function will then turn on that specified LED (e.g. number 6 will turn on only the sixth LED)

***2.2 SevenSeg On***: The print7seg function accpets a single digit hexadecimal number (between 0-F). The function will then display the given number on the seven segment displays.

**3.0 Music Module/2.3 Play Sound**: 



○ The details about the project (group members, roles, responsibilities)
○ High level information about the code - the function, how the program is broken down into
modules.
○ Instructions for the user
○ Details about testing procedures
