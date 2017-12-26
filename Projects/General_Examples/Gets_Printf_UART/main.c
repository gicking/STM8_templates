/**********************
  Arduino-like project with setup() & loop(). Read number
  as string via UART from PC terminal and echo value back.
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - use UART1 receive for gets() input
  - read string from PC, convert to number and send value to PC
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "getchar.h"         // for gets()


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // use UART1 blocking read for gets() input
  getcharAttach(UART1_readBlock);
  
  // wait a it for console to launch
  sw_delay(1000);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  char    str[20];
  int     num;

  // read a string via UART1
  printf("Enter a number: ");
  gets(str);
  
  // convert to integer [-2^16; 2^16-1]
  num = atoi(str);
  
  // print result via UART1
  printf("value: %d\n\n", num);
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
