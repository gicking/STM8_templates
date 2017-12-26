/**
  \file awu.h
   
  \author G. Icking-Konert
  \date 2017-02-3
  \version 0.1
   
  \brief declaration of functions/macros for AWU (auto-wakeup)
   
  declaration of functions/macros for auto-wakeup clock
  Optional functionality via #define:
    - USE_AWU_ISR: call ISR after wakeup time is expired
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _AWU_H_
#define _AWU_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
 
#include <stdint.h>
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// enter CPU halt mode with auto-wake
#define haltAutoWake(ms)           AWU_HaltMode(ms)                     

/// clear AWU interrupt flag
#define AWU_reset_ISR_flag()      { AWU.CSR.reg.AWUF = 0; }
     
     
/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// enter CPU halt mode with auto-wake after N milliseconds
void AWU_HaltMode(uint16_t ms);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _AWU_H_
