/**
  \file main_muBoard.h
   
  \author G. Icking-Konert
  \date 2017-02-19
  \version 0.1
   
  \brief declaration of a general main() with board specific initialization
   
  declaration of a muBoard-specific, Arduino-like main() routine with
  initialization. 
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MAIN_MUBOARD_H_
#define _MAIN_MUBOARD_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <ctype.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"                 // for optional features
#include "stm8as.h"                 // STM8 registers etc.
#include "gpio.h"                   // every embedded SW uses pins somehow...
#include "timer4.h"                 // required for SW clock
#include "adc.h"                    // measure routines for ADC
#include "uart1.h"                  // UART1 communication to PC
#include "putchar.h"                // for printf()
#include "spi.h"                    // SPI communication
#include "i2c.h"                    // I2C communication
#include "eeprom.h"                 // for flash log
#include "misc.h"                   // no code overhead, only inline functions
#include "sw_delay.h"               // no code overhead, only inline functions
#include "timeout.h"                // simple scheduler
#include "stopwatch.h"              // simple scheduler (2)
#include "stm8_interrupt_vector.h"  // ISR routines. For SDCC: must be included in source containing main()

#include "digPoti-AD5280.h"
#include "lcd-BTHQ21605V.h"

#include "mub_error_codes.h"
#include "mub_io.h"
#include "mub_diffAmp.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL VARIABLES
-----------------------------------------------------------------------------*/

// declare or reference to global variables, depending on '_MUBOARD_MAIN_'
#if defined(_MUBOARD_MAIN_)
  volatile uint8_t            g_Vdd;        ///< Vdd=5V(=5) or 3.3V(=3)
#else // _TIM4_MAIN_
  extern volatile uint8_t     g_Vdd;
#endif // _TIM4_MAIN_


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// for convenience rename muBoard_resetHardware
#define resetHW()                     muBoard_resetHardware()

/// for convenience rename set_dig_poti(), and invert for channel A
#define set_dig_poti(res)             AD5280_set_poti((255-res))

/// for convenience rename lcd_init()
#define lcd_init(pPortRST,pinRST)     BTHQ21605V_lcd_init(pPortRST, pinRST)

/// for convenience rename lcd_clear()
#define lcd_clear()                   BTHQ21605V_lcd_clear()

/// for convenience rename lcd_init()
#define lcd_print(line,col, s)        BTHQ21605V_lcd_print(line,col, s)

/// for convenience rename g_Vdd
#define voltVdd                       g_Vdd


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// board initialization
void muBoard_resetHardware(void);

/// actual main routine
void main(void);

/// user init routine. Added by user, not main_muBoard.c
void setup(void);

/// user loop routine. Added by user, not main_muBoard.c
void loop(void);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MAIN_MUBOARD_H_
