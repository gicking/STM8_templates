/**********************
  Arduino-like project with setup() & loop(). 
  Use EXINT port interrupt @ pin PE5 (=io_1 on muBoard)
  (-> #define USE_PORT_ISR) to call function on falling edge. 
  Functionality:
  - configure 1 pins as input pull-up & 2 pins as output high
  - attach ISR to port interrupt -> background operation
  - after 10 ISR calls disable ISR
  - poll button and mirror to LED
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access button(=PE5=io_1) and LEDs(green=PH2, red=PH3) pins. See gpio.h
#define BUTTON     pinRead(PORT_E, pin5)
#define LED_GREEN  pinSet(PORT_H, pin2)
#define LED_RED    pinSet(PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle LED 10x, then deactivate pin ISR
//////////
ISR_HANDLER(PORTE_ISR, __EXTI4_VECTOR__) {
  
  static uint8_t   numToggle = 0;

  // toggle LED state
  LED_RED ^= 1;

  // wait a while for debouncing
  sw_delay(50);

  // after 10 cycles disable ISR
  if (++numToggle == 10)
    pinMode(PORT_E, pin5, INPUT_PULLUP);

} // PORTE_ISR



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure button pin PE5 as input pull-up with interrupt
  pinMode(PORT_E, pin5, INPUT_PULLUP_INTERRUPT);
  
  // configure LED pins as output high
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;
  
  // configure edge sensitivity for port E (all 8 pins!) 
  configExintEdge(&PORT_E, FALLING);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // also mirror button state to green LED
  LED_GREEN = BUTTON;

} // loop

