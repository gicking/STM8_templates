/**
  \file timer3.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of timer TIM3 functions/macros for delay and timeout
   
  implementation of timer TIM3 functions for delay and timeout.
  Optional functionality via #define:
    - USE_TIM3_UPD_ISR:    call TIM3 update ISR. Is triggered after timeout_ms() is expired
    - USE_TIM3_CAP_ISR:    call TIM3 capcom ISR. Currently not supported
*/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include "stm8as.h"
#include "config.h"
#define _TIM3_MAIN_          // required for globals in timer3.h
  #include "timer3.h"
#undef _TIM3_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void TIM3_init(void)
   
  \brief init timer 3 (delay* & timeout)
   
  init timer TIM3 (used for delay* and timeout).
*/
void TIM3_init(void) {

  // stop the timer
  TIM3.CR1.reg.CEN = 0;
  
  // reset timeout flag and function pointer for TIM3UPD_ISR
  #ifdef USE_TIM3UPD_ISR
    g_flagTimeout = 0;
    m_TIM3UPD_pFct = TIM3_Default;
  #endif

  // disable single-shot mode (causes SW stalls)
  TIM3.CR1.reg.OPM = 0;
  
  // set prescaler to fclk/2^4 -> 1MHz clock -> 1us resolution
  TIM3.PSCR.reg.PSC = 4;
  
  // init to 1ms timeout (write high byte first)
  TIM3.ARR.byteH = 0x03;
  TIM3.ARR.byteL = 0xE8;

  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = 0;
  TIM3.CNTR.byteL = 0;
      
  // clear status registers
  TIM3.SR1.byte = 0x00;
  TIM3.SR2.byte = 0x00;
  
  // request register update
  TIM3.EGR.reg.UG = 1;

  // disable all TIM3 interrupts
  TIM3.IER.byte = 0x00;

} // TIM3_init



/**
  \fn void delay(uint16_t dt)

  \brief halt code execution for specified milliseconds
   
  \param dt halt duration in ms
   
  code execution is halted for specified number of milliseconds. 
*/
void delay(uint16_t dt) {

  uint16_t  i;
  
  // for simplicity use delayMicroseconds()
  for (i=0; i<dt; i++)
    delayMicroseconds(1000);
    
} // delay



/**
  \fn void delayMicroseconds(uint16_t dt)

  \brief halt code execution for specified microseconds
   
  \param dt halt duration in us
   
  code execution is halted for specified number of microseconds. 
*/
void delayMicroseconds(uint16_t dt) {
  
  // correct for function latency (empirical @ 16MHz)
  dt -= 0;
  
  // stop timer
  TIM3.CR1.reg.CEN = 0;

  // set prescaler to fclk/2^4 -> 1MHz clock -> 1us resolution
  TIM3.PSCR.reg.PSC = 4;
  
  // set timout to dt us (freq_Hz=fclk/(prescaler*ARR)) (write high byte first)
  TIM3.ARR.byteH = (uint8_t) (dt >> 8);
  TIM3.ARR.byteL = (uint8_t) dt;
  
  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = (uint8_t) 0;
  TIM3.CNTR.byteL = (uint8_t) 0;
      
  // disable update interrupt 
  TIM3.IER.reg.UIE = 0;

  // request register update
  TIM3.EGR.reg.UG = 1;
  
  // start the timer
  TIM3.CR1.reg.CEN = 1;
  
  // clear status registers (do this last)
  TIM3.SR1.byte = 0x00;
  
  // wait for overflow (no interrupts!)
  while (!(TIM3.SR1.reg.UIF));
    
} // delayMicroseconds



/**
  \fn void delayNanoseconds(uint16_t dt)

  \brief halt code execution for specified 62.5ns units
   
  \param dt halt duration in 62.5ns units
   
  code execution is halted for specified number of 62.5ns units. 
*/
void delayNanoseconds(uint16_t dt) {
  
  // convert 250ns-->62.5ns
  dt *= 4;

  // stop timer
  TIM3.CR1.reg.CEN = 0;

  // set prescaler to fclk -> 16MHz clock -> 62.5ns resolution
  TIM3.PSCR.reg.PSC = 0;
  
  // set timout to dt*250ns (freq_Hz=fclk/(prescaler*ARR)) (write high byte first)
  TIM3.ARR.byteH = (uint8_t) (dt >> 8);
  TIM3.ARR.byteL = (uint8_t) dt;
  
  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = (uint8_t) 0;
  TIM3.CNTR.byteL = (uint8_t) 0;
      
  // disable update interrupt 
  TIM3.IER.reg.UIE = 0;

  // request register update
  TIM3.EGR.reg.UG = 1;
  
  // start the timer
  TIM3.CR1.reg.CEN = 1;
  
  // clear status registers (do this last)
  TIM3.SR1.byte = 0x00;
  
  // wait for overflow (no interrupts!)
  while (!(TIM3.SR1.reg.UIF));
    
} // delayNanoseconds



/**
  \fn void startTimeout(uint16_t dt)

  \brief start timeout with specified number of ms
   
  \param dt timeout duration in ms (0=forever)
   
  start timeout with specified number of milliseconds. To check for
  timeout query respective timer overflow flag.
*/
void startTimeout(uint16_t dt) {

  // stop timer
  TIM3.CR1.reg.CEN = 0;

  // set prescaler to fclk/2^14 -> ~1kHz clock 
  TIM3.PSCR.reg.PSC = 14;
  
  // set timout to dt ms (freq_Hz=fclk/(prescaler*ARR)) (write high byte first)
  TIM3.ARR.byteH = (uint8_t) (dt >> 8);
  TIM3.ARR.byteL = (uint8_t) dt;
    
  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = (uint8_t) 0;
  TIM3.CNTR.byteL = (uint8_t) 0;

  // request register update
  TIM3.EGR.reg.UG = 1;
    
  // reset update flag
  TIM3.SR1.reg.UIF = 0;
    
  // if update interrupt is configured, activate it (after register update, else ISR)
  #if defined(USE_TIM3UPD_ISR)
    g_flagTimeout    = 0;      ///< reset global timeout flag
    TIM3.IER.reg.UIE = 1;
  #else
    TIM3.IER.reg.UIE = 0;
  #endif
    
  // start the timer only if dt!=0
  if (dt != 0)
    TIM3.CR1.reg.CEN = 1;
  else
    TIM3.CR1.reg.CEN = 0;
  
} // startTimeout



// if any TIM3 interrupt is used
#if defined(USE_TIM3UPD_ISR) || defined(USE_TIM3CAP_ISR)

  /**
    \fn void TIM3_Default(void)
     
    \brief default dummy function for TIM3 ISR
    
    default dummy function for below ISRs. Is faster
    than checking if a function pointer was given or not
  */
  void TIM3_Default(void)
  {
    return;
    
  } // TIM3_Default

#endif // USE_TIM3UPD_ISR || USE_TIM3CAP_ISR



// if TIM3 update interrupt is used
#if defined(USE_TIM3UPD_ISR)

  /**
    \fn void TIM3UPD_attach_interrupt(void (*pFct)(void))
     
    \brief attach/detach function call to below UPD ISR
    
    \param[in]  pFct  function to call in UPD ISR, or NULL to detach
     
    attach/detach function which is called in TIM3 update interrupt
    service routine. Parameter NULL detaches the function again.
  */
  void TIM3UPD_attach_interrupt(void (*pFct)(void)) {
    
    uint8_t   tmp;
    
    // disable interrupt while modifying
    tmp = TIM3.IER.byte;
    TIM3.IER.reg.UIE = 0;

    // attach function to ISR. On NULL reset to default
    if (pFct != 0)
      m_TIM3UPD_pFct = pFct;
    else
      m_TIM3UPD_pFct = TIM3_Default;

    // restore original interrupt setting
    TIM3.IER.byte = tmp;
    
  } // TIM3UPD_attach_interrupt


  /**
    \fn void TIM3UPD_ISR(void)
     
    \brief ISR for TIM3 update
     
    interrupt service routine for TIM3 update.
    Used for optional user function after timeout is expired
  */
  #if defined(__CSMC__)
    @near @interrupt void TIM3UPD_ISR(void)
  #elif defined(__SDCC)
    void TIM3UPD_ISR() __interrupt(__TIM3UPD_VECTOR__)
  #endif
  {
    // clear UPD interrupt flag
    TIM3.SR1.reg.UIF = 0;
   
    // stop the timer after 1 interrupt (single shot)
    TIM3.CR1.reg.CEN = 0;

    // disable update interrupt 
    TIM3.IER.reg.UIE = 0;
    
    // set global timeout flag
    g_flagTimeout = 1;

    // call external function (default function is faster than checking for NULL) 
    (*m_TIM3UPD_pFct)();

    return;

  } // TIM3UPD_ISR

#endif // USE_TIM3UPD_ISR

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
