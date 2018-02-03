/**********************
  Arduino-like project with setup() & loop(). 
  Print current millis() to the LCD screen. 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "lcd-BTHQ21605V.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init I2C module 
  i2c_init();
  
  // init and reset LCD display
  BTHQ21605V_lcd_init(&PORT_E, 3);

  // print to LCD
  BTHQ21605V_lcd_print(1, 1, "hello user");

} // setup()



//////////
// user loop, called continuously
//////////
void loop() {
  
  char              str[20];    // string buffer for LCD output

  // print to LCD
  sprintf(str, "time = %d s", (int) (millis()/1000L));
  BTHQ21605V_lcd_print(2, 1, str);
      
  // wait 1s
  sw_delay(1000);

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
