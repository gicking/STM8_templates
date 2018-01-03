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
#include "muBoard_config.h"

/// alternatively select STM8 device directly. For supported devices see file "stm8as.h"
//#define STM8S208      // muBoard


/// required for timekeeping (1ms interrupt)
#define USE_TIM4_UPD_ISR

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif  // _CONFIG_H_
