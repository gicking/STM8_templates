/**
  \file adc2.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of ADC2 functions/macros
   
  implementation of functions for ADC2 measurements in single-shot and continuous mode
  Optional functionality via #define:
    - USE_ADC2_ISR:  use ADC2 end-of conversion interrupt (default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _ADC2_MAIN_
  #include "adc2.h"
#undef _ADC2_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void ADC2_init(ADC2_Mode mode)
   
  \brief initialize ADC2
   
  \param[in] mode       ADC2 conversion mode (see adc2.h)

  initialize ADC2 for single-shot or continuous mode and select channel.
  For accuracy configure for slowest conversion speed (16µs) 
*/
void ADC2_init(ADC2_Mode mode) {
  
  // reset registers
  ADC2.CSR.byte = ADC2_CSR_RESET_VALUE;
  ADC2.CR1.byte = ADC2_CR1_RESET_VALUE;
  ADC2.CR2.byte = ADC2_CR2_RESET_VALUE;

  // keep single shot or set continuous mode
  if (mode == ADC_CONTINUOUS)
    ADC2.CR1.reg.CONT = 1;
  
  // set ADC clock to 1/18*fMaster to minimize influence between channels 
  // Conversion takes 14 cycl -> 16µs
  ADC2.CR1.reg.SPSEL = 7;
  
  // right alignment (read DRL, then DRH), no external trigger
  ADC2.CR2.reg.ALIGN = 1;
  
  // disable all Schmitt trigger, which are recommended for EMC noisy conditions  
  ADC2.TDR.byteL = 0xFF;
  ADC2.TDR.byteH = 0xFF;
  
} // ADC2_init



/**
  \fn uint16_t ADC2_measure_single(uint8_t ch)
   
  \brief measure ADC2 channel
   
  \param ch         ADC2 channel to query
  \return           ADC2 value in INC
  
  measure ADC2 channel in single shot mode.
*/
uint16_t ADC2_measure_single(uint8_t ch) {
 
  uint16_t  result;

  // switch to selected ADC channel 
  ADC2_set_channel(ch);
  
  // clear HW & SW conversion ready flags, start conversion, wait until EOC-ISR finished
  ADC2.CSR.reg.EOC = 0;              // reset HW EOC flag, set by ADC
  ADC2_start_conversion();           // start conversion 
  while(!ADC2.CSR.reg.EOC);          // wait for HW "conversion ready" flag

  // get ADC result (read low byte first for right alignment!)
  result  = ADC2_get_result();
  
  // return result
  return(result);

} // ADC2_measure_single


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
