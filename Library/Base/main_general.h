/**
  \file main_general.h
   
  \author G. Icking-Konert
  \date 2017-02-19
  \version 0.1
   
  \brief declaration of a general main() with minimal initialization
   
  declaration of a general, Arduino-like main() routine with minimal
  initialization. Only FCPU is set to 16MHz and SW-clock ist started.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MAIN_GENERAL_H_
#define _MAIN_GENERAL_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "config.h"     // for optional features
#include "stm8as.h"     // STM8 registers etc.
#include "gpio.h"       // every embedded SW uses pins somehow...
#include "timer4.h"     // required for SW clock
#include "misc.h"       // no code overhead, only inline functions
#include "sw_delay.h"   // no code overhead, only inline functions

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// actual main routine
void main(void);

/// user init routine. Added by user, not main_general.c
void setup(void);

/// user loop routine. Added by user, not main_general.c
void loop(void);


/*-----------------------------------------------------------------------------

    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MAIN_GENERAL_H_
