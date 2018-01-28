/**********************
  Arduino-like project with setup() & loop().
  Periodically ramp potentiometer resistance via I2C.
  Used 20kR potentiometer: Analog Devices AD5280BRUZ20 (Farnell 1438441).
  Connected via I2C pins PE1/SCL and PE2/SDA
  Functionality:
  - initialize I2C bus
  - periodically ramp resistance
  - print current value via UART1  
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "mub_digPoti.h"     // control digital poti via I2C
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init I2C bus
  i2c_init();
  
  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

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
