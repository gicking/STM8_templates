/**
  \file shift.h
   
  \author G. Icking-Konert
  \date 2018-01-25
  \version 0.1
   
  \brief declaration of shiftIn() and shiftOut()
   
  declaration of synchronous data transmit (shiftOut) and receive (shiftIn) 
  software implementations.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _SHIFT_H_
#define _SHIFT_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"
#include "gpio.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// synchronous data transmit via software (master mode)
void     shiftOut(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder, uint8_t data);

/// synchronous data receive via software (master mode)
uint8_t  shiftIn(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder);

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _SHIFT_H_
