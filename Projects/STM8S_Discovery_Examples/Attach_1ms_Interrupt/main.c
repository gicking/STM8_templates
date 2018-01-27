/**********************
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_MILLI_ISR) to 
  automatically call function every 1ms. 
  Functionality:
  - configure LED pin as output
  - attach pin toggle function to 1ms interrupt -> background operation
  - after N cycles detach user function
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
// toggle LED 20x then detach user function
//////////
void toggle_LED(void) {
  
  static uint16_t  count1ms = 0;
  static uint8_t   numToggle = 0;

  // check if 500ms have passed
  if (++count1ms == 500) {
    count1ms = 0;

    // toggle LED state
    LED ^= 1;

    // after 20 cycles detach this function from 1ms ISR
    if (++numToggle == 20)
      detachInterruptMillis();

  } // 500ms

} // toggle_LED



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pins and init to off(=1)
  pinMode(&PORT_D, 0, OUTPUT);
  portOutputReg(&PORT_D) |= 0b00000001;
  
  // attach user function to 1ms interrupt
  attachInterruptMillis(toggle_LED);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // dummy. Action is happening in 1ms interrupt & above toggle_LED()

} // loop

