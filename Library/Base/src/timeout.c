/**
  \file timeout.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of timeouts based on 1ms clock
   
  implementation of timeouts based on 1ms clock (TIM4 ISR)
  Optional functionality via #define:
    - USE_TIM4_UPD_ISR: required for TIM4 ISR
	- NUM_TIMEOUTS: custom number of timeouts (default=5)
*/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "timer4.h"
#include "config.h"
#include "timeout.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
// number of user timouts
#if !defined(NUM_TIMEOUTS)
  #define  NUM_TIMEOUTS  5                         
#endif

// end times of timeout [ms]
volatile uint32_t      timeoutEnd[NUM_TIMEOUTS];


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void setTimeout(uint8_t N, uint32_t ms)
   
  \brief start timeout N (0..NUM_TIMEOUTS-1) with 'ms'
  
  \param[in]  N     which timeout to set (0..NUM_TIMEOUTS-1)
  \param[in]  ms    duration[us] of timeout
   
  start timeout N (0..NUM_TIMEOUTS-1) with 'ms'. 
  Requires TIM4 interrupt -> is not vulnerable to 
  interrupts (within limits).
*/
void setTimeout(uint8_t N, uint32_t ms) {

  // index check
  if (N >= NUM_TIMEOUTS)
    return;
 
  // set respective timeout from millis 
  timeoutEnd[N] = millis() + ms;

} // setTimeout



/**
  \fn uint8_t checkTimeout(uint8_t N)
   
  \brief check timeout N (0..NUM_TIMEOUTS-1)
  
  \param[in]  N     which timeout to check (0..NUM_TIMEOUTS-1)

  \return 1 if timeout has passed, else 0
   
  check if timeout N (0..NUM_TIMEOUTS-1) has passed. 
  Requires TIM4 interrupt -> is not vulnerable to 
  interrupts (within limits).
*/
uint8_t checkTimeout(uint8_t N) {

  // index check
  if (N >= NUM_TIMEOUTS)
    return(0);
 
  // check respective timeout with roll-over (see https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover)
  if ((int32_t)(timeoutEnd[N] - millis()) < 0)
    return(1);
  
  // avoid compiler warning
  return(0);

} // checkTimeout


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
