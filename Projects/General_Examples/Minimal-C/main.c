/**********************
  simple C-project without Arduino-like initialization and setup()/loop(). 
  No assumption is made, no interrupts used. Can be used as starting point 
  for projects with extreme memory limitations.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - toggle pin every 500ms with delay (->blocking)
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"     // STM8 peripheral registers
#include "gpio.h"       // pin access routines
#include "sw_delay.h"   // SW pause without timer


// main routine
void main(void) {
  
  uint8_t  i;
  
  // switch to 16MHz (default is 2MHz) 
  CLK.CKDIVR.byte = 0x00;  

  // configure LED pin as output (STM8S Discovery Board)
  pinMode(PORT_D, 0, OUTPUT);
  
  // main loop
  while (1) {

    // toggle LED state
    /*
    pinHigh(PORT_D, 0);
    sw_delay(500);
    pinLow(PORT_D, 0);
    sw_delay(500);
    */
    
    // toggle LED state
    pinToggle(PORT_D, 0);
    sw_delay(500);

  } // main loop

} // main

