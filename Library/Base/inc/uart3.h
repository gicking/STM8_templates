/**
  \file uart3.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of UART3 / LINUART functions & macros
   
  declaration of UART3 / LINUART functions and macros for send & receive.
  Optional functionality via #define:
    - USE_UART234_TXE_ISR:  use TXE interrupt (shared with UART2+4, default is w/o ISR)
    - USE_UART234_RXF_ISR:  use RXF interrupt (shared with UART2+4, default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _UART3_H_
#define _UART3_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// only if UART3_TXE interrupts are used
#if defined(USE_UART234_TXE_ISR)

  /// enable UART3_TXE interrupt
  #define UART3_enable_send_interrupt()  UART3.CR2.reg.TIEN = 1

  /// disable UART3_TXE interrupt
  #define UART3_disable_send_interrupt() UART3.CR2.reg.TIEN = 0

#endif

// only if UART3_RXF interrupts are used
#if defined(USE_UART234_RXF_ISR)

  /// enable UART3_RXF interrupt
  #define UART3_enable_receive_interrupt()  UART3.CR2.reg.RIEN = 1

  /// disable UART3_RXF interrupt
  #define UART3_disable_receive_interrupt() UART3.CR2.reg.RIEN = 0

#endif



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init UART3 for communication
void     UART3_begin(uint32_t BR);

/// send arry of bytes via UART3
void     UART3_writeBytes(uint16_t num, uint8_t *buf);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL INLINE FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn void UART3_end(void)
   
  \brief UART3 disable sender & receiver

  UART3 disable sender & receiver. Retain previous settings
*/
INLINE void UART3_end(void) {

  // disable sender & receiver
  UART3.CR2.reg.TEN = 0;
  UART3.CR2.reg.REN = 0;
  
} // UART3_end



/**
  \fn uint8_t UART3_available(void)
   
  \brief UART3 check if data available
  
  \return  1=data waiting, 0=receive buffer empty

  UART3 check if data is available
*/
INLINE uint8_t UART3_available(void) {

  // return if data in Rx buffer
  return(UART3.SR.reg.RXNE);
  
} // UART3_available



/**
  \fn void  UART3_write(uint8_t data)
   
  \brief send byte via UART3
  
  \param[in]  data   byte to send

  send byte via UART3 as soon as possible
*/
INLINE void UART3_write(uint8_t data) {

  // wait until TX buffer is available
  while (!(UART3.SR.reg.TXE));
    
  // send byte
  UART3.DR.byte = data;
  
} // UART3_write



/**
  \fn uint8_t UART3_read(void)
   
  \brief UART3 byte receive function. Blocking
  
  \return received byte
  
  wait until byte received via UART3 and return content of Rx register
*/
INLINE uint8_t UART3_read(void) {

  // wait until byte received
  while (!(UART3.SR.reg.RXNE));

  // return Rx buffer
  return(UART3.DR.byte);

} // UART3_read



/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _UART3_H_
