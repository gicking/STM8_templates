/**
  \file getchar.h
   
  \author G. Icking-Konert
  \date 2017-04-15
  \version 0.1
   
  \brief declaration of getchar() function for gets()
   
  declaration of getchar() function required for stdio.h
  functions, e.g. gets(). 
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _CUSTOM_GETCHAR_H_
#define _CUSTOM_GETCHAR_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// detach receive function 
#define getcharDetach()  getcharAttach(getchar_Default)
  

/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// dummy getchar() receive function
uint8_t getchar_Default(void);

/// set getchar() receive function
void getcharAttach(uint8_t (*pFct)(void));

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
#endif  // _CUSTOM_GETCHAR_H_
