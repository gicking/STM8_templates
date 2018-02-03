/**
  \file digPoti-AD5282.h
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief declaration of control for digital poti AD5282
   
  declaration of function to control digital poti AD5282 (Farnell 1438442, 200k)
  via I2C. Connect SCL/SDA of digital poti and of STM8 
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _AD5280_H_
#define _AD5280_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "config.h"
#include "misc.h"
#include "i2c.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// I2C address of digital poti. Set custom address in config.h
#if !defined(ADDR_I2C_AD5282)
  #define ADDR_I2C_AD5282  44
#endif


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// 2-channel digital potentiometer control
uint8_t AD5282_set_poti(uint8_t ch, uint8_t res);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _AD5280_H_
