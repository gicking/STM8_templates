/**********************
  Arduino-like project with setup() & loop(). Only 1ms interrupts
  are used, but no other optional features. Can be used as a 
  starting point for simple Arduino-like STM8 projects.
  Functionality:
  - configure LED pin as output
  - poll SW clock and toggle LED every 500ms -> non-blocking
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// define board LED pin on STM8S Discovery Board
#define LED   pinSet(PORT_D, pin0)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pin as output
  pinMode(PORT_D, pin0, OUTPUT);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // poll 1ms flag
  if (flagMilli()) {
    clearFlagMilli();    // reset 1ms flag

    // every 500ms toggle LED
    if (!(millis() % 500))
      LED ^= 1;

  } // if flagMilli

} // loop

