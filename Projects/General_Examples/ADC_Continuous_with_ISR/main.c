/**********************
  Arduino-like project with setup() & loop().
  Continuously measure ADC channels 0..7 in background
  via ADC interrupt. That way, recent ADC results are
  always available.
  Functionality:
  - initialize ADC for continuous mode
  - attach ISR to ADC_EOC interrupt
  - in ADC ISR sweep through ADC channels
  - send out ADC results via UART on user request
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "adc.h"             // ADC measurements
#include "uart1.h"           // UART1 communication
#include "putchar.h"         // for printf()
#include "getchar.h"         // for gets()


/*----------------------------------------------------------
    GLOBALS
----------------------------------------------------------*/
uint16_t   valADC[8] = {0,0,0,0,0,0,0,0};


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void ADC_ISR(void)
 
  \brief send ADC result via UART
  
  send every Nth ADC result via UART to PC
*/
ISR_HANDLER(ADC_ISR, __ADC_VECTOR__) {

  // reset conversion ready flag (mandatory)
  ADC_reset_conversion_flag();
  
  // get current ADC result and switch to other channel
  valADC[ADC_get_channel()] = ADC_get_result();

  // advance to next channel with overflow
  if (ADC_get_channel() == 7)
    ADC_set_channel(0); 
  else
    ADC_set_channel(ADC_get_channel()+1);
  
} // ADC_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // after reset I/Os are input float -> no need to re-configure

  // init ADC for continuously measuring poti 
  ADC_init(ADC_CONTINUOUS);
  ADC_set_channel(0);
  
  // avoid spurious interrupts...
  noInterrupts();

  // enable ADC conversion complete interrupt
  ADC_enable_interrupt();
  
  // re-enable interrupts
  interrupts();
    
  // start continuous ADC conversion
  ADC_start_conversion();

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // use UART1 blocking read for gets() input
  getcharAttach(UART1_read);
  
  // wait a it for console to launch
  sw_delay(1000);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  char    num;

  // read a string via UART1
  printf("Enter a number: ");
  num = getchar() - 48;
  
  // print ADC result via UART1
  if (inRange(num,0,7))
    printf("\nADC channel %d: %d INC\n\n", (int) num, (int) valADC[num]);
  else
    printf("\nADC channel %d outside 0..7\n\n", (int) num);
    
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
