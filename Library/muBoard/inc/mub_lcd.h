/**
  \file mub_lcd.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of 2x16 I2C LCD output functions/macros
   
  declaration of functions for printing strings via I2C to 2x16 LCD
  Batron BTHQ21605V-COG-FSRE-I2C (Farnell 1220409).
  Connect LCD I2C bus to STM8 SCL/SDA, and LCD reset pin to STM8 pin PE3
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MUB_LCD_H_
#define _MUB_LCD_H_


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

/// I2C address of LCD display
#define MUB_ADDR_I2C_LCD  59



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// initialize LCD for output
uint8_t   lcd_init(void);

/// clear LCD
void      lcd_clear(void);

/// print string to LCD diplay
void      lcd_print(uint8_t line, uint8_t col, char *s);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MUB_LCD_H_
