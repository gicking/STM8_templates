/**********************
  Arduino-like project with setup() & loop(). 
  Ramp up resistance of 1-channel poti AD5280 via I2C. 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "digPoti-AD5280.h"


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
  
  // set resistance to Rmax/255*res
  AD5280_set_poti(res);

  // wait a while
  delay(500);
  
  // ramp up
  res += 8;

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
