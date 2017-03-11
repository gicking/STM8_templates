
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
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include <stdio.h>


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pin (=PH3). See gpio.h
#define LED   pinSet(PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin
  pinMode(PORT_H, pin3, OUTPUT);

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  #if defined(USE_FTOA)
    char    str[20];
  #endif

  // every 1ms do
  if (flagMilli()) {
    clearFlagMilli();    // reset 1ms flag

    // every 500ms toggle LED
    if (!(millis() % 500)) {
      LED ^= 1;
      #if defined(USE_FTOA)
        printf("time is %s s\n", floatToString(str, millis()/1000.0, 2));
      #else
        printf("time is %d ms\n", (int) (millis()));
      #endif
    }

  } // if flagMilli

} // loop

