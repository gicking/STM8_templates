/**
  \file muBoard_config.h
   
  \author G. Icking-Konert
  \date 2017-04-22
  \version 0.1
   
  \brief muBoard specific settings
   
  muBoard specific configuration header file
  Selects STM8 family, memory sizes etc.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MUBOARD_CONFIG_H_
#define _MUBOARD_CONFIG_H_

// board name for pin initialization
#define MUBOARD

/// select STM8 device used for muBoard
#define STM8S208

// set memory size
#define PFLASH_SIZE  (1024L * 128)
#define RAM_SIZE     (1024  * 6)
#define EEPROM_SIZE  (2048)


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _MUBOARD_CONFIG_H_
