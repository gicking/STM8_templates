/**
  \file uart4.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of UART4 / LINUART functions & macros
   
  implementation of UART4 / LINUART functions and macros for send & receive.
  Optional functionality via #define:
    - USE_UART234_TXE_ISR:  use TXE interrupt (shared with UART2+3, default is w/o ISR)
    - USE_UART234_RXF_ISR:  use RXF interrupt (shared with UART2+3, default is w/o ISR)
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "uart4.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART4_begin(uint32_t BR)
   
  \brief initialize UART4 for blocking/polling communication 
  
  \param[in]  BR    baudrate [Baud]

  initialize UART4 for communication with specified baudrate.
  Use 1 start, 8 data and 1 stop bit; no parity or flow control.
*/
void UART4_begin(uint32_t BR) {

  volatile uint16_t  val16;
  
  // set UART4 behaviour
  UART4.CR1.byte = UART4_CR1_RESET_VALUE;  // enable UART4, 8 data bits, no parity control
  UART4.CR2.byte = UART4_CR2_RESET_VALUE;  // no interrupts, disable sender/receiver 
  UART4.CR3.byte = UART4_CR3_RESET_VALUE;  // no LIN support, 1 stop bit, no clock output(?)

  // set baudrate (note: BRR2 must be written before BRR1!)
  val16 = (uint16_t) (((uint32_t) 16000000L)/BR);
  UART4.BRR2.byte = (uint8_t) (((val16 & 0xF000) >> 8) | (val16 & 0x000F));
  UART4.BRR1.byte = (uint8_t) ((val16 & 0x0FF0) >> 4);
  
  // enable transmission
  UART4.CR2.reg.REN = 1; // enable receiver
  UART4.CR2.reg.TEN = 1; // enable sender

} // UART4_begin

 
/**
  \fn void  UART4_writeBytes(uint16_t num, uint8_t *data)
   
  \brief send arry of bytes via UART4
  
  \param[in]  num    buf size in bytes
  \param[in]  data   bytes to send

  send array of bytes via UART4 directly
*/
void  UART4_writeBytes(uint16_t num, uint8_t *data) {

  uint16_t i;

  // send bytes
  for (i=0; i<num; i++) {
    UART4_write(data[i]);
  }      

} // UART4_writeBytes

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
