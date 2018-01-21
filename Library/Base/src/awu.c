/**
  \file awu.c
   
  \author G. Icking-Konert
  \date 2017-02-3
  \version 0.1
   
  \brief implementation of functions/macros for AWU (auto-wakeup)
   
  implementation of functions/macros for auto-wakeup clock
  Optional functionality via #define:
    - USE_AWU_ISR: call ISR after wakeup time is expired
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "misc.h"
#define _AWU_MAIN_
  #include "awu.h"
#undef _AWU_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void AWU_setTime(uint16_t ms)
   
  \brief configure auto-wake after N milliseconds
  
  \param[in]  ms    sleep duration [ms] within [1;30000]
  
  configure auto-wake after specified number of milliseconds.
  Do not enter HALT mode here.

  \note the LSI low speed clock is quite inaccurate, and the granularity
        of the AWU is coarse -> don't use for time-critical tasks!
*/
void AWU_setTime(uint16_t ms) {

  uint8_t    APR, AWUTB;

  // skip optional measurement of LSI with fCPU

  // clip to valid AWU range
  ms = constrain(ms, 1, 30000);

  // calculate AWU parameters
  if (ms>=5120) {
    AWUTB = 15;
    APR   = (uint8_t) ((ms >> 4)/30L);
  }
  else if (ms>=2048) {
    AWUTB = 14;
    APR   = (uint8_t) ((ms >> 4)/5L);
  }
  else {
    AWUTB = (uint8_t) (log2(ms)+2);
    AWUTB = constrain(AWUTB, 3, 13);
    APR   = (uint8_t) ((((uint32_t) ms) << 8) >> AWUTB);
  }
  APR = min(APR, 0x3E);

  // set (N+2) prescaler for 128kHz LSI clock
  AWU.APR.reg.APR   = APR;
  
  // set AWU counter 2^0..2^12, 5*2^11, 30*2^11
  AWU.TBR.reg.AWUTB = AWUTB;
  
  // enable wake and enable AWU interrupt
  AWU.CSR.reg.AWUEN = 1;
  
} // AWU_setTime
     

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
