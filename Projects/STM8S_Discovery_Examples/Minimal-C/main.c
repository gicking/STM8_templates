/**********************
  simple C-project without Arduino-like initialization and 
  setup()/loop(). No assumption is made, no interrupts used.
  Can be used as starting point for projects with extreme
  memory limitations or real-time requirements.
  Functionality:
  - init FCPU to 16MHz
  - configure LED pin as output
  - toggle LED every 500ms w/o timer -> blocking
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"     // STM8 peripheral registers
#include "gpio.h"       // pin access routines
#include "sw_delay.h"   // dummy pause without timer


// define board LED pin for STM8S Discovery Board
#define LED   pinOutputReg(&PORT_D, pin0)

// main routine
void main(void) {
  
  // switch to 16MHz (default is 2MHz) 
  CLK.CKDIVR.byte = 0x00;  

  // configure LED pin as output
  pinMode(&PORT_D, 0, OUTPUT);

  // main loop
  while (1) {

    // toggle LED
    //LED ^= 1;               // direct (bitwise) pin access
    pinToggle(&PORT_D, 0);   // "normal" access via pin number
    
    // wait some time
    sw_delay(500);

  } // main loop

} // main

