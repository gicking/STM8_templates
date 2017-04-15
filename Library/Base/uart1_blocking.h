/**
  \file uart1_blocking.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of blocking UART1 / USART functions & macros
   
  declaration of UART1 / USART functions and macros for blocking send & 
  polling receive. This is the most primitive communication.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _UART1_BLOCKING_H_
#define _UART1_BLOCKING_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// UART1 check if data received
#define UART1_available()  (UART1.SR.reg.RXNE)

/// UART1 enable sender & receiver. Retain previous settings
#define UART1_listen()     { UART1.CR2.reg.TEN = 1; UART1.CR2.reg.REN = 1; }

/// UART1 disable sender & receiver
#define UART1_end()        { UART1.CR2.reg.TEN = 0; UART1.CR2.reg.REN = 0; }



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init UART1 for communication
void     UART1_begin(uint32_t BR);

/// send byte via UART1
void     UART1_write(uint8_t data);

/// send arry of bytes via UART1
void     UART1_writeBytes(uint16_t num, uint8_t *buf);

/// UART1 byte receive function. Non-blocking
uint8_t  UART1_read(void);

/// UART1 byte receive function. Blocking
uint8_t  UART1_readBlock(void);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _UART1_BLOCKING_H_
