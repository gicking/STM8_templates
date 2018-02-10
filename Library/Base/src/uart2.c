/**
  \file uart2.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of UART2 / LINUART functions & macros
   
  implementation of UART2 / LINUART functions and macros for send & receive.
  Optional functionality via #define:
    - USE_UART234_TXE_ISR:  use TXE interrupt (shared with UART3+4, default is w/o ISR)
    - USE_UART234_RXF_ISR:  use RXF interrupt (shared with UART3+4, default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "uart2.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART2_begin(uint32_t BR)
   
  \brief initialize UART2 for blocking/polling communication 
  
  \param[in]  BR    baudrate [Baud]

  initialize UART2 for communication with specified baudrate.
  Use 1 start, 8 data and 1 stop bit; no parity or flow control.
*/
void UART2_begin(uint32_t BR) {

  volatile uint16_t  val16;
  
  // set UART2 behaviour
  UART2.CR1.byte = UART2_CR1_RESET_VALUE;  // enable UART2, 8 data bits, no parity control
  UART2.CR2.byte = UART2_CR2_RESET_VALUE;  // no interrupts, disable sender/receiver 
  UART2.CR3.byte = UART2_CR3_RESET_VALUE;  // no LIN support, 1 stop bit, no clock output(?)

  // set baudrate (note: BRR2 must be written before BRR1!)
  val16 = (uint16_t) (((uint32_t) 16000000L)/BR);
  UART2.BRR2.byte = (uint8_t) (((val16 & 0xF000) >> 8) | (val16 & 0x000F));
  UART2.BRR1.byte = (uint8_t) ((val16 & 0x0FF0) >> 4);
  
  // enable transmission
  UART2.CR2.reg.REN = 1; // enable receiver
  UART2.CR2.reg.TEN = 1; // enable sender

} // UART2_begin

 
/**
  \fn void  UART2_writeBytes(uint16_t num, uint8_t *data)
   
  \brief send arry of bytes via UART2
  
  \param[in]  num    buf size in bytes
  \param[in]  data   bytes to send

  send array of bytes via UART2 directly
*/
void  UART2_writeBytes(uint16_t num, uint8_t *data) {

  uint16_t i;

  // send bytes
  for (i=0; i<num; i++) {
    UART2_write(data[i]);
  }      

} // UART2_writeBytes

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
