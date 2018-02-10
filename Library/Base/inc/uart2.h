/**
  \file uart2.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of UART2 / LINUART functions & macros
   
  declaration of UART2 / LINUART functions and macros for send & receive.
  Optional functionality via #define:
    - USE_UART234_TXE_ISR:  use TXE interrupt (shared with UART3+4, default is w/o ISR)
    - USE_UART234_RXF_ISR:  use RXF interrupt (shared with UART3+4, default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _UART2_H_
#define _UART2_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// only if UART2_TXE interrupts are used
#if defined(USE_UART234_TXE_ISR)

  /// enable UART2_TXE interrupt
  #define UART2_enable_send_interrupt()  UART2.CR2.reg.TIEN = 1

  /// disable UART2_TXE interrupt
  #define UART2_disable_send_interrupt() UART2.CR2.reg.TIEN = 0

#endif

// only if UART2_RXF interrupts are used
#if defined(USE_UART234_RXF_ISR)

  /// enable UART2_RXF interrupt
  #define UART2_enable_receive_interrupt()  UART2.CR2.reg.RIEN = 1

  /// disable UART2_RXF interrupt
  #define UART2_disable_receive_interrupt() UART2.CR2.reg.RIEN = 0

#endif



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init UART2 for communication
void     UART2_begin(uint32_t BR);

/// send arry of bytes via UART2
void     UART2_writeBytes(uint16_t num, uint8_t *buf);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL INLINE FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn void UART2_end(void)
   
  \brief UART2 disable sender & receiver

  UART2 disable sender & receiver. Retain previous settings
*/
INLINE void UART2_end(void) {

  // disable sender & receiver
  UART2.CR2.reg.TEN = 0;
  UART2.CR2.reg.REN = 0;
  
} // UART2_end



/**
  \fn uint8_t UART2_available(void)
   
  \brief UART2 check if data available
  
  \return  1=data waiting, 0=receive buffer empty

  UART2 check if data is available
*/
INLINE uint8_t UART2_available(void) {

  // return if data in Rx buffer
  return(UART2.SR.reg.RXNE);
  
} // UART2_available



/**
  \fn void  UART2_write(uint8_t data)
   
  \brief send byte via UART2
  
  \param[in]  data   byte to send

  send byte via UART2 as soon as possible
*/
INLINE void UART2_write(uint8_t data) {

  // wait until TX buffer is available
  while (!(UART2.SR.reg.TXE));
    
  // send byte
  UART2.DR.byte = data;
  
} // UART2_write



/**
  \fn uint8_t UART2_read(void)
   
  \brief UART2 byte receive function. Blocking
  
  \return received byte
  
  wait until byte received via UART2 and return content of Rx register
*/
INLINE uint8_t UART2_read(void) {

  // wait until byte received
  while (!(UART2.SR.reg.RXNE));

  // return Rx buffer
  return(UART2.DR.byte);

} // UART2_read



/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _UART2_H_
