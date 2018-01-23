/**********************
  simple C-project without Arduino-like initialization and with calls to the 
  STM8 Standard Peripheral Library (SPL)
  (SDCC patch available from https://github.com/gicking/STM8-SPL_SDCC_patch)
  No further assumption is made, no interrupts are used.
  Can be used as starting point for SPL projects with extreme memory limitations.
  Note that device headers from STM8_templates and SPL are incompatible ->
  need to create separate SPL.c file in project folder and use interface
  functions (here simply 'SPL_init()' and 'SPL_setPin()').
  Advantage is transparent mixing of STM8_templates (simple) with STM8
  SPL library (powerful) and examples by STM.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - toggle pin every 500ms w/o timer -> blocking
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"     // STM8 peripheral registers
#include "sw_delay.h"   // dummy pause without timer

// interface functions for SPL calls. Here simply setup/loop
void SPL_init(void);
void SPL_setPin(uint8_t state);


// main routine
void main(void) {
  
  uint8_t  state = 0;
  
  // init peripherals using SPL 
  SPL_init();

  // main loop
  while (1) {

    // toggle LED
    SPL_setPin(state);
    state = ~state;
    
    // wait some time
    sw_delay(300);

  } // main loop

} // main

