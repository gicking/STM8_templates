/**********************
  Arduino-like project with setup() & loop().
  Periodically enter STOP mode with auto-wake.
  Functionality:
  - attach ISR to AWU interrupt
  - periodically enter STOP mode with auto-wake
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "awu.h"

// LED pin
#define LED pinSet(PORT_D, pin0)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void AWU_ISR(void)
 
  \brief toggle LED after wake
 
  reset AWU flag (is mandatory!)
*/
ISR_HANDLER(AWU_ISR, __AWU_VECTOR__) {

  // reset wakeup flag (mandatory)
  AWU_reset_ISR_flag();
  
} // AWU_ISR


//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin as output
  pinMode(PORT_D, pin0, OUTPUT);
  LED = 1;

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  uint16_t  sleepDuration = 2000;
  
  // every 1ms do
  if (flagMilli()) {
    clearFlagMilli();
    
    // every 100ms toggle LED
    if ((millis() % 100) == 0)
      LED ^= 1;

    
    // every 1ms enter HALT mode LED
    if ((millis() % 1000) == 0) {
  
      // halt code execution then wake via AWU interrupt
      AWU_HaltMode(sleepDuration);

      // fast-foward SW clock
      millis() += sleepDuration;
  
    } // 1s loop
    
  } // 1ms loop

} // loop


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
