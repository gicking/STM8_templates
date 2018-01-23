/**
  \file power-saving.h
   
  \author G. Icking-Konert
  \date 2018-01-20
  \version 0.1
   
  \brief implementation of functions/macros for low-power modes
   
  implementation of functions/macros for low-power modes
  Optional functionality via #define:
    - see ISR of respective wake peripheral!
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "misc.h"
#define _POWER_SAVING_MAIN_
  #include "power-saving.h"
#undef _POWER_SAVING_MAIN_
#include "awu.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void lowPower_Wait(void)
   
  \brief enter WAIT mode: only stop CPU, wake via any interrupt
  
  Enter CPU WAIT mode: only stop the CPU, all clocks are still running.
  Wake is possible via any internal or external interrupt.
*/
void lowPower_Wait() {

  uint8_t  tmp;
  
  // disable the 1ms interrupt. Remember current state 
  tmp = TIM4.IER.reg.UIE;
  TIM4.IER.reg.UIE = 0;

  // enter WAIT mode
  WAIT_FOR_INTERRUPT;  

  // after wake revert 1ms ISR state
  TIM4.IER.reg.UIE = tmp;

} // lowPower_Wait
     


/**
  \fn void lowPower_ActiveHalt(void)
   
  \brief enter HALT mode: all clocks off, wake only via EXINT
  
  Enter active HALT mode: all clocks off, wake only via EXINT
*/
void lowPower_Halt() {

  // switch off main regulator during halt mode
  CLK.ICKR.reg.REGAH = 1;
  
  // power down flash during halt mode
  FLASH.CR1.reg.AHALT = 1;

  // enter HALT mode
  ENTER_HALT;  

} // lowPower_Halt
       


/**
  \fn void lowPower_HaltAWU(uint16_t ms)
   
  \brief enter active HALT mode: LSI active, wake via AWU or EXINT
  
  \param[in]  ms    sleep duration [ms] within [1;30000]

  Enter active HALT mode: only LSI active, wake via AWU or EXINT.
  If no external interrupt occurs within 'ms', the AWU resumes
  operation automatically.
  
  Note: requires a AWU_ISR to be implemented
*/
void lowPower_HaltAWU(uint16_t ms) {

  // configure AWU for wake after 'ms'
  AWU_setTime(ms);
  
  // enter HALT mode
  lowPower_Halt();

} // lowPower_HaltAWU
   

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
