/**********************
  Arduino-like project with setup() & loop().
  Periodically ramp potentiometer resistance via I2C.
  Used 20kR potentiometer: Analog Devices AD5280BRUZ20 (Farnell 1438441).
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_muBoard.h"    // board-independent main
#include "uart1.h"           // UART1 communication
#include "putchar.h"         // for printf()


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // nothing to do, initialization is done in main() 

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  static uint8_t  res = 0;  // resistance in [20kR/255]
  uint8_t         err;      // I2C status response
      
  // set new resistance
  err = set_dig_poti(res);
  
  // print to terminal
  printf("%d Ohm, err=%d\n", (int) (((long) res * 20000L) >> 8), (int) err);

  // wait a bit
  sw_delay(1000);

  // set new value
  res += 8;

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
