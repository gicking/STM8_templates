/**
  \file STM8S_Discovery_config.h
   
  \author G. Icking-Konert
  \date 2017-04-22
  \version 0.1
   
  \brief STM8S Discovery specific settings
   
  STM8S Discovery board specific configuration header file
  Selects STM8 family, memory sizes etc.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _STM8S_DISCOVERY_CONFIG_H_
#define _STM8S_DISCOVERY_CONFIG_H_

// board name for pin initialization
#define STM8S_DISCOVERY

/// select STM8 device used for muBoard
#define STM8S105

// set memory size
#define PFLASH_SIZE  1024*32
#define RAM_SIZE     1024*2
#define EEPROM_SIZE  1024


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _STM8S_DISCOVERY_CONFIG_H_
