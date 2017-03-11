/**********************
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_MILLI_ISR) to 
  automatically call function every 1ms. 
  Functionality:
    - configure 2 pins as output high
    - attach pin toggle function to 1ms interrupt -> background operation
    - after 10 cycles swap user function
    - after 20 cycles detach user function
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


// declare for toggle_red()
void toggle_green(void);


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pins (green=PH2; red=PH3). See gpio.h
#define LED_GREEN  pinSet(PORT_H, pin2)
#define LED_RED    pinSet(PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle red LED 10x then swap user function
//////////
void toggle_red(void) {
  
  static uint16_t  count1ms = 0;
  static uint8_t   numToggle = 0;

  if (++count1ms == 500) {
    count1ms = 0;

    // toggle LED state
    LED_RED ^= 1;

    // after 10 cycles swap to other user function
    if (++numToggle == 10)
      attachInterruptMillis(toggle_green);

  } // 500ms

} // toggle_red


//////////
// toggle green LED 10x then detach user function
//////////
void toggle_green(void) {
  
  static uint16_t  count1ms = 0;
  static uint8_t   numToggle = 0;

  if (++count1ms == 500) {
    count1ms = 0;

    // toggle LED state
    LED_GREEN ^= 1;

    // after 10 cycles swap to other user function
    if (++numToggle == 10)
      detachInterruptMillis();

  } // 500ms

} // toggle_green



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pins and init to off(=1)
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  portSet(PORT_H) = B00001100;
  
  // attach user function to 1ms interrupt
  attachInterruptMillis(toggle_red);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // dummy. Action is happening in 1ms interrupt & above routines

} // loop

