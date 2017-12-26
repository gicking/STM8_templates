/**
  \file tone.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of beeper control
   
  declaration of functions for beeper control to play tone.
  Note that the beeper has very coarse resolution!
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _TONE_H_
#define _TONE_H_

#include <stdint.h>


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// switch off tone
#define noTone()  tone(0,0);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// play tone via beeper module
void tone(uint16_t freq, uint16_t duration);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _TONE_H_
