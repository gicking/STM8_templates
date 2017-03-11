/**
  \file stm8_interrupt_vector.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
  \copyright MIT License (MIT)

  \brief declaration if interrupt vector table (Cosmic compiler only)
   
  declaration if interrupt vector table for Cosmic compiler. If not required, replace below ISRs 
  with NonHandledInterrupt (=dummy) service routine. For SDCC just skip the implementation of 
  not required ISR.
*/

// get specified ISR usage
#include <stdlib.h>
#include "config.h"


// only for COSMIC compiler, else skip
#if defined(__CSMC__)

  #if defined(USE_TRAP)
    #include "trap.h"
  #else
    #define TRAP_ISR                NonHandledInterrupt               
  #endif
  
  #if defined(USE_TLI_ISR)
    #include "gpio.h"
  #else
    #define TLI_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_AWU_ISR)
    #include "awu.h"
  #else
    #define AWU_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_CLK_ISR)
    #include "clk.h"
  #else
    #define CLK_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_PORT_ISR)
    #include "gpio.h"
  #else
    #define EXTI0_ISR               NonHandledInterrupt             
    #define EXTI1_ISR               NonHandledInterrupt             
    #define EXTI2_ISR               NonHandledInterrupt             
    #define EXTI3_ISR               NonHandledInterrupt             
    #define EXTI4_ISR               NonHandledInterrupt             
  #endif
  
  #if defined(USE_CAN_ISR)
    #include "can.h"
  #else
    #define CAN_RX_ISR              NonHandledInterrupt            
    #define CAN_TX_ISR              NonHandledInterrupt            
  #endif
  
  #if defined(USE_SPI_ISR)
    #include "spi.h"
  #else
    #define SPI_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_TIM1_ISR)
    #include "timer1.h"
  #else
    #define TIM1UPD_ISR             NonHandledInterrupt           
    #define TIM1CAP_ISR             NonHandledInterrupt           
  #endif
  
  #if defined(USE_TIM2_ISR)
    #include "timer2.h"
  #else
    #define TIM2UPD_ISR             NonHandledInterrupt           
    #define TIM2CAP_ISR             NonHandledInterrupt           
  #endif
  
  #if defined(USE_TIM3UPD_ISR)
    #include "timer3.h"
  #else
    #define TIM3UPD_ISR             NonHandledInterrupt           
  #endif
  
  #if defined(USE_TIM3CAP_ISR)
    #include "timer3.h"
  #else
    #define TIM3CAP_ISR             NonHandledInterrupt           
  #endif
  
  #if defined(USE_UART1_TXE_ISR)
    #include "uart1.h"
  #else
    #define UART1_TXE_ISR           NonHandledInterrupt     
  #endif
  
  #if defined(USE_UART1_RXF_ISR)
    #include "uart1.h"
  #else
    #define UART1_RXF_ISR           NonHandledInterrupt     
  #endif
  
  #if defined(USE_I2C_ISR)
    #include "i2c.h"
  #else
    #define I2C_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_UART2_ISR)
    #include "uart2"
  #elif defined(USE_UART3_ISR)
    #include "uart3"
  #elif defined(USE_UART4_ISR)
    #include "uart4"
  #else
    #define UART2_3_4_TXE_ISR       NonHandledInterrupt 
    #define UART2_3_4_RXF_ISR       NonHandledInterrupt 
  #endif
    
  #if defined(USE_ADC1_ISR)
    #include "adc1.h"
  #elif defined(USE_ADC2_ISR)
    #include "adc2.h"
  #else
    #define ADC_ISR                 NonHandledInterrupt               
  #endif
  
  #if defined(USE_TIM4_ISR)
    #include "timer4.h"
  #else
    #define TIM4UPD_ISR             NonHandledInterrupt           
  #endif
  
  #if defined(USE_FLASH_ISR)
    #include "flash.h"
  #else
    #define FLASH_ISR               NonHandledInterrupt             
  #endif
    
    
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
      {0x82, (interrupt_handler_t) EXTI0_ISR},                  /* irq3  - External interrupt 0 (GPIOA) */
      {0x82, (interrupt_handler_t) EXTI1_ISR},                  /* irq4  - External interrupt 1 (GPIOB) */
      {0x82, (interrupt_handler_t) EXTI2_ISR},                  /* irq5  - External interrupt 2 (GPIOC) */
      {0x82, (interrupt_handler_t) EXTI3_ISR},                  /* irq6  - External interrupt 3 (GPIOD) */
      {0x82, (interrupt_handler_t) EXTI4_ISR},                  /* irq7  - External interrupt 4 (GPIOE) */
      {0x82, (interrupt_handler_t) CAN_RX_ISR},                 /* irq8  - CAN interrupt Rx */
      {0x82, (interrupt_handler_t) CAN_TX_ISR},                 /* irq9  - CAN interrupt Tx/ER/SC */
      {0x82, (interrupt_handler_t) SPI_ISR},                    /* irq10 - SPI End of transfer interrupt */
      {0x82, (interrupt_handler_t) TIM1UPD_ISR},                /* irq11 - TIM1 Update/Overflow/Trigger/Break interrupt */
      {0x82, (interrupt_handler_t) TIM1CAP_ISR},                /* irq12 - TIM1 Capture/Compare interrupt */
      {0x82, (interrupt_handler_t) TIM2UPD_ISR},                /* irq13 - TIM2 Update/Overflow/Break interrupt */
      {0x82, (interrupt_handler_t) TIM2CAP_ISR},                /* irq14 - TIM2 Capture/Compare interrupt */
      {0x82, (interrupt_handler_t) TIM3UPD_ISR},                /* irq15 - TIM3 Update/overflow */
      {0x82, (interrupt_handler_t) TIM3CAP_ISR},                /* irq16 - TIM3 Capture/compare */
      {0x82, (interrupt_handler_t) UART1_TXE_ISR},              /* irq17 - USART1 Tx send interrupt */
      {0x82, (interrupt_handler_t) UART1_RXF_ISR},              /* irq18 - USART1 Rx receive interrupt */
      {0x82, (interrupt_handler_t) I2C_ISR},                    /* irq19 - I2C interrupt */
      {0x82, (interrupt_handler_t) UART2_3_4_TXE_ISR},          /* irq20 - LINUART3 Tx interrupt */
      {0x82, (interrupt_handler_t) UART2_3_4_RXF_ISR},          /* irq21 - LINUART3 Rx interrupt */
      {0x82, (interrupt_handler_t) ADC_ISR},                    /* irq22 - ADC end of conversion/Analog watchdog interrupts */
      {0x82, (interrupt_handler_t) TIM4UPD_ISR},                /* irq23 - Timer 4 interrupt */
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
