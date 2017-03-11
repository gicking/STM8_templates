/**
  \file uart1_blocking.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation  of blocking UART1 / USART functions & macros
   
  implementation of UART1 / USART functions and macros for blocking send & 
  polling receive. This is the most primitive communication.
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "uart1_blocking.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART1_begin(uint32_t BR)
   
  \brief initialize UART1 for blocking/polling communication 
  
  \param[in]  BR    baudrate [Baud]

  initialize UART1 for communication with specified baudrate.
  Use 1 start, 8 data and 1 stop bit; no parity or flow control.
*/
void UART1_begin(uint32_t BR) {

  volatile uint16_t  val16;
  
  // set UART1 behaviour
  UART1.CR1.byte = UART1_CR1_RESET_VALUE;  // enable UART1, 8 data bits, no parity control
  UART1.CR2.byte = UART1_CR2_RESET_VALUE;  // no interrupts, disable sender/receiver 
  UART1.CR3.byte = UART1_CR3_RESET_VALUE;  // no LIN support, 1 stop bit, no clock output(?)

  // set baudrate (note: BRR2 must be written before BRR1!)
  val16 = (uint16_t) (((uint32_t) 16000000L)/BR);
  UART1.BRR2.byte = (uint8_t) (((val16 & 0xF000) >> 8) | (val16 & 0x000F));
  UART1.BRR1.byte = (uint8_t) ((val16 & 0x0FF0) >> 4);
  
  // enable transmission
  UART1.CR2.reg.REN = 1; // enable receiver
  UART1.CR2.reg.TEN = 1; // enable sender

} // UART1_begin


 
/**
  \fn void  UART1_write(uint8_t data)
   
  \brief send byte via UART1
  
  \param[in]  data   byte to send

  send byte via UART1 directly and blocking
*/
void  UART1_write(uint8_t data) {

  // wait until TX buffer is available
  while (!(UART1.SR.reg.TXE));
    
  // send byte
  UART1.DR.byte = data;
  
} // UART1_write


 
/**
  \fn void  UART1_writeBytes(uint16_t num, uint8_t *data)
   
  \brief send arry of bytes via UART1
  
  \param[in]  num    buf size in bytes
  \param[in]  data   bytes to send

  send array of bytes via UART1 directly
*/
void  UART1_writeBytes(uint16_t num, uint8_t *data) {

  uint16_t i;

  // send bytes (blocking)
  for (i=0; i<num; i++) {
    
    // wait until TX buffer is available
    while (!(UART1.SR.reg.TXE));
    
    // send byte
    UART1.DR.byte = data[i];      
  }

} // UART1_writeBytes



/**
  \fn uint8_t UART1_read(void)
   
  \brief UART1 data receive function
  
  \return  received byte or 0x00 (if buffer is empty)
  
  return content of UART1 Rx data register, or 0x00 if no byte was received
*/
uint8_t UART1_read(void) {

  uint8_t   data;
  
  // get content of UART1 Rx register
  if (UART1.SR.reg.RXNE)
    data = UART1.DR.byte;
  else
    data = 0x00;
   
  // return the data
  return(data);

} // UART1_read

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
