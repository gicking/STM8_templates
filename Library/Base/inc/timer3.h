/**
  \file timer3.h
   
  \author G. Icking-Konert
  \date 2017-12-30
  \version 0.1
   
  \brief declaration of TIM3 functions/macros 
   
  declaration of timer TIM3 functions, currently for (mutually exclusive)
    - generating PWM signals
    - high accuracy delay* functions
  Optional functionality via #define:
    - USE_TIM3_UPD_ISR:    call TIM4 update/overflow ISR
    - USE_TIM3_CAPCOM_ISR: call TIM3 capture/compare ISR
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _TIMER3_H_
#define _TIMER3_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/

#include <stdint.h>
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    DEFINITION OF GLOBAL MACROS/#DEFINES
-----------------------------------------------------------------------------*/

/// delay code execution for 'ms' using HW timer. Optionally use other timer*.h (except TIM4)
#define highRez_delay(t)                TIM3_delay(t)

/// delay code execution for 'us' using HW timer. Optionally use other timer*.h (except TIM4)
#define highRez_delayMicroseconds(t)    TIM3_delayMicroseconds(t)

/// delay code execution for dt*62.5ns using HW timer. Optionally use other timer*.h (except TIM4)
#define highRez_delayNanoseconds(t)     TIM3_delayNanoseconds(t)

// only with TIM3 update/overflow interrupt
#ifdef USE_TIM3_UPD_ISR

  /// enable TIM3UPD interrupt
  #define TIM3_enable_UPD_interrupt()  TIM3.IER.reg.UIE = 1;

  /// disable TIM3UPD interrupt
  #define TIM3_disable_UPD_interrupt() TIM3.IER.reg.UIE = 0;

#endif // USE_TIM3UPD_ISR


// only with TIM3 capture/compare interrupt
#ifdef USE_TIM3_CAPCOM_ISR
  
  #error TIM3_CAPCOM_ISR not yet implemented

#endif // USE_TIM3_CAPCOM_ISR


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init timer 3
void TIM3_init(void);

/// delay code execution for 'ms' using timer 3
void TIM3_delay(uint32_t ms);

/// delay code execution for 'us' using timer 3
void TIM3_delayMicroseconds(uint16_t dt);

/// delay code execution for dt*62.5ns using timer 3
void TIM3_delayNanoseconds(uint16_t dt);

/// set PWM frequency [0.01Hz] for all channels
void TIM3_setFrequency(uint32_t centHz);

/// set PWM duty cycle [0.1%] for single compare channel
void TIM3_setDutyCycle(uint8_t channel, uint16_t deciPrc);

/// set PWM duty cycle [0.1%] for all compare channels
void TIM3_setDutyCycleAll(uint16_t *deciPrc);

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _TIMER3_H_
