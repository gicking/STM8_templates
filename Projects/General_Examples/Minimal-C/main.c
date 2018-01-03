/**********************
  simple C-project without Arduino-like initialization and 
  setup()/loop(). No assumption is made, no interrupts used.
  Can be used as starting point for projects with extreme
  memory limitations.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - toggle pin every 500ms with delay (->blocking)
  - optionally use delay via SW (less overhead & latency) or timer 3 (robust against high ISR load)
**********************/

// define if SW or high-rez delay function is used
//#define DELAY_HIGHREZ


/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"     // STM8 peripheral registers
#include "gpio.h"       // pin access routines
#include "sw_delay.h"   // SW pause without timer
#if defined(DELAY_HIGHREZ)
  #include "timer3.h"     // pause using TIM3
#endif

// define board LED pin
#if defined(STM8S105)
  #define LED   pinSet(PORT_D, pin0)   // STM8S Discovery Board
#else
  #define LED   pinSet(PORT_H, pin3)   // muBoard LED
#endif



// main routine
void main(void) {
  
  uint8_t  i;
  
  // switch to 16MHz (default is 2MHz) 
  CLK.CKDIVR.byte = 0x00;  

  // configure LED pin as output
  #if defined(STM8S105)
    pinMode(PORT_D, pin0, OUTPUT);    // STM8S Discovery Board
  #else
    pinMode(PORT_H, pin3, OUTPUT);    // muBoard LED
  #endif
  
  // initialize TIM3 for highRez_delay()
  #if defined(DELAY_HIGHREZ)
    TIM3_setFrequency(10000);
  #endif
  
  // main loop
  while (1) {

    // toggle LED
    LED ^= 1;
    
    // wait some time

    // using SW delay
    #if !defined(DELAY_HIGHREZ)
      sw_delay(500);

    // using HW-timer and ms delay
    #else
      highRez_delay(500);
      //for (i=0; i<100; i++) highRez_delayMicroseconds(5000); // us delay with 5ms each
      //for (i=0; i<200; i++) highRez_delayNanoseconds(40000); // 62.5ns delay (each 2.5ms)
    #endif
    
  } // main loop

} // main

