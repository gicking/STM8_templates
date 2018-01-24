/**********************
  Arduino-like project with setup() & loop(). Print output
  via UART to PC terminal. Optionally in integer (small)
  or floating (large) number format. 
  For float output #define USE_FTOA in config.h.
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - every 500ms send current time via printf()
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "timeout.h"        // user timeout clocks


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pin (=PH3). See gpio.h
#define LED   pinOutputReg(PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin
  pinMode(PORT_H, 3, OUTPUT);

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // start timeout 0
  setTimeout(0, 500);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  #if defined(USE_FTOA)
    char    str[20];
  #endif

  // check if timeout 0 has passed
  if (checkTimeout(0)) {

    // restart timeout 0
    setTimeout(0, 500);

    LED ^= 1;
    #if defined(USE_FTOA)
      printf("time is %s s\n", floatToString(str, millis()/1000.0, 3));
    #else
      printf("time is %d ms\n", (int) (millis()));
    #endif

  } // every 500ms

} // loop

