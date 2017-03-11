/**
  \file gpio.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of functions/macros for GPIO control
   
  implementation of functions/macros for port pin control
  For speed use macros instead of functions where reasonable
  Optional functionality via #define:
    - USE_PORT_ISR: allow attaching user function to port interrupts (EXTIn)
    - USE_TLI_ISR:  allow attaching user function to interrupt on pin PD7 (TLI) 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "gpio.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
#if defined(USE_PORT_ISR) || defined(USE_TLI_ISR)
  volatile void (*m_EXTI0_pFct)(void) = GPIO_Default;     ///< function to call in EXTI0 ISR (port A)
  volatile void (*m_EXTI1_pFct)(void) = GPIO_Default;     ///< function to call in EXTI1 ISR (port B)
  volatile void (*m_EXTI2_pFct)(void) = GPIO_Default;     ///< function to call in EXTI2 ISR (port C)
  volatile void (*m_EXTI3_pFct)(void) = GPIO_Default;     ///< function to call in EXTI3 ISR (port D)
  volatile void (*m_EXTI4_pFct)(void) = GPIO_Default;     ///< function to call in EXTI4 ISR (port E)
  volatile void (*m_TLI_pFct)(void)   = GPIO_Default;     ///< function to call in TLI ISR (pin PD7/TLI)
#endif


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

#if defined(USE_PORT_ISR) || defined(USE_TLI_ISR)

  /**
    \fn void GPIO_Default(void)
     
    \brief default dummy function for EXINTx or TLI
    
    default dummy function for below ISRs. Is faster
    than checking if a function pointer was given or not
  */
  void GPIO_Default(void)
  {
    return;

  } // GPIO_Default

#endif // USE_PORT_ISR || USE_TLI_ISR



#if defined(USE_PORT_ISR)

  /**
    \fn void EXINTxAttachInterrupt(PORT_t *addrPort, void (*pFct)(void), uint8_t edge)
     
    \brief attach/detach function call to port ISR
    
    \param[in]  addrPort  address of port to configure, e.g. &PORT_A (see stm8as.h)
    \param[in]  pFct      name of function to call in ISR
    \param[in]  edge      edge sensitivity. Supported sensitivities are
      - LOW         interrupt on low level. Warning: may stall device!
      - CHANGE      interrupt on both edges
      - RISING      interrupt on rising edge
      - FALLING     interrupt on falling edge
      - NOCHANGE    keep current sensitivity
     
    attach/detach function which is called in respective port interrupt service routine.
    For available ports see datasheet of device.

    \note
      pin interrupts are not en-/disabled by this routine. Use pinMode() in module gpio instead  
  */
  void EXINTxAttachInterrupt(PORT_t *addrPort, void (*pFct)(void), uint8_t edge) {
    
    uint8_t   tmp;
    
    // disable port interrupts for input pins while modifying
    // for output pins slope is modified temporarily, which is uncritical
    tmp = addrPort->CR2.byte;
    addrPort->CR2.byte = addrPort->DDR.byte;
    
    // configure port A ISR
    if (addrPort == &PORT_A) {

      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PAIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PAIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PAIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PAIS = 3;

      // attach user routine to port ISR  
      m_EXTI0_pFct = pFct;

    } // port A

    
    // configure port B ISR
    else if (addrPort == &PORT_B) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PBIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PBIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PBIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PBIS = 3;
    
      // attach user routine to port ISR  
      m_EXTI1_pFct = pFct;
    
    } // port B

    
    // configure port C ISR
    else if (addrPort == &PORT_C) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PCIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PCIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PCIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PCIS = 3;
    
      // attach user routine to port ISR  
      m_EXTI2_pFct = pFct;
      
    } // port C

    
    // configure port D ISR
    else if (addrPort == &PORT_D) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PDIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PDIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PDIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PDIS = 3;
    
      // attach user routine to port ISR  
      m_EXTI3_pFct = pFct;
      
    } // port D

    
    // configure port E ISR
    else if (addrPort == &PORT_E) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR2.reg.PEIS = 0;
      else if (edge == RISING)
        EXTI.CR2.reg.PEIS = 1;
      else if (edge == FALLING)
        EXTI.CR2.reg.PEIS = 2;
      else if (edge == CHANGE)
        EXTI.CR2.reg.PEIS = 3;
    
      // attach user routine to port ISR  
      m_EXTI4_pFct = pFct;
      
    } // port E
  
    // restore original port interrupt setting
    addrPort->CR2.byte = tmp;   
    
  } // EXINTxAttachInterrupt


  
  /**
    \fn void EXTI0_ISR(void)
     
    \brief ISR for port A external interrupt
     
    interrupt service routine for port A interrupt.
    Used for optional user function on external interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void EXTI0_ISR(void)
  #elif defined(__SDCC)
    void EXTI0_ISR() __interrupt(__EXTI0_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via portAttachInterrupt(), call external function
    (*m_EXTI0_pFct)();

    return;

  } // EXTI0_ISR


  
  /**
    \fn void EXTI1_ISR(void)
     
    \brief ISR for port B external interrupt
     
    interrupt service routine for port B interrupt.
    Used for optional user function on external interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void EXTI1_ISR(void)
  #elif defined(__SDCC)
    void EXTI1_ISR() __interrupt(__EXTI1_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via portAttachInterrupt(), call external function
    (*m_EXTI1_pFct)();

    return;

  } // EXTI1_ISR



  /**
    \fn void EXTI2_ISR(void)
     
    \brief ISR for port C external interrupt
     
    interrupt service routine for port C interrupt.
    Used for optional user function on external interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void EXTI2_ISR(void)
  #elif defined(__SDCC)
    void EXTI2_ISR() __interrupt(__EXTI2_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via portAttachInterrupt(), call external function
    (*m_EXTI2_pFct)();

    return;

  } // EXTI2_ISR


  
  /**
    \fn void EXTI3_ISR(void)
     
    \brief ISR for port D external interrupt
     
    interrupt service routine for port D interrupt.
    Used for optional user function on external interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void EXTI3_ISR(void)
  #elif defined(__SDCC)
    void EXTI3_ISR() __interrupt(__EXTI3_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via portAttachInterrupt(), call external function
    (*m_EXTI3_pFct)();

    return;

  } // EXTI3_ISR



  /**
    \fn void EXTI4_ISR(void)
     
    \brief ISR for port E external interrupt
     
    interrupt service routine for port E interrupt.
    Used for optional user function on external interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void EXTI4_ISR(void)
  #elif defined(__SDCC)
    void EXTI4_ISR() __interrupt(__EXTI4_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via portAttachInterrupt(), call external function
    (*m_EXTI4_pFct)();

    return;

  } // EXTI4_ISR

#endif // USE_PORT_ISR



#if defined(USE_TLI_ISR)

  /**
    \fn void pinAttachInterrupt(void (*pFct)(void), uint8_t edge)
     
    \brief attach/detach function call to pin PD7 TLI ISR
    
    \param[in]  pFct      name of function to call in ISR
    \param[in]  edge      edge sensitivity. Supported sensitivities are
      - RISING      interrupt on rising edge
      - FALLING     interrupt on falling edge
      - NOCHANGE    keep current sensitivity
     
    attach/detach function which is called in TLI interrupt service routine for pin PD7.
    
    \note
      - TLI is generally mapped to pin PD7. However in 20-pin package it can be remapped to pin PC3
        using option bytes. This is not supported yet
      - pin interrupts are not en-/disabled by this routine. Use pinMode() in module gpio instead  
  */
  void TLIAttachInterrupt(void (*pFct)(void), uint8_t edge) {
    
    uint8_t   tmp;
    
    // disable pin interrupts while modifying
    // for output, slope is modified temporarily, which is uncritical
    tmp = PORT_D.CR2.bit.b7;
    PORT_D.CR2.bit.b7 = 0;           // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
    
    // set new edge sensitivity
    if (edge == FALLING)
      EXTI.CR2.reg.TLIS = 0;
    else if (edge == RISING)
      EXTI.CR2.reg.TLIS = 1;

    // attach function to pin ISR
    m_TLI_pFct = pFct;
    
    // restore original pin interrupt setting
    PORT_D.CR2.bit.b7 = tmp;   
    
  } // TLIAttachInterrupt


  
  /**
    \fn void TLI_ISR(void)
     
    \brief ISR for pin/TLI interrupt
     
    interrupt service routine for pin/TLI interrupt.
    Used for optional user function on TLI interrupts
  */
  #if defined(__CSMC__)
    @near @interrupt void TLI_ISR(void)
  #elif defined(__SDCC)
    void TLI_ISR() __interrupt(__TLI_VECTOR__)
  #endif
  {
    // clear interrupt flag not required
    
    // if set via pinAttachInterrupt(), call external function
    (*m_TLI_pFct)();

    return;

  } // TLI_ISR

#endif // USE_TLI_ISR

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
