/**
  \file beep.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of beeper control
   
  declaration of functions for beeper control to play tone.
  Note that the beeper has very basic functionality and coarse resolution.
  For flexible frequencies and/or duty cycle use timer PWM modules instead.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _BEEP_H_
#define _BEEP_H_

#include <stdint.h>


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// switch off tone
#define noBeep()  beep(0,0);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// play tone via beeper module
void beep(uint16_t freq, uint16_t duration);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _BEEP_H_
