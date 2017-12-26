/**********************
  Arduino-like project with setup() & loop().
  Periodically measure via ADC2 and send result via 
  UART1 in ADC interrupt routine (muBoard)
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - initialize ADC2 for single measurement
  - periodically send ADC result via UART1 and blink LED
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "adc2.h"


// misc defines
#define ADC_CH      5                   ///< ADC channel to measure (=PB5=AIN5=poti)
#define LED_GREEN   PORT_H.ODR.bit.b2	  ///< green LED control (0=on)
#define LED_RED     PORT_H.ODR.bit.b3	  ///< red LED control (0=on)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // configure pins for LEDs (red=PH3 / green=PH2)
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;


  // configure ADC poti(=PB5) as input float
  pinMode(PORT_B, pin5, INPUT);


  // init ADC2 for measuring poti 
  ADC2_init(ADC_SINGLE_SHOT, ADC_CH);

  
  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  uint16_t  result;
  
  // every 1ms do
  if (flagMilli()) {
    clearFlagMilli();
    
    // every 500ms do
    if ((millis() % 500) == 0) {
  
      // toggle LED state
      LED_RED ^= 1;

      // measure ADC
      result = ADC2_measure_single(ADC_CH);
    
      // send result via UART1 (uses blocking send)
      printf("ADC = %d\n", (int) result);

    } // 500ms loop
    
  } // 1ms loop

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
