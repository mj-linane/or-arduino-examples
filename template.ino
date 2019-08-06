// Template for Arduino projects on VSCode

#include <Arduino.h>

/*
SETUP BLOCK  = Preparation
The setup function is the first to execute when the program is executed, 
and this function is called only once. The setup function is used to 
initialize the pin modes and start serial communication. 
This function has to be included even if there are no statements to execute.

Example:
pinMode (pin-number, OUTPUT); // set the ‘pin-number’ as output
pinMode (pin-number, INPUT); // set the ‘pin-number’ as output
*/

void setup()
{
  // Your code goes here
}

/* 
LOOP BLOCK = Execution
After the setup ( ) function is executed, the execution block runs next. 
The execution block hosts statements like reading inputs, triggering outputs, 
checking conditions etc.

In the above example loop ( ) function is a part of execution block. 
As the name suggests, the loop( ) function executes the set of statements 
(enclosed in curly braces) repeatedly.

Example:
digitalWrite (pin-number,HIGH); // turns ON the component connected to ‘pin-number’
delay (1000); // wait for 1 sec
*/

void loop()
{
  // Your code goes here
}
