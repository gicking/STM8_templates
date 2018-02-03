/**
  \file mub_diffAmp.c
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief implementation of function to control the differential amplifier
   
  implementation of function to control the differential amplifier via I2C. Type
  OPAMP LM2904 (Farnell 2450774) with feedback via digital poti AD5282BRUZ200 (Farnell 1438442).
  Connect SCL/SDA of digital poti and of STM8 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#define _MUB_DIFFAMP_MAIN_    // required for globals in mub_diffAmp.h
  #include "mub_diffAmp.h"
#undef _MUB_DIFFAMP_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t set_diff_amplifier(uint8_t gain)
   
  \brief set differential amplifier gain
   
  \param[in] gain  new gain x1..x16
  
  \return  operation succeeded?
   
  set differential amplifier gain from x1 to x16
*/
uint8_t set_diff_amplifier(uint8_t gain) {

  // poti settings for gains 1..16 ( G=n/(255-n) )
  const uint8_t  lut[16] = { 127, 170, 191, 204, 212, 219, 223, 227, 229, 232, 234, 235, 237, 238, 239, 240 };
  volatile uint8_t err;

  // set resistance of channel A to Rmax/255*res, and B to Rmax/255*(255-res)
  err  = AD5282_set_poti(0, lut[gain-1]);
  err |= AD5282_set_poti(1, lut[gain-1]);

  // return error status
  return(err);

} // set_diff_amplifier


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
