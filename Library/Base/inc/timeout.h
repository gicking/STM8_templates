/**
  \file timeout.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of timeouts based on 1ms clock
   
  declaration of timeouts based on 1ms clock (TIM4 ISR)
  Optional functionality via #define:
    - USE_TIM4_UPD_ISR: required for TIM4 ISR
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _TIMEOUT_H_
#define _TIMEOUT_H_


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// start timeout N (0..NUM_TIMEOUTS-1) with 'ms'
void setTimeout(uint8_t N, uint32_t ms);

/// check timeout N (0..NUM_TIMEOUTS-1)
uint8_t checkTimeout(uint8_t N);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _TIMEOUT_H_
