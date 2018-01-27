/**********************
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_MILLI_ISR) to 
  automatically call function every 1ms. 
  Functionality:
  - configure 2 pins as output high
  - attach pin toggle function to 1ms interrupt -> background operation
  - use timeouts to periodically perform tasks in ISR
  - after N cycles swap user function
  - after M cycles detach user function
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "timeout.h"        // user timeout clocks


// declare for toggle_red()
void toggle_green(void);


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pins (green=PH2; red=PH3). See gpio.h
#define LED_GREEN   pinOutputReg(&PORT_H, pin2)
#define LED_RED     pinOutputReg(&PORT_H, pin3)

// blink delay [ms]
#define BLINK_DELAY   500


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle red LED 10x then swap user function
//////////
void toggle_red(void) {
  
  static uint8_t   numToggle = 0;

  // check if timeout 0 has passed
  if (checkTimeout(0)) {
  
    // restart timeout 0
    setTimeout(0, BLINK_DELAY);
    
    // toggle LED state
    LED_RED ^= 1;

    // after 10 cycles swap to other user function
    if (++numToggle == 10)
      attachInterruptMillis(toggle_green);

  } // timout passed

} // toggle_red


//////////
// toggle green LED 10x then detach user function
//////////
void toggle_green(void) {
  
  static uint8_t   numToggle = 0;

  // check if timeout 0 has passed
  if (checkTimeout(0)) {
  
    // restart timeout 0
    setTimeout(0, BLINK_DELAY);
    
    // toggle LED state
    LED_GREEN ^= 1;

    // after 10 more cycles detach user function
    if (++numToggle == 10)
      detachInterruptMillis();

  } // 500ms

} // toggle_green



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pins and init to off(=1)
  pinMode(&PORT_H, 2, OUTPUT);
  pinMode(&PORT_H, 3, OUTPUT);
  portOutputReg(&PORT_H) = 0b00001100;
  
  // attach user function to 1ms interrupt
  attachInterruptMillis(toggle_red);

  // set initial timeout 0
  setTimeout(0, BLINK_DELAY);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // dummy. Action is happening in 1ms interrupt & above toggle_x() routines

} // loop

