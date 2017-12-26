/**
  \file sw_delay.h
   
  \author G. Icking-Konert
  \date 2016-10-18
  \version 0.1
   
  \brief inline function for sw_delay_* via software (no timer)
   
  inline function for software delay (=sw_delay_*) without timer.
  The timing depends on e.g. CPU clock, compiler and optimization level
  -> use with care and check timing!
  Also, if delay functions are interrupted by ISRs, timing is inaccurate
  Benefit is that no timer is required, and that the code overhead is very small
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _SW_DELAY_H_
#define _SW_DELAY_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/

#include <stdint.h>
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn inline void sw_delayNOP(uint8_t num)
   
  \brief inline function to pause code for N nop()
  
  \param[in]  num   number of NOPs to wait [0..255]

  inline function to halt code for specified number of NOPs
  without using timer or interrupts.
  Measured latency/delay @ fcpu=16MHz see below
  
  \note:
    - timing depends on e.g. CPU clock, compiler and optimization level -> check timing
    - if interrupts are enabled, timing can be inaccurate
*/
INLINE void sw_delayNOP(uint8_t num) {

  // Cosmic v4.3.7
    // debug:           750ns + num * 375ns
    // speed optimized: 625ns + num * 375ns
  // SDCC v3.6.5
    // debug+optimized: 1937ns + num * 500ns
  while (num--) {
    NOP;
  };

} // sw_delayNOP()



/**
  \fn inline void sw_delayMicroseconds(uint16_t us)
   
  \brief inline function to pause code for N microseconds
  
  \param[in]  us    time [us] to pause program [0..65535]

  inline function to halt code for specified micros without using timer 
  or interrupts.
  Measured latency/delay @ fcpu=16MHz see below
  
  \note:
    - timing depends on e.g. CPU clock, compiler and optimization level -> check timing
    - if interrupts are enabled, timing can be inaccurate
*/
INLINE void sw_delayMicroseconds(uint16_t us) {

  // number of NOPS empirically optimized for fCPU=16MHz and no ISRs
  while (us--) {
    
    // Cosmic v4.3.7
    #if defined(__CSMC__)
      #if defined(DEBUG)    // debug: 1.36us + n * 0.996us
        NOP;
        NOP;
        NOP;
      #else                 // speed optimized: 0.81us + n * 0.995us
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
      #endif
      
    // SDCC v3.6.5
    #elif defined(__SDCC)
      #if defined(DEBUG)    // debug: 2.24us + n * 0.995us
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
      #else                 // speed optimized: 2.24us + n * 0.995us
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
      #endif
    #endif
    
  }; // while (us--)

} // sw_delayMicroseconds()



/**
  \fn inline void sw_delay(uint32_t ms)
   
  \brief inline function to pause code for N milliseconds
  
  \param[in]  ms    time [ms] to pause program [0..2^32-1]

  inline function to halt code for specified millis without using timer 
  or interrupts.
  Measured latency/delay @ fcpu=16MHz see below
  
  \note:
    - timing depends on e.g. CPU clock, compiler and optimization level -> check timing
    - if interrupts are enabled, timing can be inaccurate
*/
INLINE void sw_delay(uint32_t ms) {

  volatile uint16_t    i;
  
  // values empirically determined for fCPU=16MHz and no ISRs
  #if defined(__CSMC__)       // Cosmic v4.3.7
    #if defined(DEBUG)
      #define LOOP_MAX 1208   // debug
    #else
      #define LOOP_MAX 1308   // speed optimized
    #endif
  #elif defined(__SDCC)       // SDCC v3.6.5
    #if defined(DEBUG)
      #define LOOP_MAX 1236   // debug
    #else
      #define LOOP_MAX 1236   // speed optimized
    #endif
  #endif
  
  // loop over ms loops
  while (ms--) {
    for (i=LOOP_MAX; i; i--) {
      NOP;
    }
  };
  
  // clean up
  #undef LOOP_MAX
  
} // sw_delay()

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _SW_DELAY_H_
