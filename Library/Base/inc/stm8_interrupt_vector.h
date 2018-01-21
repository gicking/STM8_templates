/**
  \file stm8_interrupt_vector.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
  \copyright MIT License (MIT)

  \brief declaration of interrupt vector table
   
  declaration of interrupt vector table. For SDCC this needs to be included by
  the source file containing main(), else ISRs are not called!
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _INTERRUPT_VECTOR_H_
#define _INTERRUPT_VECTOR_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "config.h"
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// COSMIC compiler specific
#if defined(__CSMC__)

  // macros to unify ISR declaration and implementation
  #define ISR_HANDLER(a,b) @far @interrupt void a(void)
  #define ISR_HANDLER_TRAP(a) void @far @interrupt a(void)

// SDCC compiler specific
#elif defined(__SDCC)

  // macros to unify ISR declaration and implementation
  #define ISR_HANDLER(a,b) void a(void) __interrupt(b)
  #if defined(USE_TRAP)
    #if SDCC_VERSION >= 30403  // traps require >=v3.4.3
      #define ISR_HANDLER_TRAP(a) void a() __trap 
    #else
      #error traps require SDCC >=3.4.3. Please update!
    #endif
  #endif 

#endif // __SDCC


/// trap - Software interrupt (call TRIGGER_TRAP to trip)
#if defined(USE_TRAP)
  ISR_HANDLER_TRAP(TRAP_ISR);
#else
  #define TRAP_ISR                  NonHandledInterrupt              
#endif


/// irq0 - External Top Level interrupt (TLI) for pin PD7
#if defined(USE_TLI_ISR)
  #define __TLI_VECTOR__            0
  ISR_HANDLER(TLI_ISR, __TLI_VECTOR__);
#else
  #define TLI_ISR                   NonHandledInterrupt              
#endif


/// irq1 - Auto Wake Up from Halt interrupt (AWU)
#if defined(USE_AWU_ISR)
  #define __AWU_VECTOR__            1
  ISR_HANDLER(AWU_ISR, __AWU_VECTOR__);
#else
  #define AWU_ISR                   NonHandledInterrupt              
#endif


/// irq2 - Clock Controller interrupt
#if defined(USE_CLK_ISR)
  #define __CLK_VECTOR__            2
  ISR_HANDLER(CLK_ISR, __CLK_VECTOR__);
#else
  #define CLK_ISR                   NonHandledInterrupt              
#endif


/// irq3 - External interrupt 0 (GPIOA)
#if defined(USE_PORTA_ISR)
  #define __PORTA_VECTOR__          3
  ISR_HANDLER(PORTA_ISR, __PORTA_VECTOR__);
#else
  #define PORTA_ISR                 NonHandledInterrupt              
#endif


/// irq4 - External interrupt 1 (GPIOB)
#if defined(USE_PORTB_ISR)
  #define __PORTB_VECTOR__          4
  ISR_HANDLER(PORTB_ISR, __PORTB_VECTOR__);
#else
  #define PORTB_ISR                 NonHandledInterrupt              
#endif


/// irq5 - External interrupt 2 (GPIOC)
#if defined(USE_PORTC_ISR)
  #define __PORTC_VECTOR__          5
  ISR_HANDLER(PORTC_ISR, __PORTC_VECTOR__);
#else
  #define PORTC_ISR                 NonHandledInterrupt              
#endif


/// irq6 - External interrupt 3 (GPIOD)
#if defined(USE_PORTD_ISR)
  #define __PORTD_VECTOR__          6
  ISR_HANDLER(PORTD_ISR, __PORTD_VECTOR__);
#else
  #define PORTD_ISR                 NonHandledInterrupt              
#endif
  

/// irq7 - External interrupt 4 (GPIOE)
#if defined(USE_PORTE_ISR)
  #define __PORTE_VECTOR__          7
  ISR_HANDLER(PORTE_ISR, __PORTE_VECTOR__);
#else
  #define PORTE_ISR                 NonHandledInterrupt              
#endif


/// irq8 - External interrupt 5 (GPIOF) or CAN receive interrupt -- device dependent
#ifdef STM8S903
  #if defined(USE_PORTF_ISR)
    #define __PORTF_VECTOR__        8
    ISR_HANDLER(PORTF_ISR, __PORTF_VECTOR__);
  #else
    #define PORTF_ISR               NonHandledInterrupt              
  #endif
#elif defined (STM8S208) || defined (STM8AF52Ax)
   #if defined(USE_CAN_RX_ISR)
   #define __CAN_RX_VECTOR__        8
    ISR_HANDLER(CAN_RX_ISR, __CAN_RX_VECTOR__);
  #else
    #define CAN_RX_ISR              NonHandledInterrupt              
  #endif
#endif


/// irq9 - CAN transmit interrupt -- device dependent
#if defined (STM8S208) || defined (STM8AF52Ax)
  #if defined(USE_CAN_TX_ISR)
    #define __CAN_TX_VECTOR__       9
    ISR_HANDLER(CAN_TX_ISR, __CAN_TX_VECTOR__);
  #else
    #define CAN_TX_ISR              NonHandledInterrupt              
  #endif
#endif


/// irq10 - SPI End of transfer interrupt
#if defined(USE_SPI_ISR)
  #define __SPI_VECTOR__            10
  ISR_HANDLER(SPI_ISR, __SPI_VECTOR__);
#else
  #define SPI_ISR                   NonHandledInterrupt              
#endif
 

/// irq11 - TIM1 Update/Overflow/Trigger/Break interrupt
#if defined(USE_TIM1_UPD_ISR)
  #define __TIM1_UPD_VECTOR__       11
  ISR_HANDLER(TIM1_UPD_ISR, __TIM1_UPD_VECTOR__);
#else
  #define TIM1_UPD_ISR              NonHandledInterrupt              
#endif
 

/// irq12 - TIM1 Capture/Compare interrupt
#if defined(USE_TIM1_CAPCOM_ISR)
  #define __TIM1_CAPCOM_VECTOR__    12
  ISR_HANDLER(TIM1_CAPCOM_ISR, __TIM1_CAPCOM_VECTOR__);
#else
  #define TIM1_CAPCOM_ISR           NonHandledInterrupt              
#endif


/// irq13 - TIM5 or TIM2 Update/overflow interrupt -- device dependent
#ifdef STM8S903
  #if defined(USE_TIM5_UPD_ISR)
    #define __TIM5_UPD_VECTOR__     13
    ISR_HANDLER(TIM5_UPD_ISR, __TIM5_UPD_VECTOR__);
  #else
    #define TIM5_UPD_ISR            NonHandledInterrupt              
  #endif
#else
  #if defined(USE_TIM2_UPD_ISR)
    #define __TIM2_UPD_VECTOR__     13
    ISR_HANDLER(TIM2_UPD_ISR, __TIM2_UPD_VECTOR__);
  #else
    #define TIM2_UPD_ISR            NonHandledInterrupt              
  #endif
#endif


/// irq14 - TIM5 or TIM2 Capture/Compare interrupt -- device dependent
#ifdef STM8S903
  #if defined(USE_TIM5_CAPCOM_ISR)
    #define __TIM5_CAPCOM_VECTOR__  14
    ISR_HANDLER(TIM5_CAPCOM_ISR, __TIM5_CAPCOM_VECTOR__);
  #else
    #define TIM5_CAPCOM_ISR         NonHandledInterrupt              
  #endif
#else
  #if defined(USE_TIM2_CAPCOM_ISR)
    #define __TIM2_CAPCOM_VECTOR__  14
    ISR_HANDLER(TIM2_CAPCOM_ISR, __TIM2_CAPCOM_VECTOR__);
  #else
    #define TIM2_CAPCOM_ISR         NonHandledInterrupt              
  #endif
#endif


/// irq15 - TIM3 Update/overflow interrupt -- device dependent
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8AF626x)
  #if defined(USE_TIM3_UPD_ISR)
    #define __TIM3_UPD_VECTOR__     15
    ISR_HANDLER(TIM3_UPD_ISR, __TIM3_UPD_VECTOR__);
  #else
    #define TIM3_UPD_ISR             NonHandledInterrupt              
  #endif
#endif


/// irq16 - TIM3 Capture/Compare interrupt -- device dependent
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8AF626x)
  #if defined(USE_TIM3_CAPCOM_ISR)
    #define __TIM3_CAPCOM_VECTOR__  16
    ISR_HANDLER(TIM3_CAPCOM_ISR, __TIM3_CAPCOM_VECTOR__);
  #else
    #define TIM3_CAPCOM_ISR         NonHandledInterrupt              
  #endif
#endif


/// irq17 - USART/UART1 send (TX empty) interrupt -- device dependent
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8S903)
  #if defined(USE_UART1_TXE_ISR)
    #define __UART1_TXE_VECTOR__    17
    ISR_HANDLER(UART1_TXE_ISR, __UART1_TXE_VECTOR__);
  #else
    #define UART1_TXE_ISR           NonHandledInterrupt
  #endif
#endif


/// irq18 - USART/UART1 receive (RX full) interrupt -- device dependent
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8S903)
  #if defined(USE_UART1_RXF_ISR)
    #define __UART1_RXF_VECTOR__    18
    ISR_HANDLER(UART1_RXF_ISR, __UART1_RXF_VECTOR__);
  #else
    #define UART1_RXF_ISR           NonHandledInterrupt
  #endif
#endif
 

/// irq19 - I2C interrupt
#if defined(USE_I2C_ISR)
  #define __I2C_VECTOR__            19
  ISR_HANDLER(I2C_ISR, __I2C_VECTOR__);
#else
  #define I2C_ISR                   NonHandledInterrupt
#endif


/// irq20 - UART2/3/4 send (TX empty) interrupt -- device dependent
#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x) || defined(STM8S207) || \
    defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
  #if defined(USE_UART234_TXE_ISR)
    #define __UART234_TXE_VECTOR__ 20
    ISR_HANDLER(UART234_TXE_ISR, __UART234_TXE_VECTOR__);
  #else
    #define UART234_TXE_ISR       NonHandledInterrupt
  #endif
#endif


/// irq21 - UART2/3/4 receive (RX full) interrupt -- device dependent
#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x) || defined(STM8S207) || \
    defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
  #if defined(USE_UART234_RXF_ISR)
    #define __UART234_RXF_VECTOR__ 21
    ISR_HANDLER(UART234_RXF_ISR, __UART234_RXF_VECTOR__);
  #else
    #define UART234_RXF_ISR       NonHandledInterrupt
  #endif
#endif
 

/// irq22 - ADC1/2 end of conversion/Analog watchdog interrupts
#if defined(USE_ADC_ISR)
  #define __ADC_VECTOR__            22
  ISR_HANDLER(ADC_ISR, __ADC_VECTOR__);
#else
  #define ADC_ISR                   NonHandledInterrupt
#endif
 

/// irq23 - TIM4 or TIM6 Update/Overflow interrupt
#if defined(STM8S903) || defined(STM8AF622x)
  #if defined(USE_TIM6_UPD_ISR)
    #define __TIM6_UPD_VECTOR__     23
    ISR_HANDLER(TIM6_UPD_ISR, __TIM6_UPD_VECTOR__);
  #else
    #define TIM6_UPD_ISR            NonHandledInterrupt
  #endif
#else
  #if defined(USE_TIM4_UPD_ISR)
    #define __TIM4_UPD_VECTOR__     23
    ISR_HANDLER(TIM4_UPD_ISR, __TIM4_UPD_VECTOR__);
  #else
    #define TIM4_UPD_ISR            NonHandledInterrupt
  #endif
#endif
 

/// irq24 - flash interrupt
#if defined(USE_FLASH_ISR)
  #define __FLASH_VECTOR__          24
  ISR_HANDLER(FLASH_ISR, __FLASH_VECTOR__);
#else
  #define FLASH_ISR                 NonHandledInterrupt              
#endif

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _INTERRUPT_VECTOR_H_
