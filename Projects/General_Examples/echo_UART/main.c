/**********************
  Arduino-like project with setup() & loop(). 
  Echo bytes received via UART1 with polling.
  Functionality:
  - configure UART1 for PC in-/output
  - poll if byte was received via UART1
  - echo bytes back to PC
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  char    c;

  // check for character received
  if (UART1_available()) {
    c = UART1_read();
    UART1_write(c);
  }
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
