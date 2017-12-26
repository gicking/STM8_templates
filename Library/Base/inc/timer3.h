/**
  \file timer3.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of timer TIM3 functions/macros for delay and timeout
   
  declaration of timer TIM3 functions for delay and timeout.
  Optional functionality via #define:
    - USE_TIM3UPD_ISR:    call TIM3 update ISR. Is triggered after timeout_ms() is expired
    - USE_TIM3CAP_ISR:    call TIM3 capcom ISR. Currently not supported
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
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL VARIABLES
-----------------------------------------------------------------------------*/

// if TIM3_UPD ISR is used, store timeout flag in global variable
#ifdef USE_TIM3_UPD_ISR
  
  // declare or reference to global variables, depending on '_TIM3_MAIN_'
  #if defined(_TIM3_MAIN_)
    volatile uint8_t            g_flagTimeout;     ///< flag timeout. Set in TIM3UPD ISR
  #else // _TIM3_MAIN_
    extern volatile uint8_t     g_flagTimeout;     ///< flag timeout. Set in TIM3UPD ISR
  #endif // _TIM3_MAIN_

#endif // _TIM3_MAIN_


/*-----------------------------------------------------------------------------
    DEFINITION OF GLOBAL MACROS/#DEFINES
-----------------------------------------------------------------------------*/

// use TIM3 update interrupt
#ifdef USE_TIM3_UPD_ISR
  
  /// timeout flag is set in ISR and cleared by user SW
  #define check_timeout()             g_flagTimeout 
  
  /// reset timeout flag
  #define reset_timeout()             g_flagTimeout = 0;
  
  /// attach function call to below UPD ISR
  #define attach_timeout(pFct)        TIM3_UPD_attach_interrupt(pFct);

  /// detach function call to below UPD ISR
  #define detach_timeout()            TIM3_UPD_attach_interrupt(NULL);

  /// detach user function from TIM3UPD ISR
  #define TIM3_UPD_detach_interrupt() TIM3_UPD_attach_interrupt(NULL)

  /// enable TIM3UPD interrupt
  #define TIM3_UPD_enable_interrupt() TIM3.IER.reg.UIE = 1;

  /// disable TIM3UPD interrupt
  #define TIM3_UPD_disable_interrupt() TIM3.IER.reg.UIE = 0;

/// without TIM3UPD interrupt use polling of flag
#else
  #define check_timeout()             (TIM3.SR1.reg.UIF)

#endif // USE_TIM3UPD_ISR


// use TIM3 capture/compare interrupt
#ifdef USE_TIM3_CAP_ISR
  
  #error TIM3_CAP not yet implemented

#endif // USE_TIM3CAP_ISR


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init timer 3 (delay_x/timeout)
void TIM3_init(void);

/// halt code execution for dt milliseconds
void delay(uint16_t dt);

/// halt code execution for dt microseconds
void delayMicroseconds(uint16_t dt);

/// halt code execution for dt*62.5ns
void delayNanoseconds(uint16_t dt);

/// start timeout timer
void startTimeout(uint16_t dt);


// use timer 3 update interrupt
#if defined(USE_TIM3_UPD_ISR)

  /// attach/detach function call to below UPD ISR
  void TIM3_UPD_attach_interrupt(void (*pFct)(void));
  
#endif // USE_TIM3_UPD_ISR


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _TIMER3_H_
