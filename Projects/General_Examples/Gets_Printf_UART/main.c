
/**********************
  Arduino-like project with setup() & loop(). Print output
  via UART to PC terminal. Optionally in integer (small)
  or floating (large) format.
  Functionality:
    - configure UART1 and putchar() for PC output
    - every 500ms send current time via printf()
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
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

