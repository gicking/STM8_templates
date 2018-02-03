/**********************
  Arduino-like project with setup() & loop(). 
  Ramp up/down resistances of 2-channel poti AD5282 via I2C. 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "digPoti-AD5282.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init I2C module 
  i2c_init();

} // setup


//////////
// user loop, called continuously
//////////
void loop() {
  
  static uint8_t res = 0;
  
  // set resistance of channel A to Rmax/255*res, and B to Rmax/255*(255-res)
  AD5282_set_poti(0, res);
  AD5282_set_poti(1, 255-res);

  // wait a while
  delay(500);
  
  // ramp up
  res += 8;

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
