/**********************
  Arduino-like project with calls to the STM8 Standard Peripheral Library
  (SDCC patch available from https://github.com/gicking/STM8-SPL_SDCC_patch). 
  Note that device headers from STM8_templates and SPL are incompatible ->
  need to create separate SPL.c file in project folder and use interface
  functions (here simply 'SPL_setup()' and 'SPL_loop()').
  Advantage is transparent mixing of STM8_templates (simple) with STM8
  SPL library (powerful) and examples by STM.
  Functionality:
  - use SPL to configure LED pin as output
  - toggle LED via SPL every 500ms
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main

// interface functions for SPL calls. Here simply setup/loop
void SPL_setup(void);
void SPL_loop(void);


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // call SPL setup function
  SPL_setup();

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // poll 1ms flag
  if (flagMilli()) {
    clearFlagMilli();    // reset 1ms flag

    // every 500ms call SPL function (toggle LED)
    if (!(millis() % 500))
      SPL_loop();
    
  } // if flagMilli

} // loop

