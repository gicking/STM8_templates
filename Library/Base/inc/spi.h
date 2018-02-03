/**
  \file spi.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief declaration of SPI functions/macros
   
  declaration of functions for SPI communication
  For SPI bus, see https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include "stm8as.h"
#include "config.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// for readability
#define  SPI_4_WIRE    0     ///< configure 4-wire, full-duplex SPI
#define  SPI_3_WIRE    1     ///< configure 3-wire, half-duplex SPI

#define  SPI_MODE0     0     ///< clock phase & polarity, see https://www.arduino.cc/en/Reference/SPI
#define  SPI_MODE1     1     ///< clock phase & polarity, see https://www.arduino.cc/en/Reference/SPI
#define  SPI_MODE2     2     ///< clock phase & polarity, see https://www.arduino.cc/en/Reference/SPI
#define  SPI_MODE3     3     ///< clock phase & polarity, see https://www.arduino.cc/en/Reference/SPI


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// configure SPI interface in master mode
void    spi_init_master(uint8_t type, uint8_t pre, uint8_t order, uint8_t mode);

/// save SPI configuration N
void    spi_save_config(uint8_t N);

/// restore SPI configuration N
void    spi_restore_config(uint8_t N);

/// send and receive data via SPI (master mode)
void    spi_send_receive(PORT_t *pPortCSN, uint8_t pinCSN, uint8_t numMOSI, uint8_t *MOSI, uint8_t numMISO, uint8_t *MISO);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _SPI_H_
