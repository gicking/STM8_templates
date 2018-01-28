/**
  \file mub_digPoti.h
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief declaration of function to control 20k digital poti
   
  declaration of function to control 20k digital poti via I2C. Type
  Analog Devices AD5280BRUZ20 (Farnell 1438441).
  Connect LCD I2C bus to STM8 SCL/SDA
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MUB_DIGPOTI_
#define _MUB_DIGPOTI_


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

/// I2C address of digital poti
#define MUB_ADDR_I2C_POTI  46



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// digital potentiometer control
uint8_t set_dig_poti(uint8_t res);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MUB_DIGPOTI_
