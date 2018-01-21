/**
  \file stm8s_conf.h
   
  \author G. Icking-Konert
  \date 2017-12-26
  \version 0.1
   
  \brief configuration for SPL part of the project
   
  project specific SPL configuration header file.
  Select SPL modules to use in project
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

// SPL headers -> modules to include. Don't mix SPL and STM8_template headers!
#include "stm8s.h"
#include "stm8s_gpio.h"


// assert is required by SPL (even a dummy one)
#define USE_FULL_ASSERT (0) 
#ifdef  USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif // USE_FULL_ASSERT

#endif // __STM8S_CONF_H

