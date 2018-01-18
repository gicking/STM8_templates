/**
  \file stopwatch.h
   
  \author G. Icking-Konert
  \date 2018-01-18
  \version 0.1
   
  \brief declaration of stopwatches based on 1ms clock
   
  declaration of stopwatches based on 1ms clock (TIM4 ISR)
  Optional functionality via #define:
    - USE_TIM4_UPD_ISR: required for TIM4 ISR
	- NUM_STOPWATCH: custom number of stopwatches (default=5)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// start stopwatch N (0..NUM_STOPWATCH-1)
void    startStopwatch(uint8_t N);

/// read stopwatch N (0..NUM_STOPWATCH-1)
uint32_t getStopwatch(uint8_t N);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _STOPWATCH_H_
