/**
  \file stopwatch.c
   
  \author G. Icking-Konert
  \date 2018-01-18
  \version 0.1
   
  \brief implementation of stopwatches based on 1ms clock
   
  implementation of stopwatches based on 1ms clock (TIM4 ISR)
  Optional functionality via #define:
    - USE_TIM4_UPD_ISR: required for TIM4 ISR
	- NUM_STOPWATCH: custom number of stopwatches (default=5)
*/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "timer4.h"
#include "config.h"
#include "stopwatch.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
// number of user stopwatches
#if !defined(NUM_STOPWATCH)
  #define  NUM_STOPWATCH  5                         
#endif

// end times of timeout [ms]
volatile uint32_t      stopwatch[NUM_STOPWATCH];


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void startStopwatch(uint8_t N)
   
  \brief start stopwatch N (0..NUM_STOPWATCH-1)
  
  \param[in]  N     which stopwatch to start (0..NUM_STOPWATCH-1)
   
  start stopwatch N (0..NUM_STOPWATCH-1) from millis(). 
  Requires TIM4 interrupt -> is not vulnerable to 
  interrupts (within limits).
*/
void startStopwatch(uint8_t N) {

  // index check
  if (N >= NUM_STOPWATCH)
    return;
 
  // start respective stopwatch from millis
  stopwatch[N] = millis();

} // startStopwatch



/**
  \fn uint32_t getStopwatch(uint8_t N)
   
  \brief read stopwatch N (0..NUM_STOPWATCH-1)
  
  \param[in]  N     which stopwatch to read (0..NUM_STOPWATCH-1)

  \return millis() since start of stopwatch N
   
  read millisecods since stopwatch N (0..NUM_TIMEOUTS-1) was started. 
  Requires TIM4 interrupt -> is not vulnerable to interrupts (within limits).
*/
uint32_t getStopwatch(uint8_t N) {

  // index check
  if (N >= NUM_STOPWATCH)
    return(UINT32_MAX);

  // read respective stopwatch with roll-over
  return(millis() - stopwatch[N]);
  
} // getStopwatch

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
