/**
  \file shift.c
   
  \author G. Icking-Konert
  \date 2018-01-25
  \version 0.1
   
  \brief implementation of shiftIn() and shiftOut()
   
  implementation of synchronous data transmit (shiftOut) and receive (shiftIn) 
  software implementations.
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "shift.h"
#include "sw_delay.h"
#include <stdio.h>


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void shiftOut(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder, uint8_t data)
   
  \brief synchronous data transmit via software (master mode)
  
  \param[in]  pPortData  pointer to port for data output, e.g. &PORT_A
  \param[in]  pinData    pin number for data output
  \param[in]  pPortData  pointer to port for clock output, e.g. &PORT_B
  \param[in]  pinClock   pin number for clock output
  \param[in]  clockWidth width of clock pulse in microseconds
  \param[in]  bitOrder   which order to shift out the bits (MSBFIRST / LSBFIRST)
  \param[in]  data       byte to send
  
  Synchronous shift out data via data pin with clock pulse generation (i.e. as master).
*/
void shiftOut(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder, uint8_t data) {
  
  uint8_t   i;
  
  // loop over bits in data byte
  for (i=0; i<8; i++) {

    // output next data bit
    if (bitOrder == LSBFIRST)
      pinSet(pPortData, pinData, data & (0x01<<i));
    else  
      pinSet(pPortData, pinData, data & (0x01<<(7-i)));
      
    // generate clock trigger for slave to latch in data
    pinToggle(pPortClock, pinClock);
    sw_delayMicroseconds(clockWidth);
    pinToggle(pPortClock, pinClock);
    sw_delayMicroseconds(clockWidth);
 
  } // loop i

} // shiftOut



/**
  \fn uint8_t shiftIn(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder)
   
  \brief synchronous data receive via software (master mode)
  
  \param[in]  pPortData  pointer to port for data input, e.g. &PORT_A
  \param[in]  pinData    pin number for data input
  \param[in]  pPortData  pointer to port for clock output, e.g. &PORT_B
  \param[in]  pinClock   pin number for clock output
  \param[in]  clockWidth width of clock pulse in microseconds
  \param[in]  bitOrder   which order to shift in the bits (MSBFIRST / LSBFIRST)

  \return data received
  
  Synchronous shift in data via data pin with clock pulse generation (i.e. as master).
*/
uint8_t shiftIn(PORT_t *pPortData, uint8_t pinData, PORT_t *pPortClock, uint8_t pinClock, uint16_t clockWidth, uint8_t bitOrder) {
  
  volatile uint8_t data = 0x00;
  uint8_t i;

  // loop over bits in data byte
  for (i=0; i<8; i++) {
  
    pinToggle(pPortClock, pinClock);
    sw_delayMicroseconds(clockWidth);

    // read in next bit
    if (bitOrder == LSBFIRST)
      data |= (pinRead(pPortData,pinData) << i);
    else
      data |= (pinRead(pPortData,pinData) << (7-i));

    pinToggle(pPortClock, pinClock);
    sw_delayMicroseconds(clockWidth);

  } // loop i

  // return received byte
  return data;

} // shiftIn


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
