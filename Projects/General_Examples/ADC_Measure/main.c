/**********************
  Arduino-like project with setup() & loop().
  Periodically measure via ADC and switch LED on/off
  depending on analog threshold
  Functionality:
  - configure pin for LED
  - initialize ADC for single measurement
  - measure ADC and switch LED depending on value 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "adc.h"


// misc defines
#define ACH        5                          // ADC channel to measure (=PB5=AIN5=poti on muBoard, CN3 pin 5 on STM8S Discovery)
#define ATHR       512                        // analog threshold
#if defined(STM8S208)
  #define LED_ON   pinLow(&PORT_H, 2)         // muBoard (0=LED off)
  #define LED_OFF  pinHigh(&PORT_H, 2)
#else
  #define LED_ON   pinHigh(&PORT_D, 0)        // STM8S Discovery
  #define LED_OFF  pinLow(&PORT_D, 0)
#endif


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin
  #if defined(STM8S208)
    pinMode(&PORT_H, 2, OUTPUT);    // muBoard
  #else
    pinMode(&PORT_D, 0, OUTPUT);    // STM8S Discovery
  #endif
  LED_OFF;  

  // configure pin AIN5 as input float (=poti on muBoard, CN3 pin 5 on STM8S Discovery)
  pinMode(&PORT_B, 5, INPUT);

  // init ADC for measuring poti 
  ADC_init(ADC_SINGLE_SHOT);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  uint16_t  result;
  
  // every 1ms do
  if (flagMilli()) {
    clearFlagMilli();
    
    // every 50ms do
    if ((millis() % 50) == 0) {
  
      // measure ADC
      result = ADC_measure(ACH);
    
      // set new LED state
      if (result > ATHR)
        LED_ON;
      else
        LED_OFF;      

    } // 500ms loop
    
  } // 1ms loop

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
