/**
  \file adc.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of ADC functions/macros
   
  declaration of functions for ADC measurements in single-shot and continuous mode
  Optional functionality via #define:
    - USE_ADC_ISR:  use ADC interrupt (default is w/o ISR)
    
  Notes: only supports basic functions for ADC1 (advanced) and ADC2 (basic)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _ADC_H_
#define _ADC_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
 
// includes
#include <stdint.h>
#include "config.h"
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// anonymize ADC1/ADC2 registers (are identical apart from additional regs for ADC1)
#if defined(HAS_ADC1)
  #define ADC   ADC1
#elif defined(HAS_ADC2)
  #define ADC   ADC2
#else
  #error selected device has no ADC. Check configuration!
#endif


// only if ADC interrupts are used
#if defined(USE_ADC_ISR)

  /// enable ADC EOC interrupt
  #define ADC_enable_interrupt()  ADC.CSR.reg.EOCIE = 1

  /// disable ADC EOC interrupt
  #define ADC_disable_interrupt() ADC.CSR.reg.EOCIE = 0

#endif
 

/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL TYPEDEFS
-----------------------------------------------------------------------------*/

// ADC conversion modes
typedef enum {
  ADC_SINGLE_SHOT   = 0,  ///< stop after 1 measurement
  ADC_CONTINUOUS    = 1   ///< perform continuous measurements
} ADC_Mode;


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// initialize ADC for single shot mode or continuous mode
void      ADC_init(ADC_Mode mode);

/// measure ADC channel once
uint16_t  ADC_measure(uint8_t ch);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL INLINE FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn void ADC_set_channel(uint8_t channel)
   
  \brief set ADC channel
  
  \param[in] new ADC channel
  
  set new ADC channel. Minimize AMUX changes to reduce charge injection
*/
INLINE void ADC_set_channel(uint8_t channel) {

  // set ADC channel. Minimize AMUX charge injection due to channel switching 
  if (ADC.CSR.reg.CH != channel)
    ADC.CSR.reg.CH = channel;

} // ADC_set_channel()



/**
  \fn uint8_t ADC_get_channel(void)
   
  \brief get current ADC channel
  
  \return active channel

  get currently set ADC channel. 
*/
INLINE uint8_t ADC_get_channel(void) {

  // return active ADC channel
  return((uint8_t)(ADC.CSR.reg.CH));

} // ADC_get_channel()



/**
  \fn void ADC_start_conversion(void)
   
  \brief start ADC conversion
  
  start ADC conversion in continuous mode.
*/
INLINE void ADC_start_conversion(void) {

  // start ADC conversion. Need to do this 2x (empirically)
  ADC.CR1.reg.ADON=1;
  ADC.CR1.reg.ADON=1;

} // ADC_start_conversion()



/**
  \fn void ADC_stop_conversion(void)
   
  \brief stop ADC conversion
  
  stop ADC conversion in continuous mode.
*/
INLINE void ADC_stop_conversion(void) {

  // stop ADC conversion
  ADC.CR1.reg.ADON=0;

} // ADC_stop_conversion()



/**
  \fn uint8_t ADC_check_conversion_flag(void)
   
  \brief check ADC conversion done
  
  \return conversion ready?

  read ADC end-of-conversion flag
*/
INLINE uint8_t ADC_check_conversion_flag(void) {

  // return ADC EOC flag
  return((uint8_t)(ADC.CSR.reg.EOC));

} // ADC_check_conversion_flag()



/**
  \fn void ADC_reset_conversion_flag(void)
   
  \brief reset ADC conversion flag
  
  reset ADC end-of-conversion flag. Is mandatory in continuous mode
*/
INLINE void ADC_reset_conversion_flag(void) {

  // reset ADC EOC flag
  ADC.CSR.reg.EOC = 0;

} // ADC_reset_conversion_flag()



/**
  \fn uint16_t ADC_get_result(void)
   
  \brief get ADC result
  
  \return 10bit ADC result

  get ADC result (read low byte first for right alignment!)
  Requires ADC conversion to be finished.
  Needs to be done inline (not macro) to ensure LB is read first
*/
INLINE uint16_t ADC_get_result(void) {

  uint16_t  result;
  
  // get ADC result (read low byte first for right alignment!)
  result  =  (uint16_t) ADC.DR.byteL;
  result += ((uint16_t) ADC.DR.byteH) << 8;

  return(result);

} // ADC_get_result()


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _ADC_H_
