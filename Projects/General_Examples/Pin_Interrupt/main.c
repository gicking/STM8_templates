/**********************
  Arduino-like project with setup() & loop(). 
  Use TLI interrupt @ pin PD7 (=automode on muBoard)
  (-> #define USE_TLI_ISR) to call function on falling edge. 
  Functionality:
  - configure TLI pins as input pull-up w/ interrupt
  - configure 2 pins as output high
  - attach ISR to TLI interrupt -> background operation
  - after N ISR calls disable ISR
  - poll TLI pin and mirror to LED
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access TLI(=PD7=ModeSelect) and LEDs(green=PH2, red=PH3) pins. See gpio.h
#define PIN_TLI    pinInputReg(&PORT_D, pin7)
#define LED_GREEN  pinOutputReg(&PORT_H, pin2)
#define LED_RED    pinOutputReg(&PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// toggle LED 10x, then deactivate TLI ISR
//////////
ISR_HANDLER(TLI_ISR, __TLI_VECTOR__) {
  
  static uint8_t   numToggle = 0;

  // toggle LED state
  LED_RED ^= 1;

  // wait a while for debouncing
  sw_delay(50);

  // after 10 cycles disable ISR
  if (++numToggle == 10)
    pinMode(&PORT_D, 7, INPUT_PULLUP);
  
} // TLI_ISR



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // avoid spurious interrupts...
  noInterrupts();
  
  // set edge sensitivity of TLI pin
  configEdgeTLI(FALLING);
  
  // configure TLI pin PD7 as input pull-up with interrupt
  pinMode(&PORT_D, 7, INPUT_PULLUP_INTERRUPT);
  
  // re-enable interrupts
  interrupts();
  
    
  // configure LED pins as output high
  pinMode(&PORT_H, 2, OUTPUT);
  pinMode(&PORT_H, 3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;
  
} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // also mirror TLI pin state to green LED
  LED_GREEN = PIN_TLI;

} // loop

