/**********************
  Arduino-like project with setup() & loop(). Demonstrate tone
  output via beeper module.
  Note: requires option byte AFR7=1 for alternate usage of BEEP pin 
  Functionality:
    - play tone ladder with increasing frequency
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "tone.h"


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  uint16_t freq;
  
  for (freq=500; freq<=4000; freq+=100) {
    tone(freq,0);
    sw_delay(50);
  }

} // loop

