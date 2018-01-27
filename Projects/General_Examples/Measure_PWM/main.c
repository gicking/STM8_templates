/**********************
  Arduino-like project with setup() & loop(). 
  Measure a PWM and print frequency and duty cycle 
  via UART to PC terminal. 
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - measure PWM frequency and duty cycle (blocking)
  - print frequency and duty cycle via UART
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "timeout.h"         // user timeout clocks
#include "pulse.h"           // for pulseIn()


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure pins
  pinMode(&PORT_E, 5, INPUT_PULLUP);
  
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
  
  uint32_t  high, low;

  // check if timeout 0 has passed
  if (checkTimeout(0)) {

    // restart timeout 0
    setTimeout(0, 500);

    // measure PWM
    high = pulseIn(&PORT_E, 5, HIGH, 10);
    low  = pulseIn(&PORT_E, 5, LOW, 10);
    //printf("high: %ld; low: %ld\n", high,low);
    
    // print result
    if ((high == 0) || (low == 0))
      printf("timeout\n");
    else
      printf("freq: %d %d\n", (int)(1000000L/(high+low)), (int)(high*100L/(high+low)));

  } // every 500ms

} // loop

