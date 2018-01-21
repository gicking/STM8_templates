/**********************
  Arduino-like project with setup() & loop().
  Continuously measure via ADC2 and send result via 
  UART1 in ADC interrupt routine (muBoard)
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - initialize ADC2 for continuous mode
  - attach ISR to ADC2_EOC interrupt
  - in ADC ISR send every Nth result via UART1 and blink LED
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "adc2.h"


// misc defines
#define ADC_CH_1    5                   ///< ADC channel to measure (=PB5=AIN5=poti)
#define ADC_CH_2    14                  ///< ADC channel to measure (=PF6=AIN14=io7)
#define LED_GREEN   PORT_H.ODR.bit.b2	  ///< green LED control (0=on)
#define LED_RED     PORT_H.ODR.bit.b3	  ///< red LED control (0=on)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void ADC_ISR(void)
 
  \brief send ADC result via UART
  
  send every Nth ADC result via UART to PC
*/
ISR_HANDLER(ADC_ISR, __ADC_VECTOR__) {

  static uint16_t  result_1=0, result_2=0;  // conversion results for channels
  static uint16_t  count = 0;               // conversion counter

  // reset conversion ready flag (mandatory)
  ADC2_reset_ISR_flag();
  
  // store current result and switch to other ADC channel
  if (ADC2_get_channel() == ADC_CH_1) {
    result_1 = ADC2_get_result();
    ADC2_set_channel(ADC_CH_2);
  }
  else {
    result_2 = ADC2_get_result();
    ADC2_set_channel(ADC_CH_1);
  }
  

  // send every Nth conversion result to PC
  if (++count > 20000) {
    count = 0;
    
    // toggle LED state
    LED_RED ^= 1;
    
    // send both results via UART1 (uses blocking send!)
    printf("val1 = %d, val2 = %d\n", (int) result_1, (int) result_2);

  } // send Nth conversion
  
} // ADC_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // configure pins for LEDs (red=PH3 / green=PH2)
  pinMode(PORT_H, pin2, OUTPUT);
  pinMode(PORT_H, pin3, OUTPUT);
  LED_GREEN = 1;
  LED_RED   = 1;


  // configure ADC poti(=PB5) and io_7(=PF6) as input float
  pinMode(PORT_B, pin5, INPUT);
  pinMode(PORT_F, pin6, INPUT);

  // init ADC2 for continuously measuring poti 
  ADC2_init(ADC_CONTINUOUS);
  ADC2_set_channel(ADC_CH_1);
  
  // avoid spurious interrupts...
  noInterrupts();

  // enable ADC2 conversion complete interrupt
  ADC2_enable_interrupt();
  
  // re-enable interrupts
  interrupts();
    
  // start continuous ADC conversion
  ADC2_start_conversion();

  
  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  
  // dummy. Action happens in ADC2-ISR
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
