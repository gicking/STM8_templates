/**********************
  Arduino-like project with setup() & loop(). 
  Trigger TRAP interrupt by software. 
  Functionality:
  - configure pin as input pull-up
  - on pin=low, trigger TRAP_ISR
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle LED
//////////
ISR_HANDLER_TRAP(TRAP_ISR) {
  
  // toggle LED state
  pinToggle(&PORT_H, 2);

  // wait a while for debouncing
  sw_delay(50);
  
} // TRAP_ISR



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure button pin PE5 as input pull-up with interrupt
  pinMode(&PORT_E, 5, INPUT_PULLUP);
    
  // configure LED pin as output
  pinMode(&PORT_H, 2, OUTPUT);
  pinMode(&PORT_H, 3, OUTPUT);
 
} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  uint8_t s = pinRead(&PORT_E, 5);
  
  pinSet(&PORT_H, 3, s);
  
  // if PE5 is low, trigger trap
  if (s == 0)
    trap();
  
} // loop

