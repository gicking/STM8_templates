/**
  \file lcd-BTHQ21605V.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of 2x16 I2C LCD functions for BTHQ21605V-COG-FSRE-I2C
   
  declaration of functions for printing strings via I2C to 2x16 LCD
  Batron BTHQ21605V-COG-FSRE-I2C (Farnell 1220409).
  Connect LCD I2C bus to STM8 SCL/SDA, and LCD reset pin to any STM8 GPIO
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _BTHQ21605V_H_
#define _BTHQ21605V_H_


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

/// I2C address of LCD display. Set custom address in config.h
#if !defined(ADDR_I2C_AD5280)
  #define ADDR_I2C_BTHQ21605V  59
#endif



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// reset and initialize BTHQ21605V LCD for output
uint8_t   BTHQ21605V_lcd_init(PORT_t *pPortRST, uint8_t pinRST);

/// clear BTHQ21605V LCD
void      BTHQ21605V_lcd_clear(void);

/// print string to BTHQ21605V LCD diplay
void      BTHQ21605V_lcd_print(uint8_t line, uint8_t col, char *s);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _BTHQ21605V_H_
