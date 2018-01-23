/**********************
  simple C-project without Arduino-like initialization and setup()/loop(), 
  but with interrupt.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - init 1ms TIM4 interrupt (for measuring times)
  - toggle pin every 500ms based on SW clock (->non-blocking)
  Note:
    - define "USE_TIM4_UPD_ISR" in "config.h" for 1ms interrupt (TIM4_UPD)
    - include "stm8_interrupt_vector.h" here, because SDCC needs ISR declaration in file containing main()
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"                   // STM8 peripheral registers
#include "stm8_interrupt_vector.h"    // must be in file conaining main()
#include "gpio.h"                     // pin access routines
#include "timer4.h"                   // 1ms clock


// define board LED pin for STM8S Discovery Board
#define LED   pinSet(PORT_D, pin0)

// main routine
void main(void) {
  
  // globally disable interrupts
  DISABLE_INTERRUPTS;

  // switch to 16MHz (default is 2MHz) 
  CLK.CKDIVR.byte = 0x00;  

  // init 1ms SW clock
  TIM4_init();

  // configure LED pin as output
  pinMode(PORT_D, pin0, OUTPUT);

  // globally enable interrupts
  ENABLE_INTERRUPTS;
 

  // main loop
  while (1) {

    // poll 1ms flag
    if (flagMilli()) {
      clearFlagMilli();    // reset 1ms flag

      // every 500ms toggle LED
      if (!(millis() % 500))
        LED ^= 1;

    } // if flagMilli

  } // main loop

} // main

