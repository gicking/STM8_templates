/**
  \file mub_diffAmp.h
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief declaration of function to control the differential amplifier
   
  declaration of function to control the differential amplifier via I2C. Type
  OPAMP LM2904 (Farnell 2450774) with feedback via digital poti AD5282BRUZ200 (Farnell 1438442).
  Connect SCL/SDA of digital poti and of STM8 
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MUB_DIFFAMP_
#define _MUB_DIFFAMP_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "config.h"
#include "stm8as.h"
#include "misc.h"
#include "digPoti-AD5282.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// differential amplifier control
uint8_t set_diff_amplifier(uint8_t gain);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MUB_DIFFAMP_
