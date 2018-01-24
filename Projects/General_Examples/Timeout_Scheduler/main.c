/**********************
  Arduino-like project with setup() & loop(). Use several 
  timeouts to execute periodic tasks in loop(). 
  Functionality:
  - configure 2 (LED-)pins as output
  - configure timeouts for periodic tasks
  - toggle 2 pins at different intervals
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "timeout.h"        // multiple timeouts 


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pins (green=PH2; red=PH3). See gpio.h
#define LED_GREEN  pinOutputReg(PORT_H, pin2)
#define LED_RED    pinOutputReg(PORT_H, pin3)

// blink delays [ms]
#define DELAY_GREEN   500
#define DELAY_RED     333


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
  
  // configure LED pins and init to off(=1)
  pinMode(PORT_H, 2, OUTPUT);
  pinMode(PORT_H, 3, OUTPUT);
  portOutputReg(PORT_H) = 0b00001100;
  
  // set initial timeouts
  setTimeout(0, DELAY_GREEN);
  setTimeout(1, DELAY_RED);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  // timeout 0 has passed --> toggle green LED
  if (checkTimeout(0)) {

    // restart timeout (is single-shot)
    setTimeout(0, DELAY_GREEN);
    //setTimeout(0, randomIn(100,300));
    
    // toggle LED
    LED_GREEN ^= 1;
  
  } // timeout 0 passed


  // timeout 1 has passed --> toggle red LED
  if (checkTimeout(1)) {

    // restart timeout (is single-shot)
    setTimeout(1, DELAY_RED);
    //setTimeout(1, randomIn(200,400));
    
    // toggle LED
    LED_RED ^= 1;
  
  } // timeout 1 passed

} // loop

