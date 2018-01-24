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


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

#if defined(USE_PORTA_ISR) || defined(USE_PORTB_ISR) || defined(USE_PORTC_ISR) || defined(USE_PORTD_ISR) || \
    defined(USE_PORTE_ISR) || defined(USE_PORTF_ISR) || defined(USE_PORT_ISR)

  /**
    \fn void configEdgeExint(void *addrPort, uint8_t edge)
     
    \brief configure edge sensitivity for EXINT
    
    \param[in]  addrPort  address of port to configure, e.g. PORT_A (see stm8as.h)
    \param[in]  edge      edge sensitivity. Supported sensitivities are
      - LOW         interrupt on low level. Warning: may stall device!
      - CHANGE      interrupt on both edges
      - RISING      interrupt on rising edge
      - FALLING     interrupt on falling edge
      - NOCHANGE    keep current sensitivity
     
    configure edge sensitivity for port interrupt service routine.
    For available ports see datasheet of device.

    \note
      pin interrupts are not en-/disabled by this routine. Use pinMode() in module gpio instead  
  */
  void configEdgeExint(void *addrPort, uint8_t edge) {
    
    uint8_t   tmp;
    
    // disable port interrupts for input pins while modifying
    // for output pins slope is modified temporarily, which is uncritical
    tmp = ((PORT_t*) addrPort)->CR2.byte;
    ((PORT_t*) addrPort)->CR2.byte = ((PORT_t*) addrPort)->DDR.byte;
    
    // configure port A ISR
    if (addrPort == PORT_A) {

      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PAIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PAIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PAIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PAIS = 3;

    } // port A

    
    // configure port B ISR
    else if (addrPort == PORT_B) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PBIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PBIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PBIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PBIS = 3;
    
    } // port B

    
    // configure port C ISR
    else if (addrPort == PORT_C) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PCIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PCIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PCIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PCIS = 3;
    
    } // port C

    
    // configure port D ISR
    else if (addrPort == PORT_D) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR1.reg.PDIS = 0;
      else if (edge == RISING)
        EXTI.CR1.reg.PDIS = 1;
      else if (edge == FALLING)
        EXTI.CR1.reg.PDIS = 2;
      else if (edge == CHANGE)
        EXTI.CR1.reg.PDIS = 3;
    
    } // port D

    
    // configure port E ISR
    else if (addrPort == PORT_E) {
      
      // set new edge sensitivity
      if (edge == LOW)
        EXTI.CR2.reg.PEIS = 0;
      else if (edge == RISING)
        EXTI.CR2.reg.PEIS = 1;
      else if (edge == FALLING)
        EXTI.CR2.reg.PEIS = 2;
      else if (edge == CHANGE)
        EXTI.CR2.reg.PEIS = 3;
      
    } // port E


    // configure port F ISR (device dependent)
    #ifdef STM8S903
      else if (addrPort == PORT_F) {
        
        // set new edge sensitivity
        if (edge == LOW)
          EXTI.CR2.reg.PFIS = 0;
        else if (edge == RISING)
          EXTI.CR2.reg.PFIS = 1;
        else if (edge == FALLING)
          EXTI.CR2.reg.PFIS = 2;
        else if (edge == CHANGE)
          EXTI.CR2.reg.PFIS = 3;
        
      } // port F
    #endif // STM8S903
      
    // restore original port interrupt setting
    ((PORT_t*) addrPort)->CR2.byte = tmp;   
    
  } // configEdgeExint

#endif // USE_PORT_ISR



#if defined(USE_TLI_ISR)

  /**
    \fn void configEdgeTLI(uint8_t edge)
     
    \brief configure edge sensitivity for TLI
    
    \param[in]  edge      edge sensitivity. Supported sensitivities are
      - RISING      interrupt on rising edge
      - FALLING     interrupt on falling edge
     
    configure edge sensitivity for pin interrupt (TLI) service routine.
    For available pins see datasheet of device.

    \note
      pin interrupts are not en-/disabled by this routine. Use pinMode() in module gpio instead  
  */
  void configEdgeTLI(uint8_t edge) {
    
    uint8_t   tmp;
    
    // disable port D interrupts (TLI=PD7) while modifying
    // for output pins slope is modified temporarily, which is uncritical
    tmp = ((PORT_t*) &PORT_D)->CR2.byte;
    
    // set TLI edge sensitivity (only rising and falling)
    if (edge == RISING)
      EXTI.CR2.reg.TLIS = 1;
    else
      EXTI.CR2.reg.TLIS = 0;
        
    // restore original port interrupt setting
    ((PORT_t*) &PORT_D)->CR2.byte = tmp;   
      
  } // configEdgeTLI

#endif // USE_TLI_ISR

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
