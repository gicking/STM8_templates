/**
  \file low-power.h
   
  \author G. Icking-Konert
  \date 2018-01-20
  \version 0.1
   
  \brief declaration of functions/macros for low-power modes
   
  declaration of functions/macros for low-power modes
  Optional functionality via #define:
    - see ISR of respective wake peripheral!
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _LOW_POWER_H_
#define _LOW_POWER_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
 
#include <stdint.h>
#include "stm8as.h"
#include "config.h"
#include "awu.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// enter WAIT mode: only stop CPU, wake via any interrupt
void lowPower_Wait(void);

/// enter HALT mode: all clocks off, wake only via EXINT
void lowPower_Halt(void);

/// enter active HALT mode: only LSI active, wake via AWU or EXINT
void lowPower_HaltAWU(uint16_t ms);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _LOW_POWER_H_
