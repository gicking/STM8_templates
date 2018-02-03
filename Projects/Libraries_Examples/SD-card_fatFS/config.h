/**
  \file config.h
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief project specific settings
   
  project specific configuration header file
  Select STM8 device and activate optional options
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _CONFIG_H_
#define _CONFIG_H_


// select board to set STM8 family, memory size etc. 
//#include "muBoard_config.h"

/// alternatively select STM8 device directly. For supported devices see file "stm8as.h"
#define STM8S208      // muBoard


/// required for timekeeping (1ms interrupt)
#define USE_TIM4_UPD_ISR



///////////
// configure PetitFS, see http://elm-chan.org/fsw/ff/00index_p.html
///////////
#define _USE_READ   1    // Enable pf_read() function (+ 666B flash)
#define _USE_WRITE  1    // Enable pf_write() function (+ 1216B flash)
#define _USE_DIR    1    // Enable pf_opendir() and pf_readdir() functions (+ 961B flash)
#define _USE_LSEEK  1    // Enable pf_lseek() function (+ 613B flash)


///////////
// define macros required in PetitFS diskio.c and bitbang mode
///////////
#define	INIT_PORT()	{  \
  pinMode(&PORT_C, 6, OUTPUT);                 /* SPI_MOSI */  \
  pinMode(&PORT_C, 7, INPUT_PULLUP);           /* SPI_MISO */  \
  pinMode(&PORT_C, 5, OUTPUT);                 /* SPI_SCK */  \
  pinMode(&PORT_F, 0, OUTPUT);                 /* CSN for SD card */  \
}

#define SPI_MOSI   pinOutputReg(&PORT_C,pin6)  ///< SPI MOSI output
#define SPI_MISO   pinInputReg(&PORT_C,pin7)   ///< SPI MISO input
#define SPI_SCK    pinOutputReg(&PORT_C,pin5)  ///< SPI SCK output
#define SPI_SD_CSN pinOutputReg(&PORT_F,pin0)  ///< CSN output for SD card selection

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _CONFIG_H_
