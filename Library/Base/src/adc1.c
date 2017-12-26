/**
  \file adc1.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of ADC1 functions/macros
   
  implementation of functions for ADC1 measurements in single-shot mode
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "adc1.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void adc1_init(void)
   
  \brief initialize ADC
   
  initialize ADC1 for single-shot measurements. Default to channel AIN0
*/
void adc1_init() {

  // reset channel selection [3:0], no ADC interrupt [5]
  ADC1.CSR.byte = 0x00;
  
  // set single shot mode
  ADC1.CR1.reg.CONT = 0;
  
  // set ADC clock 1/12*fMaster (<2MHz)
  ADC1.CR1.reg.SPSEL = 6;
  
  // right alignment (read DRL, then DRH), no external trigger
  ADC1.CR2.reg.ALIGN = 1;
  
  // disable Schmitt trigger only for measurement channels
  //ADC1.TDR = 0xFFFF;
  
  // ADC module on
  ADC1.CR1.reg.ADON = 1; 
  
} // adc1_init



/**
  \fn uint16_t adc1_measure(uint8_t ch)
   
  \brief measure ADC1 channel
   
  \param ch         ADC1 channel to query
  \return           ADC1 value in INC
  
  measure ADC1 channel in single shot mode.
*/
uint16_t adc1_measure(uint8_t ch) {
 
  uint16_t result;
 
  // switch to ADC channel if required. Else skip to avoid AMUX charge injection
  if (ADC1.CSR.reg.CH != ch)
    ADC1.CSR.reg.CH = ch;
  
  // clear conversion ready flag, start conversion, wait until conversion done
  ADC1.CSR.reg.EOC  = 0;
  ADC1.CR1.reg.ADON = 1;             // start conversion 
  while(!ADC1.CSR.reg.EOC);          // wait for "conversion ready" flag
  
  // get ADC result (read low byte first for right alignment!)
  result  = (uint16_t) (ADC1.DR.byteL);
  result += ((uint16_t)(ADC1.DR.byteH)) << 8;
  
  // don't switch to default channel to avoid AMUX charge injection
  
  // return result
  return(result);

} // adc1_measure


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
