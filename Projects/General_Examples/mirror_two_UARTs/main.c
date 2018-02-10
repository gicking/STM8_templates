/**********************
  Arduino-like project with setup() & loop(). 
  Mirror bytes received via UART1 to UART3 and vice
  versa with polling.
  Functionality:
  - configure UART1 to 115.2kBaud
  - configure UART3 to 19.2kBaud
  - poll if byte was received via UART1 or UART3
  - if byte received, mirror to other UART
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication
#include "uart3.h"           // UART3 communication


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART1 to 115.2kBaud and UART3 to 19.2kBaud
  UART1_begin(115200);
  UART3_begin(19200);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // if character received via UART1, mirror it to UART3
  if (UART1_available())
    UART3_write(UART1_read());
  
  // if character received via UART3, mirror it to UART1
  if (UART3_available())
    UART1_write(UART3_read());

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
