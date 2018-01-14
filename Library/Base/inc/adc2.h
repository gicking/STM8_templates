/**
  \file adc2.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of ADC2 functions/macros
   
  declaration of functions for ADC2 measurements in single-shot and continuous mode
  Optional functionality via #define:
    - USE_ADC_ISR:  use ADC2 end-of conversion interrupt (default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _ADC2_H_
#define _ADC2_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
 
// includes
#include <stdint.h>
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// only if UART1 interrupts are used
#if defined(USE_ADC_ISR)

  /// enable ADC2 EOC interrupt
  #define ADC2_enable_interrupt()  { ADC2.CSR.reg.EOCIE = 1; }

  /// disable ADC2 EOC interrupt
  #define ADC2_disable_interrupt() { ADC2.CSR.reg.EOCIE = 0; }

#endif
 
/// get current ADC channel
#define ADC2_get_channel()        (ADC2.CSR.reg.CH)
  
/// set ADC channel. Minimize AMUX charge injection due to channel switching 
#define ADC2_set_channel(ch)      { if (ADC2.CSR.reg.CH != ch) ADC2.CSR.reg.CH = ch; }
  
/// start ADC conversion. Need to do this 2x (empirically)
#define ADC2_start_conversion()   { ADC2.CR1.reg.ADON=1; ADC2.CR1.reg.ADON=1; }

/// check for ADC conversion ready.
#define ADC2_check_conversion_ready    ADC2.CSR.reg.EOC

/// reset EOC flag (must be done manually)
#define ADC2_reset_ISR_flag()     { ADC2.CSR.reg.EOC = 0; }


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL TYPEDEFS
-----------------------------------------------------------------------------*/

// ADC2 conversion modes
typedef enum {
  ADC_SINGLE_SHOT   = 0,  ///< stop after 1 measurement
  ADC_CONTINUOUS    = 1   ///< perform continuous measurements
} ADC2_Mode;


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// initialize ADC2 for single shot mode or continuous mode
void      ADC2_init(ADC2_Mode mode);

/// measure ADC2 channel once
uint16_t  ADC2_measure_single(uint8_t ch);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL INLINE FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn uint16_t ADC2_get_result(void)
   
  \brief get ADC result
  
  \return 10bit ADC result

  get ADC result (read low byte first for right alignment!)
  Requires ADC2 conversion to be finished.
  Needs to be done inline (not macro) to ensure LB is read first
*/
INLINE uint16_t ADC2_get_result(void) {

  uint16_t  result;
  
  // get ADC result (read low byte first for right alignment!)
  result  =  (uint16_t) ADC2.DR.byteL;
  result += ((uint16_t) ADC2.DR.byteH) << 8;

  return(result);

} // ADC2_get_result()


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _ADC2_H_
