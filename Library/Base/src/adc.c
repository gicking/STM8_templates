/**
  \file adc.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of ADC functions/macros
   
  implementation of functions for ADC measurements in single-shot and continuous mode
  Optional functionality via #define:
    - USE_ADC_ISR:  use ADC interrupt (default is w/o ISR)
    
  Notes: only supports basic functions for ADC1 (advanced) and ADC2 (basic)
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _ADC_MAIN_
  #include "adc.h"
#undef _ADC_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void ADC_init(ADC_Mode mode)
   
  \brief initialize ADC
   
  \param[in] mode       ADC conversion mode (see adc.h)

  initialize ADC for single-shot or continuous mode and select channel.
  For accuracy configure for slowest conversion speed (16µs) 
*/
void ADC_init(ADC_Mode mode) {
  
  // reset registers
  #if defined(HAS_ADC1)
    ADC1.CSR.byte = ADC1_CSR_RESET_VALUE;
    ADC1.CR1.byte = ADC1_CR1_RESET_VALUE;
    ADC1.CR2.byte = ADC1_CR2_RESET_VALUE;
    ADC1.CR3.byte = ADC1_CR3_RESET_VALUE;
    ADC1.TDR.byteL = ADC1_TDRL_RESET_VALUE;
    ADC1.TDR.byteH = ADC1_TDRH_RESET_VALUE;
    ADC1.HTR.byteL = ADC1_HTRL_RESET_VALUE;
    ADC1.HTR.byteH = ADC1_HTRH_RESET_VALUE;
    ADC1.LTR.byteL = ADC1_LTRL_RESET_VALUE;
    ADC1.LTR.byteH = ADC1_LTRH_RESET_VALUE;
    ADC1.AWCR.byteL = ADC1_AWCRL_RESET_VALUE;
    ADC1.AWCR.byteH = ADC1_AWCRH_RESET_VALUE;
  #else
    ADC2.CSR.byte = ADC2_CSR_RESET_VALUE;
    ADC2.CR1.byte = ADC2_CR1_RESET_VALUE;
    ADC2.CR2.byte = ADC2_CR2_RESET_VALUE;
  #endif
  
  // keep single shot or set continuous mode
  if (mode == ADC_CONTINUOUS)
    ADC.CR1.reg.CONT = 1;
  
  // set ADC clock to 1/18*fMaster to minimize influence between channels 
  // Conversion takes 14 cycl -> 16µs
  ADC.CR1.reg.SPSEL = 7;
  
  // right alignment (read DRL, then DRH), no external trigger
  ADC.CR2.reg.ALIGN = 1;
  
  // disable all Schmitt trigger, which is recommended for EMC noisy conditions (skip for simplicity)
  //ADC.TDR.byteL = 0xFF;
  //ADC.TDR.byteH = 0xFF;
  
} // ADC_init



/**
  \fn uint16_t ADC_measure(uint8_t ch)
   
  \brief measure ADC channel (single shot)
   
  \param ch         ADC channel to query
  \return           ADC value in INC
  
  measure ADC channel in single shot mode.
*/
uint16_t ADC_measure(uint8_t ch) {
 
  uint16_t  result;

  // switch to selected ADC channel 
  ADC_set_channel(ch);
  
  // clear HW & SW conversion ready flags, start conversion, wait until EOC-ISR finished
  ADC_reset_conversion_flag();          // reset HW EOC flag, set by ADC
  ADC_start_conversion();               // start conversion 
  while(!ADC_check_conversion_flag());  // wait for HW "conversion ready" flag

  // get ADC result (read low byte first for right alignment!)
  result  = ADC_get_result();
  
  // return result
  return(result);

} // ADC_measure


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
