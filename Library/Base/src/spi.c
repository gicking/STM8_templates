/**
  \file spi.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of SPI functions/macros
   
  implementation of functions for SPI communication
  For SPI bus, see https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _SPI_MAIN_
  #include "spi.h"
#undef _SPI_MAIN_
#include "gpio.h"
#include "misc.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
// number of SPI settings
#if !defined(NUM_SPI_SETTINGS)
  #define  NUM_SPI_SETTINGS  2
#endif

// buffers for SPI configuration (e.g. for SD card)
volatile uint8_t   saved_SPI_CR1[NUM_SPI_SETTINGS];
volatile uint8_t   saved_SPI_CR2[NUM_SPI_SETTINGS];


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn spi_init_master(uint8_t type, uint8_t pre, uint8_t order, uint8_t mode)
   
  \brief configure SPI interface in master mode

  \param[in]  type      4-wire full-duplex(=SPI_4_WIRE) or 3-wire half duplex(=SPI_3_WIRE)
  \param[in]  pre       baudrate prescaler (BR=F_CPU/2^(pre+1))
  \param[in]  order     bit order: MSBFIRST or LSBFIRST
  \param[in]  mode      SPI clock polarity & phase (SPI_MODE0..3, see https://www.arduino.cc/en/Reference/SPI)

  configure SPI for master mode with 3- or 4-wire interface.
  
*/
void spi_init_master(uint8_t type, uint8_t pre, uint8_t order, uint8_t mode) {

  // disable SPI module
  SPI.CR1.reg.SPE = 0;

  // configure SPI for master mode
  SPI.CR2.reg.SSM  = 1;
  SPI.CR2.reg.SSI  = 1;
  SPI.CR1.reg.MSTR = 1;
  
  // set SPI type: 4-wire full-duplex(=0) or 3-wire half duplex(=1)
  SPI.CR2.reg.BDM = type;
 
  // for half-duplex disable data pin (=MOSI) interrupts in input mode (see ref. manual)
  if (SPI.CR2.reg.BDM == SPI_3_WIRE) {
    PORT_C.CR2.bit.pin6 = 0; 
  }
     
  // set baudrate (=16MHz/2^(pre+1))
  SPI.CR1.reg.BR = (uint8_t) pre;
  
  // SPI bit order (0=MSB first, 1=LSB first; see misc.h)
  SPI.CR1.reg.xLSBFIRST = (uint8_t) order; 
 

  if (mode == SPI_MODE0) {
    SPI.CR1.reg.CPOL = 0;   // idle SCK polarity low(=0) or high(=1)
    SPI.CR1.reg.CPHA = 0;   // capture on falling(=0) or rising(=1) edge
  }
  else if (mode == SPI_MODE1) {
    SPI.CR1.reg.CPOL = 0;   // idle SCK polarity low(=0) or high(=1)
    SPI.CR1.reg.CPHA = 1;   // capture on falling(=0) or rising(=1) edge
  }    
  else if (mode == SPI_MODE2) {
    SPI.CR1.reg.CPOL = 1;   // idle SCK polarity low(=0) or high(=1)
    SPI.CR1.reg.CPHA = 0;   // capture on falling(=0) or rising(=1) edge
  }
  else { // mode == SPI_MODE3
    SPI.CR1.reg.CPOL = 1;   // idle SCK polarity low(=0) or high(=1)
    SPI.CR1.reg.CPHA = 1;   // capture on falling(=0) or rising(=1) edge
  }
  
  // configure NSS(=CSN) SW-control
  SPI.CR2.reg.SSM = 1;
  SPI.CR2.reg.SSI = 1;
  
  // enable SPI module
  SPI.CR1.reg.SPE = 1;
  
} // spi_init_master



/**
  \fn void spi_save_config(uint8_t N)
   
  \brief save SPI configuration N

  \param[in]  N    index of configuration buffer (must be 0..NUM_SPI_SETTINGS-1)

  save configuration of SPI to buffer N. 
  Is convenient to switch settings for different SPI slaves
  Warning: for speed reasons no range check is performed!
*/
void spi_save_config(uint8_t N) {

  uint8_t tmp;
  
  // disable enable status prior to saving
  tmp = SPI.CR1.reg.SPE;
  SPI.CR1.reg.SPE = 0;
  
  // buffers for SPI configuration (e.g. for SD card)
  saved_SPI_CR1[N] = SPI.CR1.byte;
  saved_SPI_CR2[N] = SPI.CR2.byte;
  
  // restore enable status
  SPI.CR1.reg.SPE = tmp;

} // spi_save_config



/**
  \fn void spi_restore_config(uint8_t N)
   
  \brief restore SPI configuration N

  \param[in]  N    index of configuration buffer (must be 0..NUM_SPI_SETTINGS-1)

  restore configuration of SPI from buffer N. 
  Is convenient to switch settings for different SPI slaves
  Warning: for speed reasons no range check is performed!
*/
void spi_restore_config(uint8_t N) {

  uint8_t tmp;
  
  // disable enable status prior to saving
  tmp = SPI.CR1.reg.SPE;
  SPI.CR1.reg.SPE = 0;
  
  // buffers for SPI configuration (e.g. for SD card)
  saved_SPI_CR1[N] = SPI.CR1.byte;
  saved_SPI_CR2[N] = SPI.CR2.byte;
  
  // restore enable status
  SPI.CR1.reg.SPE = tmp;

} // spi_restore_config



/**
  \fn void spi_send_receive(PORT_t *pPortCSN, uint8_t pinCSN, uint8_t numMOSI, uint8_t *MOSI, uint8_t numMISO, uint8_t *MISO)
   
  \brief send/receive via SPI in master mode

  \param[in]  pPortCSN   pointer to port of CSN, e.g. &PORT_A
  \param[in]  pinCSN     CSN pin number (0..7)
  \param[in]  numMOSI    number of bytes to send per frame
  \param[in]  MOSI       array of MOSI bytes [0..MAX_WIDTH_SPI-1]
  \param[in]  numMISO    number of bytes to receive per frame (=ignored for full-duplex)
  \param[out] MISO       array of MISO bytes [0..MAX_WIDTH_SPI-1]

  send/receive via SPI in master mode i.e. CSN control is by muBoard
  
*/
void spi_send_receive(PORT_t *pPortCSN, uint8_t pinCSN, uint8_t numMOSI, uint8_t *MOSI, uint8_t numMISO, uint8_t *MISO) {
  
  uint8_t		i;
    
  // wait until not busy
  while (SPI.SR.reg.BSY);
  
  // select SPI slave via CSN=low
  pinLow(pPortCSN, pinCSN);

  // full-duplex mode (= 4-wire)
  if (SPI.CR2.reg.BDM == SPI_4_WIRE) {
  
    // loop over MOSI
    for (i=0; i<numMOSI; i++) {
        
      // fill MOSI buffer when SPI free
      while (!SPI.SR.reg.TXE);
      if (SPI.CR1.reg.xLSBFIRST == MSBFIRST)
        SPI.DR.byte = MOSI[i];
      else
        SPI.DR.byte = MOSI[numMOSI-i];
        
      // copy MISO byte after received
      while (SPI.SR.reg.RXNE != 0);
      if (SPI.CR1.reg.xLSBFIRST == MSBFIRST)
        MISO[i] = SPI.DR.byte;
      else
        MISO[numMOSI-i] = SPI.DR.byte;
      
    } // loop over MOSI

  } // full-duplex mode
  
  
  // half duplex mode (= 3-wire)
  else {
  
    // switch SPI data pin to output
    while (SPI.SR.reg.BSY);
    SPI.CR2.reg.BDOE = 1;   

    // send MOSI bytes
    for (i=0; i<numMOSI; i++) {
        
      // fill MOSI buffer when available
      while (!SPI.SR.reg.TXE);
      if (SPI.CR1.reg.xLSBFIRST == MSBFIRST)
        SPI.DR.byte = MOSI[i];
      else
        SPI.DR.byte = MOSI[numMOSI-i];
        
    } // loop over MOSI
    
    
    // switch SPI data pin to input
    while (SPI.SR.reg.BSY);
		SPI.CR2.reg.BDOE = 0;   

    // receive MISO bytes
    for (i=0; i<numMISO; i++) {
        
      // send 0xFF to generate clock signal
      while (!SPI.SR.reg.TXE);
      SPI.DR.byte = 0xFF;
        
      // copy MISO byte after received
      while (SPI.SR.reg.RXNE != 0);
      if (SPI.CR1.reg.xLSBFIRST == MSBFIRST)
        MISO[i] = SPI.DR.byte;
      else
        MISO[numMISO-i] = SPI.DR.byte;
      
    } // loop over MISO
      
  } // half duplex mode

  // wait until SPI frame finished
  while (SPI.SR.reg.BSY);
      
  // de-select SPI slave via CSN=high
  pinHigh(pPortCSN, pinCSN);

} // spi_send_receive


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
