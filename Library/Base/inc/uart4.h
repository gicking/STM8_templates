/**
  \file uart4.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of UART4 / LINUART functions & macros
   
  declaration of UART4 / LINUART functions and macros for send & receive.
  Optional functionality via #define:
    - USE_UART234_TXE_ISR:  use TXE interrupt (shared with UART2+3, default is w/o ISR)
    - USE_UART234_RXF_ISR:  use RXF interrupt (shared with UART2+3, default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _UART4_H_
#define _UART4_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// only if UART4_TXE interrupts are used
#if defined(USE_UART234_TXE_ISR)

  /// enable UART4_TXE interrupt
  #define UART4_enable_send_interrupt()  UART4.CR2.reg.TIEN = 1

  /// disable UART4_TXE interrupt
  #define UART4_disable_send_interrupt() UART4.CR2.reg.TIEN = 0

#endif

// only if UART4_RXF interrupts are used
#if defined(USE_UART234_RXF_ISR)

  /// enable UART4_RXF interrupt
  #define UART4_enable_receive_interrupt()  UART4.CR2.reg.RIEN = 1

  /// disable UART4_RXF interrupt
  #define UART4_disable_receive_interrupt() UART4.CR2.reg.RIEN = 0

#endif



/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// init UART4 for communication
void     UART4_begin(uint32_t BR);

/// send arry of bytes via UART4
void     UART4_writeBytes(uint16_t num, uint8_t *buf);


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL INLINE FUNCTIONS
-----------------------------------------------------------------------------*/

/**
  \fn void UART4_end(void)
   
  \brief UART4 disable sender & receiver

  UART4 disable sender & receiver. Retain previous settings
*/
INLINE void UART4_end(void) {

  // disable sender & receiver
  UART4.CR2.reg.TEN = 0;
  UART4.CR2.reg.REN = 0;
  
} // UART4_end



/**
  \fn uint8_t UART4_available(void)
   
  \brief UART4 check if data available
  
  \return  1=data waiting, 0=receive buffer empty

  UART4 check if data is available
*/
INLINE uint8_t UART4_available(void) {

  // return if data in Rx buffer
  return(UART4.SR.reg.RXNE);
  
} // UART4_available



/**
  \fn void  UART4_write(uint8_t data)
   
  \brief send byte via UART4
  
  \param[in]  data   byte to send

  send byte via UART4 as soon as possible
*/
INLINE void UART4_write(uint8_t data) {

  // wait until TX buffer is available
  while (!(UART4.SR.reg.TXE));
    
  // send byte
  UART4.DR.byte = data;
  
} // UART4_write



/**
  \fn uint8_t UART4_read(void)
   
  \brief UART4 byte receive function. Blocking
  
  \return received byte
  
  wait until byte received via UART4 and return content of Rx register
*/
INLINE uint8_t UART4_read(void) {

  // wait until byte received
  while (!(UART4.SR.reg.RXNE));

  // return Rx buffer
  return(UART4.DR.byte);

} // UART4_read



/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _UART4_H_
