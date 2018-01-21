/**
  \file stm8_interrupt_vector.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
  \copyright MIT License (MIT)

  \brief declaration of interrupt vector table (Cosmic compiler only)
   
  declaration of interrupt vector table for Cosmic compiler. If not required, replace below ISRs 
  with NonHandledInterrupt (=dummy) service routine. For SDCC just skip the implementation of 
  not required ISR.
*/

// get specified ISR usage
#include <stdlib.h>
#include "config.h"
#include "stm8_interrupt_vector.h"

// only for COSMIC compiler, else skip
#if defined(__CSMC__)

  // declaration of below ISR handler
  typedef void @far (*interrupt_handler_t)(void);
  struct interrupt_vector {
    unsigned char interrupt_instruction;
    interrupt_handler_t interrupt_handler;
  };
    
  // dummy ISR --> do nothing
  @far @interrupt void NonHandledInterrupt (void){
    return;
  }
    
  // startup routine
  extern void _stext();
    
  struct interrupt_vector const _vectab[] = {
    {0x82, (interrupt_handler_t) _stext},                     /* reset */
    {0x82, (interrupt_handler_t) TRAP_ISR},                   /* trap  - Software interrupt  */
    {0x82, (interrupt_handler_t) TLI_ISR},                    /* irq0  - External Top Level interrupt (TLI)  */
    {0x82, (interrupt_handler_t) AWU_ISR},                    /* irq1  - Auto Wake Up from Halt interrupt (AWU) */
    {0x82, (interrupt_handler_t) CLK_ISR},                    /* irq2  - Clock Controller interrupt  */
    {0x82, (interrupt_handler_t) PORTA_ISR},                  /* irq3  - External interrupt 0 (GPIOA) */
    {0x82, (interrupt_handler_t) PORTB_ISR},                  /* irq4  - External interrupt 1 (GPIOB) */
    {0x82, (interrupt_handler_t) PORTC_ISR},                  /* irq5  - External interrupt 2 (GPIOC) */
    {0x82, (interrupt_handler_t) PORTD_ISR},                  /* irq6  - External interrupt 3 (GPIOD) */
    {0x82, (interrupt_handler_t) PORTE_ISR},                  /* irq7  - External interrupt 4 (GPIOE) */
    #ifdef STM8S903
      {0x82, (interrupt_handler_t) PORTF_ISR},                /* irq8  - External interrupt 5 (GPIOF) */
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq9  - reserved */
    #elif defined (STM8S208) || defined (STM8AF52Ax)
      {0x82, (interrupt_handler_t) CAN_RX_ISR},               /* irq8  - CAN interrupt Rx */
      {0x82, (interrupt_handler_t) CAN_TX_ISR},               /* irq9  - CAN interrupt Tx/ER/SC */
    #else
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq8  - reserved */
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq9  - reserved */
    #endif
    {0x82, (interrupt_handler_t) SPI_ISR},                    /* irq10 - SPI End of transfer interrupt */
    {0x82, (interrupt_handler_t) TIM1_UPD_ISR},               /* irq11 - TIM1 Update/Overflow/Trigger/Break interrupt */
    {0x82, (interrupt_handler_t) TIM1_CAPCOM_ISR},            /* irq12 - TIM1 Capture/Compare interrupt */
    #ifdef STM8S903
      {0x82, (interrupt_handler_t) TIM5_UPD_ISR},             /* irq13 - TIM5 Update/overflow */
      {0x82, (interrupt_handler_t) TIM5_CAPCOM_ISR},          /* irq14 - TIM5 Capture/compare */
    #else
      {0x82, (interrupt_handler_t) TIM2_UPD_ISR},             /* irq13 - TIM2 Update/Overflow/Break interrupt */
      {0x82, (interrupt_handler_t) TIM2_CAPCOM_ISR},          /* irq14 - TIM2 Capture/Compare interrupt */
    #endif
    #if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
        defined(STM8S005) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8AF626x)
      {0x82, (interrupt_handler_t) TIM3_UPD_ISR},             /* irq15 - TIM3 Update/overflow */
      {0x82, (interrupt_handler_t) TIM3_CAPCOM_ISR},          /* irq16 - TIM3 Capture/compare */
    #else
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq15  - reserved */
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq16 - reserved */
    #endif
    #if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
        defined(STM8S003) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8S903)
      {0x82, (interrupt_handler_t) UART1_TXE_ISR},            /* irq17 - USART1 Tx send interrupt */
      {0x82, (interrupt_handler_t) UART1_RXF_ISR},            /* irq18 - USART1 Rx receive interrupt */
    #else
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq17  - reserved */
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq18 - reserved */
    #endif
    {0x82, (interrupt_handler_t) I2C_ISR},                    /* irq19 - I2C interrupt */
    #if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x) || defined(STM8S207) || \
        defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
      {0x82, (interrupt_handler_t) UART234_TXE_ISR},          /* irq20 - UART2/3/4 Tx interrupt */
      {0x82, (interrupt_handler_t) UART234_RXF_ISR},          /* irq21 - UART2/3/4 Rx interrupt */
    #else
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq20 - reserved */
      {0x82, (interrupt_handler_t) NonHandledInterrupt},      /* irq21 - reserved */
    #endif
    {0x82, (interrupt_handler_t) ADC_ISR},                    /* irq22 - ADC1/2 end of conversion/Analog watchdog interrupts */
    #if defined(STM8S903) || defined(STM8AF622x)
      {0x82, (interrupt_handler_t) TIM6_UPD_ISR},             /* irq23 - TIM4/6 interrupt */
    #else
      {0x82, (interrupt_handler_t) TIM4_UPD_ISR},             /* irq23 - TIM4/6 interrupt */
    #endif
    {0x82, (interrupt_handler_t) FLASH_ISR},                  /* irq24 - FLASH interrupt */
    {0x82, (interrupt_handler_t) NonHandledInterrupt},        /* irq25 - Reserved */
    {0x82, (interrupt_handler_t) NonHandledInterrupt},        /* irq26 - Reserved */
    {0x82, (interrupt_handler_t) NonHandledInterrupt},        /* irq27 - Reserved */
    {0x82, (interrupt_handler_t) NonHandledInterrupt},        /* irq28 - Reserved */
    {0x82, (interrupt_handler_t) NonHandledInterrupt},        /* irq29 - Reserved */
  };

// end only for Cosmic
#endif // __CSMC__

/*-----------------------------------------------------------------------------
    END OF MODULE 
-----------------------------------------------------------------------------*/
