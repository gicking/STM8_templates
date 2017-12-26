/**********************
  Arduino-like project with setup() & loop().
  Periodically enter STOP mode with auto-wake.
  Send Status via UART1 to PC
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - attach ISR to AWU interrupt
  - periodically enter STOP mode
  - in AWU interrupt print status
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "awu.h"

// LEDs on muBoard  
#define LED_GREEN   PORT_H.ODR.bit.b2
#define LED_RED     PORT_H.ODR.bit.b3


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void AWU_ISR(void)
 
  \brief toggle LED after wake
 
  toggle LED after wake
*/
ISR_HANDLER(AWU_ISR, __AWU_VECTOR__) {

  // reset wakeup flag (mandatory)
  AWU_reset_ISR_flag();
  
  // toggle LED state
  LED_GREEN ^= 1;
  
  // send wake time via UART1 (uses blocking send!)
  sw_delay(5);
  printf("wake at %dms \n", (int) millis());

} // AWU_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // configure pins for LEDs (red=PH3 / green=PH2)
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;


  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  uint16_t  sleepDuration = 5000;
  
  // every 1ms do
  if (flagMilli()) {
    clearFlagMilli();
    
    // every 1s do
    if ((millis() % 1000) == 0) {
  
      // toggle LED state
      LED_RED ^= 1;

      // send message to PC (uses blocking send)
      printf("sleep at %dms \n", (int) millis());
      sw_delay(5);

      // fast-foward SW clock
      millis() += sleepDuration;
      
      // halt code execution then wake via AWU interrupt
      AWU_HaltMode(sleepDuration);

    } // 1s loop
    
  } // 1ms loop

} // loop


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
