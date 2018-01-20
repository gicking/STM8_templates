/**
  \file i2c.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of I2C functions/macros
   
  implementation of functions for I2C bus communication
  For I2C bus, see http://en.wikipedia.org/wiki/I2C
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _I2C_MAIN_
  #include "i2c.h"
#undef _I2C_MAIN_
#include "gpio.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void i2c_init(void)
   
  \brief configure I2C bus

  configure I2C bus as master in standard mode, BR=100kHz, 7bit address, 250ns rise time
*/
void i2c_init() {

  // configure I2C pins PE1(=SCL) and PE2(=SDA)
  pinMode(PORT_E, pin1, OUTPUT_OPENDRAIN);
  pinMode(PORT_E, pin2, OUTPUT_OPENDRAIN);

  // init I2C bus
  I2C.CR1.byte          = 0x00;     // disable I2C, no clock stretching
  I2C.CR2.byte          = 0x00;     // reset I2C bus
  I2C.CR2.reg.ACK       = 1;        // enable ACK on address match
  I2C.FREQR.reg.FREQ    = 16;       // peripheral clock = 16MHz (f=val*1MHz)
  I2C.OARH.reg.ADDCONF  = 1;        // set 7b addressing mode
  I2C.OARL.reg.ADD      = 0x04;     // set own 7b addr to 0x04
  I2C.SR1.byte          = 0x00;     // clear status registers
  I2C.SR2.byte          = 0x00;
  I2C.SR3.byte          = 0x00;
  I2C.CCRL.reg.CCR      = 0x50;     // BR = 100kBaud (t_low = t_high = 80/16MHz)
  I2C.CCRH.byte         = 0x00;     // I2C standard mode
  I2C.TRISER.reg.TRISE  = 0x04;     // t_rise<250ns (<300ns for display driver)
  I2C.CR1.reg.PE        = 1;        // enable I2C module with broadcast receive disabled

} // i2c_init



/**
  \fn uint8_t i2c_waitFree(void)
   
  \brief wait until bus is free

  \return error code (0=ok; 1=timeout)

  wait until bus is free with timeout
*/
uint8_t i2c_waitFree() {

  uint16_t  countTimeout;     // use counter for timeout to minimize dependencies
  
  // wait until bus free with timeout
  countTimeout = 10000;                           // ~1.1us/inc -> ~10ms
  while ((I2C_BUSY) && (countTimeout--));
 
  // on I2C timeout return error
  if (I2C_BUSY) {
    i2c_init();
    return(1);
  }
  
  // return success
  return(0);

} // i2c_waitFree



/**
  \fn uint8_t i2c_start(void)
   
  \brief generate I2C start condition

  \return error code (0=ok; 1=timeout)

  generate I2C start condition with timeout
*/
uint8_t i2c_start() {

  uint16_t  countTimeout;     // use counter for timeout to minimize dependencies
  
  // generate start condition with timeout
  I2C.CR2.reg.START = 1;
  countTimeout = 10000;                           // ~1.1us/inc -> ~10ms
  while ((!I2C.SR1.reg.SB) && (countTimeout--));
 
  // on I2C timeout return error
  if (!I2C.SR1.reg.SB) {
    i2c_init();
    return(1);
  }

  // return success
  return(0);

} // i2c_start



/**
  \fn uint8_t i2c_stop(void)
   
  \brief generate I2C stop condition

  \return error code (0=ok; 1=timeout)

  generate I2C stop condition with timeout 
*/
uint8_t i2c_stop() {

  uint16_t  countTimeout;     // use counter for timeout to minimize dependencies

  // generate stop condition with timeout
  I2C.CR2.reg.STOP = 1;
  countTimeout = 10000;                           // ~1.1us/inc -> ~10ms
  while ((I2C.SR3.reg.MSL) && (countTimeout--));
 
  // on I2C timeout set error flag
  if (I2C.SR3.reg.MSL) {
    i2c_init();
    return(1);
  }
  
  // return success
  return(0);

} // i2c_stop



/**
  \fn uint8_t i2c_send(uint8_t addr, uint8_t numTx, uint8_t *bufTx)
   
  \brief write data via I2C

  \param[in]  addr        7b address [6:0] of I2C slave
  \param[in]  numTx       number of bytes to send
  \param[in]  bufTx       send buffer

  \return error code (0=ok; 1=timeout)

  write data to I2C slave with frame timeout. Note that no start or 
  stop condition is generated.
*/
uint8_t i2c_send(uint8_t addr, uint8_t numTx, uint8_t *bufTx) {

  uint8_t   i;
  uint16_t  countTimeout;     // use counter for timeout to minimize dependencies

  // send 7b slave adress [7:1] + write flag (LSB=0)
  I2C.DR.byte = (uint8_t) ((addr << 1) & ~0x01);       // shift left and set LSB (write=0, read=1)
  countTimeout = 10000;                                // ~1.1us/inc -> ~10ms
  while ((!I2C.SR1.reg.ADDR) && (countTimeout--));     // wait until address sent or timeout
  countTimeout = 10000;                                // ~1.1us/inc -> ~10ms 
  while ((!I2C.SR3.reg.BUSY) && (countTimeout--));     // seems to be required...???
  
  // no I2C timeout -> send data
  if (countTimeout) {
    for (i=0; i<numTx; i++) {
      I2C.DR.byte = bufTx[i];
      countTimeout = 1000;                             // ~1.1us/inc -> ~1ms 
      while ((!I2C.SR1.reg.TXE) && (countTimeout--));  // wait until DR buffer empty or timeout
    }
  }
 
  // on I2C timeout return error
  else {
    i2c_init();
    return(1);
  }

  // return success
  return(0);

} // i2c_send



/**
  \fn uint8_t i2c_request(uint8_t slaveAddr, uint8_t numRx, uint8_t *bufRx)
   
  \brief request data via I2C as master

  \param[in]  slaveAddr   7b address [6:0] of I2C slave
  \param[in]  numRx       number of bytes to receive
  \param[out] bufRx       receive buffer

  \return error code (0=ok; 1=timeout)

  request data from I2C slave with frame timeout. Note that no start or 
  stop condition is generated.
*/
uint8_t i2c_request(uint8_t slaveAddr, uint8_t numRx, uint8_t *bufRx) {

  uint8_t   i;
  uint16_t  countTimeout;     // use counter for timeout to minimize dependencies
  
  // init receive buffer
  for (i=0; i<numRx; i++)
    bufRx[i] = 0;
    
  // send 7b slave adress [7:1] + read flag (LSB=1)
  I2C.DR.byte = (uint8_t) ((slaveAddr << 1) | 0x01);   // shift left and set LSB (write=0, read=1)
  countTimeout = 10000;                                // ~1.1us/inc -> ~10ms
  while ((!I2C.SR1.reg.ADDR) && (countTimeout--));     // wait until adress sent or timeout
  countTimeout = 1000;                                 // ~1.1us/inc -> ~1ms 
  while ((!I2C.SR3.reg.BUSY) && (countTimeout--));     // seems to be required...???

  for (i=0; i<numRx; i++) {
    countTimeout = 1000;                               // ~1.1us/inc -> ~1ms 
    while ((!I2C.SR1.reg.RXNE) && (countTimeout--));   // wait until DR buffer not empty or timeout
    bufRx[i] = I2C.DR.byte;
  }
 
  // on I2C timeout return error
  if (!countTimeout) {
    i2c_init();
    return(1);
  }

  // return success
  return(0);
 
} // i2c_request


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
