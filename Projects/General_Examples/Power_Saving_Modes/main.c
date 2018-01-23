/**********************
  Arduino-like project with setup() & loop(). 
  Enter power-saving modes with auto-wake via 
    - any interrupt (lowPower_Wait)
    - external interrupt or auto-wake (lowPower_HaltAWU)  
    - external interrupt (lowPower_Halt)
  Use EXINT port interrupt @ pin PE5 (=io_1 on muBoard)
  (-> #define USE_PORTE_ISR) and AWU (-> #define USE_AWU_ISR)
  Functionality:
  - configure wake pin as input pull-up with interrupt on falling edge
  - configure LED output pin
  - enter power-down mode
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "power-saving.h"   // low-power mode functions


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access button(=PE5=io_1) and LED(green=PH2) pins. See gpio.h
#define BUTTON     pinRead(PORT_E, pin5)
#define LED        pinSet(PORT_H, pin2)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// AWU interrupt: AWU flag (is mandatory!)
//////////
ISR_HANDLER(AWU_ISR, __AWU_VECTOR__) {

  // reset wakeup flag (mandatory)
  AWU_resetFlag();
  
} // AWU_ISR


//////////
// port E interrupt: dummy
//////////
ISR_HANDLER(PORTE_ISR, __PORTE_VECTOR__) {
  
} // PORTE_ISR



//////////
// user setup, called once after reset
//////////
void setup() {
  
  // avoid spurious interrupts...
  noInterrupts();
  
  // configure button pin PE5 as input pull-up with interrupt
  pinMode(PORT_E, pin5, INPUT_PULLUP_INTERRUPT);
  
  // configure edge sensitivity for port E (all 8 pins!) 
  configEdgeExint(PORT_E, FALLING);
  
  // re-enable interrupts
  interrupts();

  
  // configure LED pins as output high
  pinMode(PORT_H, pin2, OUTPUT);
  LED = 1;
  
} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // indicate that STM8 is awake
  uint8_t  i;
  for (i=0; i<6; i++) {
    LED ^= 1;
    delay(100);
  }
  
  // enter power saving mode (sorted by decreasing power consumption)
  //lowPower_Wait();          // enter WAIT mode, wake via button
  lowPower_HaltAWU(2000);   // enter active HALT mode, wake via button, or latest after 2s
  //lowPower_Halt();          // enter HALT mode, wake via button

} // loop

