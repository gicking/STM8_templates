/**********************
  Arduino-like project with setup() & loop(). Use
  16-bit timer 3 to generate PWM with variable
  frequency and duty cycle. 
  Functionality:
  - ramp LED brightness using TIM3 PWM
  - use timeout periodically update brightness
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "timeout.h"         // for timeout clocks
#include "timer3.h"          // for PWM


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/
#define updatePeriod 50     // update period for LED brightness
#define channelLED   2      // LED is connected to TIM3_CC2


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin on STM8S Discovery board (=PD0=TIM3_CC2). Is io_3 on muBoard
  pinMode(&PORT_D, 0, OUTPUT);

  // init TIM3 for PWM
  TIM3_init();
  
  // set TIM3 frequency (all channels) in [0.01Hz] -> 1kHz
  TIM3_setFrequency(100000);

  // set initial timeout 0
  setTimeout(0, updatePeriod);
  
} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  static int16_t  brightness = 0;
  
  // after timeout 0 has expired
  if (checkTimeout(0)) {
  
    // restart timeout 0
    setTimeout(0, updatePeriod);

    // ramp brighness [0.1%] with overflow
    brightness -= 50;
    if (brightness < 0)
      brightness = 1000;
      
    // update PWM brightness (=duty cycle)
    TIM3_setDutyCycle(channelLED, brightness);
    
  } // timeout 0 expired
    
} // loop

