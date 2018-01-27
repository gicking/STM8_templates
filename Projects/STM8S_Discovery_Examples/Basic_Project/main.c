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
#define LED   pinOutputReg(&PORT_D, pin0)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pin as output
  pinMode(&PORT_D, 0, OUTPUT);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // toggle LED
  LED ^= 1;

  // wait 500ms
  delay(500);
  //delayMicroseconds(500000L);

} // loop

