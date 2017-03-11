/**
  \file putchar.h
   
  \author G. Icking-Konert
  \date 2015-04-09
  \version 0.1
   
  \brief declaration of required putchar() function
   
  declaration of putchar() function required for stdio.h
  functions, e.g. printf(). Is dummy (required by Makefile)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _CUSTOM_PUTCHAR_H_
#define _CUSTOM_PUTCHAR_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// detach send function. Is 
#define putcharDetach()  putcharAttach(putchar_Default)
  

/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// dummy putchar() send function
void putchar_Default(uint8_t data);

/// set putchar() send function
void putcharAttach(void (*pFct)(uint8_t));

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
#endif  // _CUSTOM_PUTCHAR_H_
