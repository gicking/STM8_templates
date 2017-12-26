/**********************
  Arduino-like project with setup() & loop(). 
  Activate/Deactivate STM8 ROM bootloader depending on
  state of pin PD7 (=switch "automode" on muBoard)
  Functionality:
  - configure pin as input pull-up
  - wait a bit and read pin state
  - activate(state=1) or deactivate(state=0) BL via option byte
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "eeprom.h"


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

#define PIN_BSL   pinRead(PORT_D, pin7)     ///< selection pin (= PD7 = muBoard automode) pin
#define LED       pinSet(PORT_H, pin3)      ///< muBoard LED
//#define LED       pinSet(PORT_D, pin0)      ///< STM8S Discovery LED

/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pin as output
  LED = 1;
  pinMode(PORT_H, pin3, OUTPUT);
  
  // configure selection pin (=PD7) as input pull-up and wait a bit to be sure
  pinMode(PORT_D, pin7, INPUT_PULLUP);    // muBoard
  //pinMode(PORT_D, pin0, OUTPUT);          // STM8S Discovery
  sw_delay(5);

  // deneding on pin state activate/deactivate the BL
  if (PIN_BSL == 1) {
    OPT_setBootloader(true);
  }
  else {
    OPT_setBootloader(false);
  }

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // dummy blink
  LED ^= 1;
  sw_delay(100);

} // loop

