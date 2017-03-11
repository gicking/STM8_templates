/**********************
  Arduino-like project with setup() & loop(). Dynamically attach 
  user function to TLI pin interrupt @ PD7 (=automode on muBoard)
  (-> #define USE_TLI_ISR) to call function on falling edge. 
  Functionality:
    - configure 1 pins as input pull-up & 2 pins as output high
    - attach user function to port interrupt -> background operation
    - after 10 ISR calls detach user function
    - poll TLI pin and mirror to LED
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access TLI(=PD7) and LEDs(green=PH2, red=PH3) pins. See gpio.h
#define PIN_TLI    pinRead(PORT_D, pin7)
#define LED_GREEN  pinSet(PORT_H, pin2)
#define LED_RED    pinSet(PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle LED 10x then detach user function
//////////
void toggle_LED(void) {
  
  static uint8_t   numToggle = 0;

  // toggle LED state
  LED_RED ^= 1;

  // wait a while for debouncing
  sw_delay(50);

  // after 10 cycles swap to other user function
  if (++numToggle == 10)
    detachInterruptPin();

} // toggle_red



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure TLI pin PD7 as input pull-up with interrupt
  pinMode(PORT_D, pin7, INPUT_PULLUP_INTERRUPT);
  
  // configure LED pins as output high
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;
  
  // attach user function to 
  attachInterruptPin(toggle_LED, FALLING);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // also mirror TLI pin state to green LED
  LED_GREEN = PIN_TLI;

} // loop

