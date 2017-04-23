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

// access switch(=PD7) pin. See gpio.h
#define PIN_BSL    pinRead(PORT_D, pin7)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure PD7 as input pull-up and wait a bit to be sure
  pinMode(PORT_D, pin7, INPUT_PULLUP);
  sw_delay(5);

  if (PIN_BSL == true) {
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

  // dummy. Action happens in setup()

} // loop

