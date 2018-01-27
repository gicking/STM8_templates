/**
  \file pulse.h
   
  \author G. Icking-Konert
  \date 2018-01-25
  \version 0.1
   
  \brief declaration of pulseIn()
   
  declaration of routine to measure pulse durations (blocking).
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _PULSE_H_
#define _PULSE_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"
#include "gpio.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// measure pulse duration with timepout
uint32_t  pulseIn(PORT_t *pPort, uint8_t pin, uint8_t state, uint16_t timeout);

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _PULSE_H_
